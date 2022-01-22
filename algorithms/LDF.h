//
// Created by rab97 on 15/01/22.
//

#ifndef PARALLELGRAPHCOLORING_LDF_H
#define PARALLELGRAPHCOLORING_LDF_H

#include "../classes/Graph.h"
#include "Algorithm.h"

#include <vector>
#include <iostream>
#include <thread>
#include <algorithm>
#include <numeric>


class LDF : public Algorithm {
    int num_threads;

public:
    LDF(int num_threads);

    void algorithmSolver(Graph &);

    void color_vertices(int, int, Graph &);

    std::string name() const;
};


#endif //PARALLELGRAPHCOLORING_LDF_H
