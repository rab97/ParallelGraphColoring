//
// Created by rab97 on 28/12/21.
//

#ifndef PARALLELGRAPHCOLORING_PARSER_H
#define PARALLELGRAPHCOLORING_PARSER_H


#include <string>
#include <fstream>
#include <iostream>
#include "../classes/Graph.h"

// Parser interface
class IParser {
public:
    virtual ~IParser() = default;

    virtual Graph parse() = 0;
};

class Parser {
    IParser *parser;
public:
    Parser(const std::string &fname);

    ~Parser();

    Graph parse();
};


#endif //PARALLELGRAPHCOLORING_PARSER_H
