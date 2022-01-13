#include <iostream>
#include <vector>

#include "classes/Vertex.h"
#include "classes/Graph.h"
#include "algorithms/Greedy.h"


using namespace std;

int main() {

    int N= 4;
    cout << "Hello, World!"<< endl;
    Graph myGraph;

    for(int i=1; i<N+1; i++){
        Vertex v(i);
        myGraph.addVertex(v);
    }


    vector<Vertex>* vertList= myGraph.getVerticesList();
    Vertex actualNode, nextNode;

    for(int i=0; i<N-1; i++){
        actualNode= vertList->at(i);
        nextNode= vertList->at(i+1);
        myGraph.colorVertex(&actualNode, i);
        myGraph.pairNeighbors(&actualNode, &nextNode);
        //actualNode.printVertex();
    }

    myGraph.printGraph();

    Greedy greedy;
    greedy.runSimpleGreedy(&myGraph);

    return 0;
}



