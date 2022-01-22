//
// Created by rab97 on 13/01/22.
//

#include "Sequential.h"
#include <numeric>
#include <algorithm>

#define RANDOM_SEED 123


Sequential::Sequential() : random(RANDOM_SEED) {}

void Sequential::algorithmSolver(Graph &graph) {
    std::vector<int> permutation(graph.num_vertices());
    std::iota(permutation.begin(), permutation.end(), 0);
    std::shuffle(permutation.begin(), permutation.end(), random);
    std::vector <Vertex> *verticesList = graph.getVerticesList();
    for (int i: permutation) {
        graph.assign_color(verticesList->at(i));
    }
}

std::string Sequential::name() const {
    return "Sequential";
}
