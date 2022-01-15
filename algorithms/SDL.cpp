//
// Created by rab97 on 12/01/22.
//

#include "SDL.h"
#include "../tools/Splitter.h"

SDL::SDL(int num_threads) : num_threads(num_threads) {}

void SDL::algorithmSolver(Graph &graph) {
    int num_vertices = graph.num_vertices();

    std::vector<int> degrees(num_vertices, 0);
    vector<int> weights(num_vertices, 0);

    if (num_threads > std::thread::hardware_concurrency())
        throw std::runtime_error("Hardware concurrency exceeded: please use at most " +
                                 std::to_string(std::thread::hardware_concurrency()) + " threads");

    Splitter s(num_vertices, num_threads);

    std::vector <std::thread> threads;

    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(std::thread([&graph, &weights, &degrees, this, s, i]() {
            int from = s.get_min(i), to = s.get_max(i);
            insert_weights(graph, degrees, weights, from, to);

            insert_colors(degrees, from, to, graph);
        }));
    }

    for (auto &thread: threads) {
        thread.join();
    }

    std::vector <Vertex> *verticesList = graph.getVerticesList();
    for (int vertex: remaining_vertices) {
        graph.assign_color(verticesList->at(vertex));
    }
}

void SDL::insert_weights(Graph &graph, std::vector<int> &degrees, std::vector<int> &weights, int from, int to) {
    vector <Vertex> *verticesList = graph.getVerticesList();
    for (int i = from; i < to; i++) {
        degrees[i] = verticesList->at(i).getDegree();
    }

    int max_degree = 0;
    for (int i = from; i < to; i++) {
        max_degree = std::max(max_degree, degrees[i]);
    }

    int curr_weight = 1;
    int curr_degree = 0;

    while (curr_degree <= max_degree) {
        for (int i = from; i < to; i++) {
            if (degrees[i] <= curr_degree && degrees[i] >= 0) {
                weights[i] = curr_weight;
                degrees[i] = -1;
                for (Vertex neighbor: verticesList->at(i).getNeighborList()) {
                    if (degrees[neighbor.getId()] > 0) {
                        degrees[neighbor.getId()]--;
                    }
                }
            }
        }
        curr_weight++;
        curr_degree++;
    }
}

void SDL::insert_colors(const std::vector<int> &weights, int from, int to, Graph &graph) {
    std::vector <Vertex> *verticesList = graph.getVerticesList();
    /* Create a vector to represent the vertices to be colored in order and initialize it in ascending order */
    std::vector<int> vertices_to_color(to - from);
    std::iota(vertices_to_color.begin(), vertices_to_color.end(), from);

    /* Sort the vector by weight */
    std::stable_sort(vertices_to_color.begin(), vertices_to_color.end(), [&](int i, int j) {
        return weights[i] > weights[j];
    });

    /* start coloring according to the order assigned above where no two neighbors have the same color */
    for (const auto &vertex_to_color: vertices_to_color) {
        int my_color = graph.assign_color(verticesList->at(vertex_to_color));
        std::vector <Vertex> neighborsList = verticesList->at(vertex_to_color).getNeighborList();
        for (Vertex &neighbor: neighborsList) {
            if (my_color == neighbor.getColor()) {
                remaining_vertices.emplace_back(vertex_to_color);
                break;
            }
        }
    }
}

std::string SDL::name() const {
    return "SDL (" + std::to_string(num_threads) + " threads)";
}


