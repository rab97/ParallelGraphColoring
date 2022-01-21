# ParallelGraphColoring

ParallelGraphColoring is a project focused on the implementation and analysis of sequential and parallel algorithms used
to color graphs.

The project is entirely written in c++.

# Introduction

In graph theory, graph coloring is a special case of graph labeling; it is an assignment of labels traditionally
called "colors" to elements of a graph subject to certain constraints. In its simplest form, it is a way of coloring the
vertices of a graph such that no two adjacent vertices are of the same color; this is called a vertex coloring.
Similarly, an edge coloring assigns a color to each edge so that no two adjacent edges are of the same color, and a face
coloring of a planar graph assigns a color to each face or region so that no two faces that share a boundary have the
same color.

Vertex coloring is often used to introduce graph coloring problems, since other coloring problems can be transformed
into a vertex coloring instance. For example, an edge coloring of a graph is just a vertex coloring of its line graph,
and a face coloring of a plane graph is just a vertex coloring of its dual. However, non-vertex coloring problems are
often stated and studied as-is. This is partly pedagogical, and partly because some problems are best studied in their
non-vertex form, as in the case of edge coloring.

The convention of using colors originates from coloring the countries of a map, where each face is literally colored.
This was generalized to coloring the faces of a graph embedded in the plane. By planar duality it became coloring the
vertices, and in this form it generalizes to all graphs. In mathematical and computer representations, it is typical to
use the first few positive or non-negative integers as the "colors". In general, one can use any finite set as the "
color set". The nature of the coloring problem depends on the number of colors but not on what they are.

# Main Design Choices

## Graph

The graph is implemented by means of two classes: Graph and Vertex. Each Vertex has as properties an id, a color and a
vector of other vertex, containing its neighbors. Because of this choice, we had decided that the explicit
implementation of the edges was not necessary, since the vertex are already linked together.

The Graph attributes are two vectors: the first one contais the colors progressively used and inserted by the running
algorithm, the second one is the full list of the vertices.

## Parsing

Parsing is implemented in two different ways according to the tipology of graph storage.

`Dimacs` and `Dimacs-10` formats are exploit. The extension file of the two format are `.gra` and `.graph` respectively.
The classes Dimacs10Parser and DimacsParser in the `parse/` directory implement the algorithm to generate graphs from
files.

### Parser

The two implemented parser are both a specialization of `Parser` class. Then the parser class implements the `IParser`
interface.

Parser job is to run the right parser according to the right extension of the given file (from the command line) and
give as result the parsed graph.

### DimacsParser

The `Dimacs` format stores graph with an adjacency list, the first line contains the number of vertices. Then for each
line there is the list of IDs neighbors for the i-th vertex. Each line terminates with `#`. Note that given two
neighbored vertices with IDs i and j, such that i < j, the neighborhood is explicitly shown only once in the list of
neighbors of the i-th vertex. So it is necessary to add i-th vertex as j-th neighbor. This make the algorithm much more
expensive in term of time and memory usage. There is an example of a `.gra` file and its content:

```
10
0: 3 8 5 #
1: 2 8 5 9 #
2: 8 5 #
3: 7 6 9 8 4 5 #
4: #
5: 7 9 8 6 #
6: 9 7 8 #
7: 8 9 #
8: 9 #
9: #
```

### Dimacs10Parser

The `Dimacs10` format stores gaph with an adjacency list, the first line contains the number of vertices and optionally
the number of edges (ignored due to the graph implementation). Then for each line there is the list of IDs neighbors for
the i-th vertex. Differently from the previous format the neighborhood is shown twice, so two near vertices appears in
both neighbors list. For this reason the algorithm is cheaper than the previous algorithm in term of memory usage and
time.

There is an example of `.graph` file and its content:

```
5 4
2 3
1 4
1 5
2
3 
```

## Parallelization

The main concept used in distributing the work within threads is the partition in range of the graph's vertex. Thanks to
the class `Splitter`, the graph is divided in a number of sets equal to the number of threads, and each thread is
assigned a specific range, in which perform the running algorithm.

This method avoids conflicts while using common data, and consequently reduces the need of complex synchronization
structures.

