//
// Created by rab97 on 29/12/21.
//

#include "classes/Graph.h"

#include "parse/Parser.h"
#include "resolve/Resolve.h"

int main(int argc, char **argv) {
    std::vector <std::string> args(argv, argv + argc);
    if (args.size() < 2) {
        throw std::runtime_error("Error number of args!");
    }

    Parser p(args.back());
    Graph graph = p.parse();
    Resolve res(graph);
    res.res();

    return 0;
}
