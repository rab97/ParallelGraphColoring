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
    //graph.addColor(max_color);
    int running_threads= num_threads;

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
        threads.emplace_back(std::thread([&graph, &mis, &I, &assigned_vertices, &max_color, &running_threads,this, s, i]() {
            int from = s.get_min(i), to = s.get_max(i);

            assign_num_to_vertices(from, to, assigned_vertices, graph);
            find_MIS_Parallel(from, to, max_color, running_threads,mis, I, assigned_vertices, graph);
            std::cout << "arrivo qui0?" << endl;

        }));
        std::cout << "arrivo qui1?" << endl;
    }

    std::cout << "arrivo qui?  2" << endl;
    for (auto &thread: threads) {
        thread.join();
    }


/*
    auto it= mis.begin();

    while(it!=mis.end()) {

        for (int i = 0; i < num_threads; i++) {
            threads.emplace_back(
                    std::thread([&graph, &mis, &I, &assigned_vertices, &max_color, &running_threads, this, s, i]() {
                        int from = s.get_min(i), to = s.get_max(i);


                    }));
            std::cout << "arrivo qui3?" << endl;
        }


        it++;

    }
    /*
    std::cout << "arrivo qui?3" << endl;

    auto it= mis.begin();

    while(it!=mis.end()){

        std::cout << "dentro il while" << endl;

        threads.emplace_back(std::thread([&graph, &mis, &it, &max_color,this]() {

            max_color++;
            std::cout << "maxColor" << max_color<< endl;
            graph.addColor(max_color);

            color_MIS(*it, max_color, graph);

        }));

        it++;

    }*/






}






void Luby::find_MIS_Parallel(int from, int to, int &max_color,int &running_threads,std::set <std::set<int>> &mis, std::set<int> &I,
                                                 vector<int> &assigned_vertices, Graph &graph) {

    int num_remain = to - from;
    std::set<int> nodes_remain;
    std::set<int> neighbors;
    std::vector <Vertex> *verticesList = graph.getVerticesList();
    running_threads= num_threads;

    for(int i=from; i< to; i++) {
        nodes_remain.insert(verticesList->at(i).getId());
    }

    int cur_node_id;
    std::vector <Vertex> neighborList;

    while (num_remain >0) {

        for (int j = from; j < to; j++) {

            cur_node_id=  verticesList->at(j).getId();

            if (nodes_remain.find(cur_node_id) != nodes_remain.end()) {

                bool isMax= isMax_between_neighbor(verticesList->at(j), assigned_vertices);
                if(isMax){
                    //vertex is colored and inserted into the indipendent set
                    I_mutex.lock();
                    I.insert(cur_node_id);
                    //graph.colorVertex(&verticesList->at(j), max_color);
                    std::cout << "cur_node_id= " << cur_node_id << "    color= " << max_color << endl;
                    assigned_vertices.at(cur_node_id)= -1;       //the next iteration it won't be the max
                    I_mutex.unlock();

                    //remove neighbors from nodes_remain if they belong to the interval [from, to)
                    neighborList = verticesList->at(j).getNeighborList();
                    int neighbor_id;
                    for (int k = 0; k < neighborList.size(); k++) { //for each neighbor of that node

                        neighbor_id = neighborList.at(k).getId();


                            if (nodes_remain.find(neighbor_id) != nodes_remain.end()) {
                                num_remain--;
                                neighbors.insert(neighbor_id);
                                nodes_remain.erase(neighbor_id);
                            }
                    }

                    //remove cur_node_id from nodes_remain
                    num_remain--;
                    nodes_remain.erase(cur_node_id);

                }else{
                    neighbors.insert(cur_node_id);
                }

            }

        }


        //at this point a MIS is found
        std::unique_lock <std::mutex> lock(I_mutex);
        semMIS--;

        if (semMIS <= 0) {
            //Insertion of indipendent set into mis
            mis.insert(I);

            auto it= I.begin();
            while(it!= I.end()){

                std::cout << "I= " << max_color << "        node_in_I= " << *it << endl;
                it++;
            }

            max_color++;
            graph.addColor(max_color);
            std::cout << "max_color=" << max_color<< endl;

            I.clear();
            if(num_remain==0){
                running_threads--;
            }
            semMIS = running_threads;
            mis_cond_var.notify_all();

        } else {

            if(num_remain==0){
                running_threads--;
            }
            std::cout << "Un thread in attesa" << endl;
            mis_cond_var.wait(lock);
        }

        num_remain = neighbors.size();
        nodes_remain = neighbors;
        neighbors.clear();
        std::cout << "RANGE [ " << from << ", " << to << "]     nodes_remain= " << num_remain << endl;
        std::cout << "semMIS=" << semMIS << endl;

    }


    std::cout << "here"<< endl;

}


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