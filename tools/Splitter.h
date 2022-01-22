//
// Created by rab97 on 12/01/22.
//

#ifndef PARALLELGRAPHCOLORING_SPLITTER_H
#define PARALLELGRAPHCOLORING_SPLITTER_H

#include "span.hpp"
#include <vector>
#include <cmath>

class Splitter {
    int max;
    int items_per_range;

public:
    Splitter(int max, int num_ranges) : max(max) {
        items_per_range = std::ceil(float(max) / float(num_ranges));
    };

    inline int get_min(int index) const {
        return std::min(items_per_range * index, max);
    };

    inline int get_max(int index) const {
        return std::min(items_per_range * (index + 1), max);
    };

    inline bool is_empty(int index) const {
        return get_min(index) == get_max(index);
    };;
};

template<typename T>
class VectorSplitter {
    Splitter s;
    std::vector <T> &vector;

public:
    VectorSplitter(std::vector <T> &vector, int num_ranges) : s(vector.size(), num_ranges), vector(vector) {};

    // Get the i-th range
    nonstd::span<T> get(int index) {
        if (s.is_empty(index))
            return nonstd::span<T>();
        return nonstd::span<T>(vector.begin() + s.get_min(index), vector.begin() + s.get_max(index));
    };
};

#endif //PARALLELGRAPHCOLORING_SPLITTER_H
