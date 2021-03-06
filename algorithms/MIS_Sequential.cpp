//
// Created by marta on 18/01/22.
//
#include <iostream>

#include "MIS_Sequential.h"


MIS_Sequential::MIS_Sequential() = default;

void MIS_Sequential::algorithmSolver(Graph & graph){

    std::set<std::set<int>> mis= find_MIS_Sequential(graph, graph.num_vertices());

    auto it= mis.begin();
    int max_color= 0;

    while(it!=mis.end()){

        max_color++;
        graph.addColor(max_color);

        color_MIS(*it, max_color, graph);
        it++;
    }

}

std::set< std::set<int>> MIS_Sequential::find_MIS_Sequential(Graph temporaryGraph, int num_nodes){

    std::set< std::set<int> > mis;
    std::set<int> I;

    int num_remain = num_nodes;
    std::set<int> nodes_remain;
    std::set<int> neighbors;

    std::vector <Vertex> *verticesList = temporaryGraph.getVerticesList();

    for(int i=0; i< num_nodes; i++){
        nodes_remain.insert(verticesList->at(i).getId());
    }

    //for the first iteration we choose the very first node
    int cur_node_id= verticesList->at(0).getId();
    I.insert(cur_node_id);

    while (!nodes_remain.empty()){

        while (num_remain > 0){

            std::vector <Vertex> neighborList;


            for(int i=0; i<num_nodes; i++){ //take the neighbor list of the considered cur_node
                if(verticesList->at(i).getId()==cur_node_id){
                    neighborList= verticesList->at(i).getNeighborList();
                    break;
                }
            }


            for(auto & j : neighborList){ //for each neighbor of that node
                // removing current node's neighbors (but only if they're still in nodes_remain)
                if (nodes_remain.find(j.getId()) != nodes_remain.end()) {
                    num_remain--;
                    neighbors.insert(j.getId());
                    nodes_remain.erase(j.getId());
                }
            }

            // remove current node
            nodes_remain.erase(cur_node_id);
            num_remain--;
            // choose the first element as new current node, insert
            if(!nodes_remain.empty()){
                cur_node_id = *(nodes_remain.begin());
                I.insert(cur_node_id);
            }

        }

        //at this point a MIS is found
        mis.insert(I);
        I.clear();
        num_remain = neighbors.size();
        nodes_remain = neighbors;

        if(!nodes_remain.empty()){
            cur_node_id = *(nodes_remain.begin());
            I.insert(cur_node_id);
        }
        neighbors.clear();

    }

    return mis;
}


//This function colors all the vertex in the set I with the same color,
//finding them in the graph
void MIS_Sequential::color_MIS(std::set<int> I, int color, Graph &graph){

    int vert_id;
    std::vector <Vertex> *verticesList = graph.getVerticesList();

    while(!I.empty()){

        vert_id= *I.begin();

        for(int i=0; i<graph.num_vertices(); i++){

            if(verticesList->at(i).getId()==vert_id){
                //vertex coloring
                graph.colorVertex(&verticesList->at(i), color);
                break;
            }
        }

        I.erase(vert_id);
    }

}


std::string MIS_Sequential::name() const{

    return "MIS_Sequential";
}