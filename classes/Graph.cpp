//
// Created by marta on 17/12/21.
//
#include <iostream>
#include <set>
#include <unordered_set>
#include "Graph.h"

Graph::Graph(int num_vertices) : colors(num_vertices) {}

/*
Graph(vector<Vertex> vertices){

}*/

void Graph::printGraph(){

    int size= getVerticesList()->size();
    for(int i=0; i<size; i++){
        getVerticesList()->at(i).printVertex();
    }
}


vector<int> Graph::getColors() {
    return colors;
}

int Graph::getNumColors() {
    return unordered_set<int>(this->colors.cbegin(), this->colors.cend()).size();
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

int Graph::assign_color(Vertex v) {
    std::set<int> neighbor_colors;
    for (Vertex n: v.getNeighborList()) {
        neighbor_colors.emplace(colors[n.getId()]);
    }

    int min_color = 0;
    for (int n_color: neighbor_colors) {
        if (min_color != n_color)
            break;
        else
            min_color++;
    }
    colors[v.getId()] = min_color;
    return min_color;
}

void Graph::deleteGraphColors() {
    for (int i = 0; i < num_vertices(); i++)
        colors[i] = 0;
}

Graph::Graph() {

}
