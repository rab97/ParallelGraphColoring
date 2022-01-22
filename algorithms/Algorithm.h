//
// Created by rab97 on 30/12/21.
//

#ifndef PARALLELGRAPHCOLORING_ALGORITHM_H
#define PARALLELGRAPHCOLORING_ALGORITHM_H

#include "../classes/Graph.h"

class Algorithm {
public:
    virtual ~Algorithm() {};

    virtual void algorithmSolver(Graph &) = 0;

    virtual std::string name() const = 0;
};

#endif //PARALLELGRAPHCOLORING_ALGORITHM_H
