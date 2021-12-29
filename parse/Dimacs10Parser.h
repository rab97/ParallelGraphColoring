//
// Created by rab97 on 28/12/21.
//

#ifndef PARALLELGRAPHCOLORING_DIMACS10PARSER_H
#define PARALLELGRAPHCOLORING_DIMACS10PARSER_H


#include <fstream>
#include <thread>
#include <vector>
#include "Parser.h"

class Dimacs10Parser : public IParser {
    std::ifstream file;

    static std::vector<int> parse_numbers(const std::string &line);

public:
    Dimacs10Parser(std::ifstream &);

    Graph parse();
};


#endif //PARALLELGRAPHCOLORING_DIMACS10PARSER_H
