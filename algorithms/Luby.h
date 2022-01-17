//
// Created by marta on 15/01/22.
//

#ifndef PARALLELGRAPHCOLORING_LUBY_H
#define PARALLELGRAPHCOLORING_LUBY_H

#include <vector>
#include <set>
#include <thread>
#include <algorithm>

#include "../classes/Graph.h"
#include "Algorithm.h"
#include "../tools/Splitter.h"

class Luby : public Algorithm{

private:

    int num_threads;
    std::vector<int> remaining_vertices;

public:

    Luby();
    //Luby(int num_threads);

    void algorithmSolver(Graph &);
    std::set< std::set<int> > find_MIS(Graph temporaryGraph, int num_nodes);
    void color_MIS(std::set<int> I, int color, Graph &graph);

    std::string name() const;

};


#endif //PARALLELGRAPHCOLORING_LUBY_H
