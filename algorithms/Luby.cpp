//
// Created by marta on 15/01/22.
//
#include "Luby.h"

#include <iostream>
#include <condition_variable>

mutex I_mutex, remainingNode_mutex;
mutex mutex_color;
condition_variable mis_cond_var;
int semMIS;

Luby::Luby() {}

Luby::Luby(int num_threads) : num_threads(num_threads) {}


void Luby::algorithmSolver(Graph &graph) {

    std::set <std::set<int>> mis;
    std::set<int> I;

    int num_vertices = graph.num_vertices();
    int max_color= 0;

    int num_remain= graph.num_vertices();
    std::set<int> nodes_remain;
    std::vector <Vertex> *verticesList = graph.getVerticesList();
    for(int i=0; i< num_remain; i++) {
        nodes_remain.insert(verticesList->at(i).getId());
    }



    vector<int> assigned_vertices(num_vertices+1, 0);
    semMIS= num_threads;

    if (num_threads > std::thread::hardware_concurrency())
        throw std::runtime_error("Hardware concurrency exceeded: please use at most " +
                                 std::to_string(std::thread::hardware_concurrency()) + " threads");

    Splitter s(num_vertices, num_threads);
    std::vector <std::thread> threads;

    //Part 1 : assign all vertices a random permutation and then find all MIS in the graph
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(std::thread([&graph, &mis, &I, &assigned_vertices, &max_color,this, s, i]() {
            int from = s.get_min(i), to = s.get_max(i);

            assign_num_to_vertices(from, to, assigned_vertices, graph);
            mis= find_MIS_Parallel(from, to, max_color,mis, I, assigned_vertices, graph);
            //mis= find_MIS_Sequential(from, to, mis, I, assigned_vertices, nodes_remain, num_remain, graph, graph.num_vertices());

        }));
    }

    for (auto &thread: threads) {
        thread.join();
    }


}






std::set <std::set<int>> Luby::find_MIS_Parallel(int from, int to, int &max_color,std::set <std::set<int>> &mis, std::set<int> &I,
                                                 vector<int> &assigned_vertices, Graph &graph) {

    int num_remain = to - from;
    std::set<int> nodes_remain;
    std::set<int> neighbors;
    std::vector <Vertex> *verticesList = graph.getVerticesList();

    for(int i=from; i< to; i++) {
        nodes_remain.insert(verticesList->at(i).getId());
    }

    int cur_node_id;
    std::vector <Vertex> neighborList;

    while (!nodes_remain.empty()) {

        std::cout << "RANGE [" <<from << ", " << to << "] ---> num_remain= " <<  nodes_remain.size() <<endl;
        for (int j = from; j < to; j++) {

            cur_node_id=  verticesList->at(j).getId();

            if (nodes_remain.find(cur_node_id) != nodes_remain.end()) {

                bool isMax= isMax_between_neighbor(verticesList->at(j), assigned_vertices);
                if(isMax){
                    //vertex is colored and inserted into the indipendent set
                    I_mutex.lock();
                    I.insert(cur_node_id);
                    graph.colorVertex(&verticesList->at(j), max_color);
                    assigned_vertices.at(cur_node_id)= -1;       //the next iteration it won't be the max
                    I_mutex.unlock();

                    //remove neighbors from nodes_remain if they belong to the interval [from, to)
                    neighborList = verticesList->at(j).getNeighborList();
                    int neighbor_id;
                    for (int k = 0; k < neighborList.size(); k++) { //for each neighbor of that node

                        neighbor_id = neighborList.at(k).getId();
                        if (neighbor_id >= from && neighbor_id < to) {

                            if (nodes_remain.find(neighbor_id) != nodes_remain.end()) {
                                num_remain--;
                                neighbors.insert(neighbor_id);
                                nodes_remain.erase(neighbor_id);
                            }
                        }
                    }

                    //remove cur_node_id from nodes_remain
                    num_remain--;
                    nodes_remain.erase(cur_node_id);
                    //std::cout << "num_remain= " << num_remain << " nodes_remain.size()" << nodes_remain.size()<< endl;

                    //std:: cout << "Colored node cur_node_id= " << cur_node_id << endl;

                }else{
                    neighbors.insert(cur_node_id);
                }

            }

        }


        //at this point a MIS is found
        std::unique_lock <std::mutex> lock(I_mutex);
        semMIS--;

        if (semMIS == 0) {
            //Insertion of indipendent set into mis
            std::cout << "A MIS is found" << endl;
            mis.insert(I);
            max_color++;
            graph.addColor(max_color);
            std::cout << "max_color=" << max_color<< endl;
            I.clear();

            semMIS = num_threads;
            mis_cond_var.notify_all();

        } else {

            std::cout << "Un thread in attesa" << endl;
            mis_cond_var.wait(lock);
        }

        std::cout << "RANGE [" <<from << ", " << to << "] ---> num_remain2= " <<  nodes_remain.size() << "     neighbor_size= " << neighbors.size()<< endl;

        if(num_remain< 5){

            auto it = nodes_remain.begin();
            while(it!= nodes_remain.end()){
                std::cout << "remain_vertex_id= " << *it << endl;
                it++;
            }
        }
        if(neighbors.size()<5){

            auto it= neighbors.begin();
            while(it!= neighbors.end()){
                std::cout << "remain_neighbor_id= " << *it << endl;
                it++;
            }
        }
        num_remain = neighbors.size();
        nodes_remain = neighbors;
        neighbors.clear();

    }

    return mis;
}






