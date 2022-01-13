//
// Created by rab97 on 12/01/22.
//

#ifndef PARALLELGRAPHCOLORING_RESOLVE_H
#define PARALLELGRAPHCOLORING_RESOLVE_H

#include "../classes/Graph.h"
#include "../algorithms/Algorithm.h"

struct result {
    int num_colors;
    double milliseconds;
};

class Resolve {
    Graph graph;

    std::vector<Algorithm *> algorithms;

    struct result run_one(Algorithm *);

public:
    Resolve(Graph &);

    void res();
};


#endif //PARALLELGRAPHCOLORING_RESOLVE_H
