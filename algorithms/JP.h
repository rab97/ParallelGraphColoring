//
// Created by marta on 17/01/22.
//

#ifndef PARALLELGRAPHCOLORING_JP_H
#define PARALLELGRAPHCOLORING_JP_H

#include <vector>
#include <set>
#include <thread>
#include <mutex>
#include <time.h>
#include <algorithm>
#include <iostream>

#include "../classes/Graph.h"
#include "Algorithm.h"
#include "../tools/Splitter.h"


class JP : public Algorithm {

private:

    int num_threads;

public:

    JP(int num_threads);

    void algorithmSolver(Graph &);

    void assign_randomNum_to_vertices(int from, int to, std::vector<int> &assigned_vertices);

    void find_and_color_MIS(int from, int to, std::vector<int> &assigned_vertices, Graph &graph);

    bool isMax_between_neighbor(Vertex v, int id, std::vector<int> &assigned_vertices);

    std::string name() const;

};


#endif //PARALLELGRAPHCOLORING_JP_H
