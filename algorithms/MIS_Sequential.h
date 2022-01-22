//
// Created by marta on 18/01/22.
//

#ifndef PARALLELGRAPHCOLORING_MIS_SEQUENTIAL_H
#define PARALLELGRAPHCOLORING_MIS_SEQUENTIAL_H

#include <vector>
#include <set>
#include <algorithm>

#include "../classes/Graph.h"
#include "Algorithm.h"
#include "../tools/Splitter.h"

class MIS_Sequential : public Algorithm{

public:
    MIS_Sequential();

    void algorithmSolver(Graph &);

    std::set< std::set<int> > find_MIS_Sequential(Graph temporaryGraph, int num_nodes);
    void color_MIS(std::set<int> I, int color, Graph &graph);
    std::string name() const;

};


#endif //PARALLELGRAPHCOLORING_MIS_SEQUENTIAL_H
