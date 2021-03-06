//
// Created by marta on 15/01/22.
//

#ifndef PARALLELGRAPHCOLORING_LUBY_H
#define PARALLELGRAPHCOLORING_LUBY_H

#include <vector>
#include <set>
#include <thread>
#include <numeric>
#include <algorithm>
#include <mutex>

#include "../classes/Graph.h"
#include "Algorithm.h"
#include "../tools/Splitter.h"
#include <random>

class Luby : public Algorithm {

private:
    std::mt19937 random;
    int num_threads;

public:

    Luby();

    Luby(int num_threads);

    void algorithmSolver(Graph &);

    void find_MIS_Parallel(int from, int to, int &max_color, int &running_threads, std::set <std::set<int>> &mis,
                           std::set<int> &I, vector<int> &assigned_vertices, Graph &graph);

    bool isMax_between_neighbor(Vertex v, int id, std::vector<int> &assigned_vertices);

    std::string name() const;

};


#endif //PARALLELGRAPHCOLORING_LUBY_H
