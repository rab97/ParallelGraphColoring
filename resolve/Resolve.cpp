//
// Created by rab97 on 12/01/22.
//

#include "Resolve.h"
#include "../algorithms/SDL.h"
#include "../algorithms/Sequential.h"
#include "../algorithms/SDL.h"

#include <chrono>

Resolve::Resolve(Graph &g) : algorithms(
        {new Sequential(), new SDL(1), new SDL(2), new SDL(4), new SDL(8)}), graph(g) {}

void Resolve::res() {
    for (Algorithm *a: algorithms) {
        struct result res = run_one(a);
        std::cout << "algorithm_name: " << a->name();
        printf(", time_elapsed: %.2f ms, num_colors: %d \n\n",
               res.milliseconds,
               res.num_colors);
        delete a;
    }
}

struct result Resolve::run_one(Algorithm *algorithm) {
    auto t1 = std::chrono::high_resolution_clock::now();
    algorithm->algorithmSolver(graph);
    auto t2 = std::chrono::high_resolution_clock::now();

    int num_colors = graph.getNumColors();
    double milliseconds = std::chrono::duration<double, std::milli>(t2 - t1).count();
    graph.deleteGraphColors();

    return {num_colors, milliseconds};
}

