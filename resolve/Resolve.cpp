//
// Created by rab97 on 12/01/22.
//

#include "Resolve.h"
#include "../tools/OutputCsv.h"
#include "../tools/Memory.h"
#include "../algorithms/Sequential.h"
#include "../algorithms/SDL.h"
#include "../algorithms/LDF.h"
#include "../algorithms/Luby.h"

#include <chrono>

Resolve::Resolve(Graph &g) : algorithms(
        {new Sequential(),
         new LDF(1), new LDF(2), new LDF(4), new LDF(8),
         new SDL(1), new SDL(2), new SDL(4), new SDL(8),
         new Luby()
        }), graph(g) {}

Resolve::Resolve(Graph &g, std::string alg) : graph(g) {
    if (alg == "sequential") {
        algorithms.emplace_back(new Sequential());
    } else if (alg == "ldf") {
        algorithms.emplace_back(new LDF(1));
        algorithms.emplace_back(new LDF(2));
        algorithms.emplace_back(new LDF(4));
        algorithms.emplace_back(new LDF(8));
    } else if (alg == "sdl") {
        algorithms.emplace_back(new SDL(1));
        algorithms.emplace_back(new SDL(2));
        algorithms.emplace_back(new SDL(4));
        algorithms.emplace_back(new SDL(8));
    }
}

void Resolve::resolve_all(std::string path) {
    OutputCsv out("./outputs/" + path + ".csv");
    out.write_header();
    printf("\n");
    for (Algorithm *a: algorithms) {
        struct result res = run_one(a);
        out.write_line(res, a);
        std::cout << "algorithm_name: " << a->name();
        printf(", time_elapsed: %.2f ms, mem_usage: %.2f kB, num_colors: %d \n",
               res.milliseconds,
               res.mem_usage,
               res.num_colors);
        delete a;
    }
    printf("\n");
}

struct result Resolve::run_one(Algorithm *algorithm) {
    Memory memory_usage;
    auto t1 = std::chrono::high_resolution_clock::now();
    algorithm->algorithmSolver(graph);
    auto t2 = std::chrono::high_resolution_clock::now();
    double mem_usage = memory_usage.stop() / 1024;

    int num_colors = graph.getNumColors();
    double milliseconds = std::chrono::duration<double, std::milli>(t2 - t1).count();
    graph.deleteGraphColors();

    return {num_colors, milliseconds, mem_usage};
}

