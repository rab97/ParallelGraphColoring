//
// Created by rab97 on 12/01/22.
//

#ifndef PARALLELGRAPHCOLORING_SDL_H
#define PARALLELGRAPHCOLORING_SDL_H

#include "../classes/Graph.h"
#include "Algorithm.h"

#include <iostream>

#include <algorithm>

#include <random>

#include <numeric>
#include <thread>
#include <vector>


class SDL : public Algorithm {
    int num_threads;

    std::vector<int> remaining_vertices;
public:
    SDL(int num_threads);

    void insert_weights(Graph &, std::vector<int> &, std::vector<int> &, int, int);

    void insert_colors(const std::vector<int> &, int, int, Graph &);

    void algorithmSolver(Graph &);

    std::string name() const;
};


#endif //PARALLELGRAPHCOLORING_SDL_H
