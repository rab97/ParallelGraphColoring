cmake_minimum_required(VERSION 3.10)
project(ParallelGraphColoring)

link_libraries(stdc++fs)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(ParallelGraphColoring main.cpp classes/Vertex.h classes/Vertex.cpp classes/Graph.h classes/Graph.cpp parse/Parser.h
        parse/Parser.cpp parse/DimacsParser.h parse/DimacsParser.cpp parse/Dimacs10Parser.h parse/Dimacs10Parser.cpp main.cpp
        algorithms/Algorithm.h algorithms/SDL.cpp algorithms/SDL.h tools/Splitter.h resolve/Resolve.cpp resolve/Resolve.h
        algorithms/Sequential.cpp algorithms/Sequential.h algorithms/LDF.cpp algorithms/LDF.h algorithms/Luby.cpp algorithms/Luby.h tools/Memory.cpp tools/Memory.h tools/OutputCsv.h
        algorithms/JP.cpp algorithms/JP.h algorithms/MIS_Sequential.cpp algorithms/MIS_Sequential.h)
