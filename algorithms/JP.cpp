//
// Created by marta on 17/01/22.
//

#include "JP.h"

mutex color_mutex;

JP::JP(int num_threads) : num_threads(num_threads) {}

void JP::algorithmSolver(Graph & graph){

    int num_vertices= graph.num_vertices();

    std::vector<int> assigned_vertices(num_vertices+1, 0);

    std::cout << "num_threads= " << num_threads << endl;
    if (num_threads > std::thread::hardware_concurrency())
        throw std::runtime_error("Hardware concurrency exceeded: please use at most " +
                                 std::to_string(std::thread::hardware_concurrency()) + " threads");

    Splitter s(num_vertices, num_threads);
    std::vector <std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(std::thread([&graph, &assigned_vertices, this, s, i]() {
            int from = s.get_min(i), to = s.get_max(i);

            assign_randomNum_to_vertices(from, to, assigned_vertices, graph);

            find_and_color_MIS(from, to, assigned_vertices, graph);
        }));
    }

    for (auto &thread: threads) {
        thread.join();
    }

}


void JP::assign_randomNum_to_vertices(int from, int to, std::vector<int> & assigned_vertices, Graph graph){

    std::vector<Vertex> vertices= *graph.getVerticesList();
    srand(time(0));

    for(int i= from; i<to; i++){
        assigned_vertices[i]= rand();
    }

}



void JP::find_and_color_MIS(int from, int to, std::vector<int> & assigned_vertices, Graph &graph){

    int num_remain= to-from;
    std::set<int> nodes_remain;
    std::vector <Vertex> *verticesList = graph.getVerticesList();

    for(int i=0; i< num_remain; i++) {
        nodes_remain.insert(verticesList->at(i).getId());
    }

    int cur_node_id;
    int actual_color= 0;
    int while_num=0;

    while(!nodes_remain.empty()){

        for(int j=from; j<to; j++){

            cur_node_id=  verticesList->at(j).getId();
            //std:: cout << "cur_node_id= " << cur_node_id << endl;

            if(nodes_remain.find(cur_node_id) != nodes_remain.end()){

                bool isMax= isMax_between_neighbor(verticesList->at(j), assigned_vertices);
                if(isMax){
                    //vertex coloring
                    color_mutex.lock();
                    actual_color= graph.assign_color(verticesList->at(j));
                    //std::cout << "actual_color=" << actual_color << endl;
                    assigned_vertices.at(cur_node_id)= 0;       //the next iteration it won't be the max
                    color_mutex.unlock();
                    //remove it from nodes_remain
                    /*
                    if(num_remain==1){
                        break;
                    }*/
                    num_remain --;
                    //std::cout << "nodes_remain= " << num_remain << endl;
                    nodes_remain.erase(cur_node_id);

                    //std:: cout << "Colored node cur_node_id= " << cur_node_id << endl;

                }

            }

        }
        while_num++;
        //std::cout << "while_num= " << while_num << endl;
    }


}


bool JP::isMax_between_neighbor(Vertex v, std::vector<int>  &assigned_vertices) {

    std::vector<Vertex> neighbor = v.getNeighborList();
    int value= assigned_vertices[v.getId()];
    //std:: cout << "error here?" << endl;
    int neighbor_id;

    //std::cout << "neighbor_size= " << neighbor.size() <<endl;
    //std::cout << "assigned_vertices.size= " << assigned_vertices.size() <<endl;


    for(int i=0; i<neighbor.size(); i++){

        //std::cout << "neighbor_id= " << neighbor.at(i).getId() <<endl;
        neighbor_id= neighbor.at(i).getId();

        if(assigned_vertices.at(neighbor_id) > value) {
            //found a neighbor with higher value
            return false;

        }else if(assigned_vertices.at(neighbor_id) == value){
            //if they have the same random value look at the id
            if(neighbor_id > v.getId()){
                return false;
            }
        }
    }
    //if we're at this point, we've not found a neighbor
    // with a major rand value
    //std:: cout << "vertex " << v.getId() << "isMax. RandomNum= " << value << endl;
    return true;
}




std::string JP::name() const{
    return "JP (" + std::to_string(num_threads) + " threads)";
};