//
// Created by marta on 17/12/21.
//

#ifndef PARALLELGRAPHCOLORING_GRAPH_H
#define PARALLELGRAPHCOLORING_GRAPH_H

#include "Vertex.h"
#include "../tools/span.hpp"
#include <set>

using namespace std;

class Graph {

private:

    vector<int> colors;
    vector <Vertex> verticesList;

public:

    Graph(int num_vertices);

    Graph();
    //Graph(vector<Vertex> vertices);

    vector<int> getColors();

    int getNumColors();

    void addColor(int newColor);

    vector <Vertex> *getVerticesList();

    int num_vertices();

    void deleteGraphColors();

    __attribute__((unused)) int assign_color(Vertex v);

    void addVertex(Vertex newVertex);

    void colorVertex(Vertex *v, int c);

    void pairNeighbors(Vertex *v1, Vertex *v2);

    void printGraph();

};


#endif //PARALLELGRAPHCOLORING_GRAPH_H
