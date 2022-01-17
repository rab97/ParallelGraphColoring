//
// Created by rab97 on 29/12/21.
//

#include <sstream>
#include "DimacsParser.h"
#include "../classes/Vertex.h"
#include "../classes/Graph.h"

DimacsParser::DimacsParser(std::ifstream &_file) : file(std::move(_file)) {

}

Graph DimacsParser::parse() {
    std::string first_line;
    std::getline(file, first_line);
    int V = std::stoul(first_line);

    Graph g(V);
    for (int i = 0; i < V; i++) {
        Vertex v(i + 1);
        std::string line;
        std::getline(file, line);
        std::vector<int> neighbours = parse_numbers(line);
        for (int n: neighbours) {
            v.addNeighbor(Vertex(n + 1));
        }
        g.addVertex(v);
    }
    return g;
}

std::vector<int> DimacsParser::parse_numbers(const std::string &line) {
    std::vector<int> res;
    std::istringstream line_str(line);
    std::string numb;
    std::getline(line_str, numb, ' ');
    while (std::getline(line_str, numb, ' ')) {
        if (numb == "#")
            break;
        int number = std::stoul(numb);
        res.emplace_back(number);
    }

    return res;
}

