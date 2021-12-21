//
// Created by marta on 17/12/21.
//

#ifndef PARALLELGRAPHCOLORING_VERTEX_H
#define PARALLELGRAPHCOLORING_VERTEX_H

#include <vector>

using namespace std;

class Vertex {

private:

    int id;
    int color;
    vector<Vertex> neighbors;

public:
    Vertex();
    Vertex(int _id, int _color, vector<Vertex> _neighbors);
    Vertex(int _id);

    void printVertex();

    int getId();

    int getColor();
    void setColor(int newColor);

    vector<Vertex> getNeighborList();
    void addNeighbor(Vertex newNeighbor);
};


#endif //PARALLELGRAPHCOLORING_VERTEX_H
