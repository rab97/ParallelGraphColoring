//
// Created by rab97 on 28/12/21.
//

#include <sstream>
#include "Dimacs10Parser.h"

Dimacs10Parser::Dimacs10Parser(std::ifstream &_file) : file(std::move(_file)) {}

Graph Dimacs10Parser::parse() {
    std::string first_line;
    std::getline(file, first_line);
    int V;

    std::vector<int> nEV = parse_numbers(first_line);

    if (nEV.size() == 2) {
        V = nEV[0];
    } else {
        throw std::runtime_error("Unexpected first_line size!");
    }

    Graph g(V);
    for (int i = 0; i < V; i++) {
        Vertex v(i);
        std::string line;
        std::getline(file, line);
        std::vector<int> neighbours = parse_numbers(line);
        for (int n: neighbours) {
            v.addNeighbor(Vertex(n));
        }

        g.addVertex(v);
    }
    return g;
}

std::vector<int> Dimacs10Parser::parse_numbers(const std::string &line) {
    std::vector<int> res;
    std::istringstream line_str(line);
    std::string numb;
    while (std::getline(line_str, numb, ' ')) {
        int number = std::stoul(numb);
        res.emplace_back(number);
    }

    return res;
}


