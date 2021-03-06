//
// Created by marta on 17/12/21.
//
#include <iostream>
#include "Vertex.h"

Vertex::Vertex() {

};

Vertex::Vertex(int _id, int _color, vector <Vertex> _neighbors) {
    id = _id;
    color = _color;
    neighbors = _neighbors;
}

Vertex::Vertex(int _id){
    id= _id;
    color= -1;
    //default initialization for vector is empty
}

void Vertex::printVertex() {
    cout << "id= " << id << endl;
    cout << "color= " << this->color << endl;
    cout << "Neighbors are: [ ";
    for (int i = 0; i < neighbors.size(); i++) {
        cout << neighbors.at(i).getId() << ", ";
    }
    cout << "]" << endl;
}

int Vertex::getId() {
    return id;
}

int Vertex::getColor() {
    return color;
}

void Vertex::setColor(int newColor) {
    color = newColor;
}

vector <Vertex> Vertex::getNeighborList() {
    return neighbors;
}

void Vertex::addNeighbor(Vertex newNeighbor) {
    neighbors.push_back(newNeighbor);
}

int Vertex::getDegree() {
    return getNeighborList().size();
}

Vertex Vertex::getVertexNeighbor(int id) {
    std::vector <Vertex> n_list = getNeighborList();
    Vertex n;
    for (Vertex v: n_list) {
        if (v.getId() == id)
            n = v;
    }
    return n;
}

