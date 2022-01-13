cmake_minimum_required(VERSION 3.14)
project(ParallelGraphColoring)

set(CMAKE_CXX_STANDARD 17)

<<<<<<< HEAD
add_executable(parallelGraphColoring main.cpp classes/Vertex.cpp classes/Graph.cpp algorithms/Greedy.cpp)

=======
add_executable(ParallelGraphColoring main.cpp classes/Vertex.h classes/Vertex.cpp classes/Graph.h classes/Graph.cpp
        parse/Parser.h parse/Parser.cpp parse/DimacsParser.h parse/DimacsParser.cpp parse/Dimacs10Parser.h parse/Dimacs10Parser.cpp main.cpp)
>>>>>>> 85b40b385c5fa35bb1e2492905ea985b08494c90
