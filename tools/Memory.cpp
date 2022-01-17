//
// Created by rab97 on 15/01/22.
//

#include "Memory.h"
#include <unistd.h>
#include <iostream>

Memory::Memory() : tot_mem_usage(0), curr_mem_usage(calc_curr_mem_usage()) {}

double Memory::calc_curr_mem_usage() {
    std::ifstream mem("/proc/self/statm");
    double m;
    for (int i = 0; i < 5; i++)
        mem >> m;
    mem >> m;

    return m * sysconf(_SC_PAGE_SIZE);
}

double Memory::stop() {
    tot_mem_usage = calc_curr_mem_usage();
    return tot_mem_usage - curr_mem_usage;
}