# Algorithms

All the algorithms are implemented as specialization classes of the `Algorithm` class. It declares two virtual methods:

* void algorithmSolver(Graph &);
* string name() const;

The algorithmSolver function must contain the full logic of that algorithm, to be triggered by the `Resolve` class. Each
class corresponding to an algorithm that can be run in parallel has a constructor to specify how many threads to launch.

# Project Structure

The projects is composed of several directories:

* `classes/`
* `parse/`
* `algorithms/`
* `resolve/`
* `tools/`

## Classes

Contains the definition of vertices (`Vertex.h/cpp`), and graph (`Graph.h/cpp`).

## Algorithms

Algorithms definition and implementation are exposed in the `algorithm/` folder.

### Sequential

The sequential algorithm implements the well-known greedy strategy shown in the document _A Comparison of Parallel Graph
Coloring Algorithms, J. R. Allwright, 1995_.

It is sequential, so it runs with a single thread. The algorithm consists of choosing a random permutation of the vertex
IDs. Then for each vertex assign the resulting permutation and color the vertex with the smallest color among its
neighbors. The smallest color is found and assigned through the following algorithm in the `Graph` class:

```
int Graph::assign_color(Vertex v) {
    std::set<int> neighbor_colors;
    for (Vertex n: v.getNeighborList()) {
        neighbor_colors.emplace(colors[n.getId()]);
    }

    int min_color = 0;
    for (int n_color: neighbor_colors) {
        if (min_color != n_color)
            break;
        else
            min_color++;
    }
    colors[v.getId()] = min_color;
    return min_color;
}
```

### Largest Degree First

The Largest Degree First algorithm implements the algorithm exposed in the document _A Comparison of Parallel Graph
Coloring Algorithms, J. R. Allwright, 1995_.

The algorithm chooses to color vertices considering their degrees. The coloring strategy priority is given to vertices
that have largest degrees. It is parallelized among the number of threads that are given and each thread job is to
assign colors to the subset of vertices it has to work on. The strategy is to assign the right color according to the
startegy described before.

### Smallest Degree Last

The Smallest Degree Last algorithm implements the algorithm exposed in the document _A Comparison of Parallel Graph
Coloring Algorithms, J. R. Allwright, 1995_.

The algorithm follows the same strategy adopted by the previous algorithm. But in this case it uses also weights to
decide wich vertex to color firstly.

The flow of the algorithm is composed of two phases:

1) `weighting phase`: find all the vertices with degree equal to the smallest degree in the graph. These vertices are
   assigned the current weight and then removed from the graph. The process is repeated until there are sets of vertices
   with a unique weight.
2) `coloring phase`: colors the sets provided from the previous step starting from the largest weight.

### MIS_Sequential

The class `MIS_Sequential.h/.ccp` implements the basic algorithm to find a maximal indipendent set in a graph, as it was
explained into the `allwrigth1995`. As the name suggest, this algorithm is sequential and no parallelism is provided.

Firstly, it is called the method find_MIS_Sequential to fully process the graph, and to insert all the indipendent set
in a variable <set< set< int>> mis. The indipendent sets are found by restricting the list of available vertices at each
iteration, deleting all the neighbors of the current vertex.

Once this process ends, the mis variable is explored and a color is assigned to each set using the function color_MIS.

Even if this algorithm works, we have decided to not include it into the results because it is very slow, and it is due
to the data structures we choose at the beginning of the project.

### Jones Plassman

### Luby

## Solver

## Experimental Evaluation

All the algorithms and the graph implementation are run and tested. The performace of each algorithm are evaluated
considering three properties:

* Time elapsed
* Memory usage
* Number of colors used

The running simulation was performed on a _AMD Ryzen 7 4800H, 2.9 GHz, 16 threads, 8 CPU cores_.

The results are exposed in the `outputs/` folder that contains a `.csv` file for each benchmark runned. Each file
contains the report in term of time elapsed, memory usage and number of colors used for each algorithm (togheter with
the number of threads).

Finally in the follow there is a description of the results obtained with several graph with different sizes and a
comparison between the different algorithm. The purpose of this simulation is to find the algorithm with the best
performance according to the properties written before.



