//
// Created by marta on 17/12/21.
//

#ifndef PARALLELGRAPHCOLORING_GRAPH_H
#define PARALLELGRAPHCOLORING_GRAPH_H

#include "Vertex.h"

using namespace std;

class Graph {

private:

    vector<int> colors;
    vector <Vertex> verticesList;

public:

    Graph();
    //Graph(vector<Vertex> vertices);

    vector<int> getColors();

    int getNumColors();

    void addColor(int newColor);

    vector <Vertex> *getVerticesList();

    int num_vertices();

    void addVertex(Vertex newVertex);

    void colorVertex(Vertex *v, int c);

    void pairNeighbors(Vertex *v1, Vertex *v2);

    void printGraph();

};


#endif //PARALLELGRAPHCOLORING_GRAPH_H
