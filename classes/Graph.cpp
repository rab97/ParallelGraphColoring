//
// Created by marta on 17/12/21.
//
#include <iostream>
#include "Graph.h"

Graph::Graph() {

}

/*
Graph(vector<Vertex> vertices){

}*/

<<<<<<< HEAD
void Graph::printGraph(){

    int size= getVerticesList()->size();
    for(int i=0; i<size; i++){
        getVerticesList()->at(i).printVertex();
    }
}

vector<int> Graph::getColors(){
=======
vector<int> Graph::getColors() {
>>>>>>> 85b40b385c5fa35bb1e2492905ea985b08494c90
    return colors;
}

int Graph::getNumColors() {
    return colors.size();
}

void Graph::addColor(int newColor) {
    colors.push_back(newColor);
}

vector <Vertex> *Graph::getVerticesList() {
    return &verticesList;
}

int Graph::num_vertices() {
    return verticesList.size();
}

void Graph::addVertex(Vertex newVertex) {
    verticesList.push_back(newVertex);
}

void Graph::colorVertex(Vertex *v, int c) {
    v->setColor(c);
}

//Double assignment into the neighbor vectors: v1 is v2's neighbor, v2 is v1's neighbor
void Graph::pairNeighbors(Vertex *v1, Vertex *v2) {
    v1->addNeighbor(*v2);
    v2->addNeighbor(*v1);
}

void Graph::printGraph() {
    std::cout << "Num vertices: " << num_vertices() << std::endl;
    std::vector <Vertex> *list = getVerticesList();
    for (int i = 0; i < list->size(); i++) {
        std::cout << "Vertex ";
        list->at(i).printVertex();
        std::cout << ": ";
        std::cout << std::endl;
    }
}
