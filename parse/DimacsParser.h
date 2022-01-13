//
// Created by rab97 on 29/12/21.
//

#ifndef PARALLELGRAPHCOLORING_DIMACSPARSER_H
#define PARALLELGRAPHCOLORING_DIMACSPARSER_H

#include "Parser.h"

class DimacsParser : public IParser {
    std::ifstream file;

    static std::vector<int> parse_numbers(const std::string &line);

public:
    DimacsParser(std::ifstream &);

    Graph parse();
};


#endif //PARALLELGRAPHCOLORING_DIMACSPARSER_H
