# ParallelGraphColoring

ParallelGraphColoring is a project focused on the implementation and analysis of sequential and parallel algorithms used
to color graphs.

The project is entirely written in c++.

## Introduction

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

## Main Design Choices

### Graph
The graph is implemented by means of two classes: Graph and Vertex.
Each Vertex has as properties an id, a color and a vector of other vertex, containing its neighbors.
Because of this choice, we had decided that the explicit implementation of the edges was not necessary, since the vertex are already linked together.

The Graph attributes are two vectors: the first one contais the colors progressively used and inserted by the running algorithm, the second one is the full list of the vertices.

### Parsing

### Parallelization

The main concept used in distributing the work within threads is the partition in range of the graph's vertex. Thanks to the class `Splitter`, the graph is divided in a number of sets equal to the number of threads, and each thread is assigned a specific range, in which perform the running algorithm.

This method avoids conflicts while using common data, and consequently reduces the need of complex synchronization structures.

### Algorithms

All the algorithms are implemented as specialization classes of the `Algorithm` class. It declares two virtual methods:
* void algorithmSolver(Graph &);
* string name() const;

The algorithmSolver function must contain the full logic of that algorithm, to be triggered by the `Resolve` class.
Each class corresponding to an algorithm that can be run in parallel has a constructor to specify how many threads to launch.


## Project Structure

The projects is composed of several directories:

* `classes/`
* `parse/`
* `algorithms/`
* `resolve/`
* `tools/`

### Classes

Contains the definition of vertices (`Vertex.h/cpp`), and graph (`Graph.h/cpp`).

### Algorithms

#####Sequential
#####Greedy
#####SDL
#####LDF



#####MIS_Sequential
The class MIS_Sequential.h/.ccp implements the basic algorithm to find a maximal indipendent set in a graph, as it was explained into the `allwrigth1995`. As the name suggest, this algorithm is sequential and no parallelism is provided.

Firstly, it is called the method find_MIS_Sequential to fully process the graph, and to insert all the indipendent set in a variable <set< set< int>> mis. The indipendent sets are found by restricting the list of available vertices at each iteration, deleting all the neighbors of the current vertex.

Once this process ends, the mis variable is explored and a color is assigned to each set using the function color_MIS.

Even if this algorithm works, we have decided to not include it into the results because it is very slow, and it is due to the data structures we choose at the beginning of the project.

#####Jones Plassman




#####Luby



## Experimental Evaluation

