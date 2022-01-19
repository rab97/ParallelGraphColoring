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

class Luby : public Algorithm{

private:

    int num_threads;
    std::vector<int> remaining_vertices;

public:

    Luby();
    Luby(int num_threads);

    void algorithmSolver(Graph &);
    std::set< std::set<int> > find_MIS_Parallel(int from, int to, int &max_color,std::set<std::set<int>> &mis, std::set<int>  &I, vector<int> &assigned_vertices,Graph &graph);
    std::set< std::set<int>> find_MIS_Sequential(int from, int to,  std::set<std::set<int>> &mis, std::set<int> &I, vector<int> &assigned_vertices, std::set<int> nodes_remain, int num_remain,Graph temporaryGraph, int num_nodes);
    void assign_num_to_vertices(int from, int to, std::vector<int> & assigned_vertices, Graph &graph);
    void color_MIS(std::set<int> I, int color, Graph &graph);
    bool isMax_between_neighbor(Vertex v, std::vector<int>  &assigned_vertices);

    std::string name() const;

};


#endif //PARALLELGRAPHCOLORING_LUBY_H
