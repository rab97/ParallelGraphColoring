# ParallelGraphColoring

ParallelGraphColoring is a project focused on the implementation and analysis pf sequential and parallel algorithms used to color graphs.

In the following section there is a short user guide useful to build and run the program correctly.

### Build and Run
Project can br built with `make`:

```
cmake .
make
```

To run the program:

```
ParallelGraphColoring [--run-all || --run-single] <graph_path> [options]
```

`--run-all`     -> executes all algorthms implemented for the specific graph

`--run-single`   -> executes one single algorithms speciified in the 'options' field for the specific graph

The `[options]` available are:
* `sequential` -> executes Sequential algorithm
* `ldf`-> executes Largest-Degree-First algorithm
* `sdl` -> executes Smallest-Degree-Last algorithm
* `jp` -> executes Jones-Plassmann algorithm
* `luby` -> executes Luby algorithm

A help menu is also available for the user, showing what explained before:
```
ParallelGraphColoring --help
```