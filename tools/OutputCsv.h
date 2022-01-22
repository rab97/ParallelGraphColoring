//
// Created by rab97 on 17/01/22.
//

#ifndef PARALLELGRAPHCOLORING_OUTPUTCSV_H
#define PARALLELGRAPHCOLORING_OUTPUTCSV_H

#include "../resolve/Resolve.h"
#include <iostream>
#include <fstream>

class OutputCsv {
    std::ofstream file;
public:
    OutputCsv(std::string filename) : file(filename) {};

    void write_header() {
        if (!file.is_open()) {
            std::runtime_error("Error file .csv is not opened!");
        }
        file << "name, time, mem_usage, num_colors" << std::endl;
    };

    void write_line(struct result res, Algorithm *a) {
        file << a->name() << ", " << res.milliseconds << ", " << res.mem_usage << ", " << res.num_colors
             << std::endl;
    }

    void close_file() {
        file.close();
    }
};

#endif //PARALLELGRAPHCOLORING_OUTPUTCSV_H
