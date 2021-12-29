//
// Created by rab97 on 28/12/21.
//

#include "Parser.h"
#include "Dimacs10Parser.h"
#include "DimacsParser.h"
#include <filesystem>

Parser::Parser(const std::string &fname) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening " + fname + " file!");
    }

    auto path = std::filesystem::path(fname);

    if (path.extension() == ".graph") {
        parser = new Dimacs10Parser(file);
    } else if (path.extension() == ".gra") {
        parser = new DimacsParser(file);
    }
}

Parser::~Parser() {
    delete parser;
}

Graph Parser::parse() {
    return parser->parse();
}
