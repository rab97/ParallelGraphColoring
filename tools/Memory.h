//
// Created by rab97 on 15/01/22.
//

#ifndef PARALLELGRAPHCOLORING_MEMORY_H
#define PARALLELGRAPHCOLORING_MEMORY_H

#include <fstream>


class Memory {
    double tot_mem_usage, curr_mem_usage;

public:
    Memory();

    double calc_curr_mem_usage();

    double stop();
};


#endif //PARALLELGRAPHCOLORING_MEMORY_H
