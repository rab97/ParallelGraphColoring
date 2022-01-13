cmake_minimum_required(VERSION 3.14)
project(ParallelGraphColoring)

set(CMAKE_CXX_STANDARD 14)

add_executable(parallelGraphColoring main.cpp classes/Vertex.cpp classes/Graph.cpp algorithms/Greedy.cpp)