std::set< std::set<int>> Luby::find_MIS_Sequential(int from, int to,  std::set<std::set<int>> &mis, std::set<int> &I, vector<int> &assigned_vertices, std::set<int> nodes_remain, int num_remain,Graph temporaryGraph, int num_nodes){

    std::vector <Vertex> *verticesList = temporaryGraph.getVerticesList();

    //for the first iteration we choose the very first node
    int cur_node_id= verticesList->at(from).getId();
    I.insert(cur_node_id);

    while (!nodes_remain.empty()){

        std::cout <<"nodes_remain.size()= " << nodes_remain.size() << endl;

        while (num_remain > 0){

            std::vector <Vertex> neighborList;
            bool isMax;
            for(int i=from; i<to; i++){ //take the neighbor list of the considered cur_node
                if(verticesList->at(i).getId()==cur_node_id){
                    neighborList= verticesList->at(i).getNeighborList();
                    isMax= isMax_between_neighbor(verticesList->at(i), assigned_vertices);
                    break;
                }
            }


            if (isMax) {
                //vertex is inserted into the set
                I_mutex.lock();
                I.insert(cur_node_id);
                assigned_vertices.at(cur_node_id) = -1;       //the next iteration it won't be the max
                I_mutex.unlock();

                remainingNode_mutex.lock();
                for (auto &j : neighborList) { //for each neighbor of that node
                    // removing current node's neighbors (but only if they're still in nodes_remain)
                    if (nodes_remain.find(j.getId()) != nodes_remain.end()) {
                        num_remain--;
                        nodes_remain.erase(j.getId());
                    }
                }

                // remove current node
                nodes_remain.erase(cur_node_id);
                num_remain--;
                // choose the first element as new current node
                if (!nodes_remain.empty()) {
                    cur_node_id = *(nodes_remain.begin());
                }
                remainingNode_mutex.unlock();

            }

        }

        //at this point a MIS is found
        std::unique_lock<std::mutex> lk(I_mutex);
        semMIS--;

        if(semMIS==0){
            //Insertion of indipendent set into mis
            //std::cout<< "semMis1= " << semMIS << endl;
            mis.insert(I);
            I.clear();

            semMIS= num_threads;
            mis_cond_var.notify_all();

        } else{

            //std::cout<< "semMis2= " << semMIS << endl;
            //std::cout << "Un thread in attesa" << endl;
            mis_cond_var.wait(lk);
        }

        std::cout<< "numremain4= " << num_remain << ",  nodes_remain.empty()= " << nodes_remain.empty() << endl;


        if(!nodes_remain.empty()){
            cur_node_id = *(nodes_remain.begin());
            I.insert(cur_node_id);
        }

    }

    return mis;

}


void Luby::assign_num_to_vertices(int from, int to, std::vector<int> &assigned_vertices, Graph &graph) {

    std::vector <Vertex> vertices = *graph.getVerticesList();
    //permutation of id numbers
    srand(time(0));
    //std::shuffle(vertices.begin(), vertices.end(), 123);

    for (int i = from; i < to; i++) {
        //assigned_vertices[i]= vertices.at(i).getId();
        assigned_vertices[i] = rand();
    }
}

bool Luby::isMax_between_neighbor(Vertex v, std::vector<int> &assigned_vertices) {

    std::vector <Vertex> neighbor = v.getNeighborList();
    int value = assigned_vertices[v.getId()];
    int neighbor_id;

    for (int i = 0; i < neighbor.size(); i++) {

        neighbor_id = neighbor.at(i).getId();

        if (assigned_vertices.at(neighbor_id) > value) {
            //found a neighbor with higher value
            return false;

        } else if (assigned_vertices.at(neighbor_id) == value) {
            //if they have the same random value look at the id
            if (neighbor_id > v.getId()) {
                return false;
            }
        }
    }
    //if we're at this point, we've not found a neighbor
    // with a major rand value
    return true;
}

//This function colors all the vertex in the set I with the same color,
//finding them in the graph
void Luby::color_MIS(std::set<int> I, int color, Graph &graph) {

    int vert_id;
    std::vector <Vertex> *verticesList = graph.getVerticesList();

    while (!I.empty()) {

        vert_id = *I.begin();

        for (int i = 0; i < graph.num_vertices(); i++) {

            if (verticesList->at(i).getId() == vert_id) {
                //vertex coloring
                graph.colorVertex(&verticesList->at(i), color);
                break;
            }
        }

        I.erase(vert_id);
    }

}


std::string Luby::name() const {
    return "Luby (" + std::to_string(num_threads) + " threads),";
};