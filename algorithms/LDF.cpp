//
// Created by rab97 on 15/01/22.
//

#include "LDF.h"
#include "../tools/Splitter.h"

LDF::LDF(int num_threads) : num_threads(num_threads) {}

void LDF::algorithmSolver(Graph &graph) {
    if (num_threads > std::thread::hardware_concurrency())
        throw std::runtime_error("Hardware concurrency exceeded: please use at most " +
                                 std::to_string(std::thread::hardware_concurrency()) + " threads");
    Splitter s(graph.num_vertices(), num_threads);
    std::vector <std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(std::thread([i, &graph, this, s]() {
            int from = s.get_min(i), to = s.get_max(i);

            color_vertices(from, to, graph);
        }));
    }

    for (auto &thread: threads)
        thread.join();

    std::vector <Vertex> *verticesList = graph.getVerticesList();
    for (int vertex: remaining_vertices) {
        graph.assign_color(verticesList->at(vertex));
    }
}

void LDF::color_vertices(int from, int to, Graph &graph) {
    std::vector<int> vertices(to - from);
    std::iota(vertices.begin(), vertices.end(), from);
    std::vector <Vertex> *verticesList = graph.getVerticesList();

    std::stable_sort(vertices.begin(), vertices.end(), [&](int i, int j) {
        return verticesList->at(i).getDegree() > verticesList->at(i).getDegree();
    });

    for (const auto &vertex: vertices) {
        int my_color = graph.assign_color(verticesList->at(vertex));
        std::vector <Vertex> neighborsList = verticesList->at(vertex).getNeighborList();
        for (Vertex &neighbor: neighborsList) {
            if (my_color == neighbor.getColor()) {
                remaining_vertices.emplace_back(vertex);
                break;
            }
        }
    }
}

std::string LDF::name() const {
    return "LDF";
}
