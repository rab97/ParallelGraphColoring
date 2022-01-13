//
// Created by rab97 on 13/01/22.
//

#ifndef PARALLELGRAPHCOLORING_SEQUENTIAL_H
#define PARALLELGRAPHCOLORING_SEQUENTIAL_H

#include "Algorithm.h"
#include <random>

class Sequential : public Algorithm {
    std::mt19937 random;

public:
    Sequential();

    void algorithmSolver(Graph &);

    std::string name() const;
};


#endif //PARALLELGRAPHCOLORING_SEQUENTIAL_H
