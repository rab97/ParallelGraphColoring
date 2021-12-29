cmake_minimum_required(VERSION 3.20)
project(ParallelGraphColoring)

set(CMAKE_CXX_STANDARD 17)

add_executable(ParallelGraphColoring main.cpp classes/Vertex.h classes/Vertex.cpp classes/Graph.h classes/Graph.cpp
        parse/Parser.h parse/Parser.cpp parse/DimacsParser.h parse/DimacsParser.cpp parse/Dimacs10Parser.h parse/Dimacs10Parser.cpp main.cpp)
