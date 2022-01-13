//
// Created by rab97 on 29/12/21.
//

#include <iostream>
//#include <vector>

#include "classes/Graph.h"
<<<<<<< HEAD
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

=======
#include "parse/Parser.h"
#include "resolve/Resolve.h"
#include <set>

int main(int argc, char **argv) {
    std::vector <std::string> args(argv, argv + argc);
    if (args.size() < 2) {
        throw std::runtime_error("Error number of args!");
    }

//    int N = 4;
    Parser p(args.back());
    Graph graph = p.parse();

//    graph.getVerticesList()->at(0).setColor(1);
//    std::cout << graph.getVerticesList()->at(0).getColor();
//
//    for (Vertex v: graph.getVerticesList()->at(11).getNeighborList()) {
//        std::cout << "id: " << v.getId() << "color: " << v.getColor() << std::endl;
//    }

    Resolve res(graph);
    res.res();

//    graph.printGraph();




    //print the read graph
    //graph.printGraph();

//    for (int i = 1; i < N + 1; i++) {
//
//        Vertex v(i);
//        myGraph.addVertex(v);
//    }
//
//
//    vector <Vertex> *vertList = myGraph.getVerticesList();
//    Vertex actualNode, nextNode;
//
//    for (int i = 0; i < N - 1; i++) {
//        actualNode = vertList->at(i);
//        nextNode = vertList->at(i + 1);
//        myGraph.colorVertex(&actualNode, i);
//        myGraph.pairNeighbors(&actualNode, &nextNode);
//        actualNode.printVertex();
//    }
//
//    vertList->at(3).printVertex();
>>>>>>> 85b40b385c5fa35bb1e2492905ea985b08494c90
    return 0;
}



<<<<<<< HEAD
=======

/*
 * #include<bits/stdc++.h>
using namespace std;
int n,e,i,j;
vector<vector<int> > graph;
vector<int> color;
bool vis[100011];
void greedyColoring()
{
    color[0]  = 0;
    for (i=1;i<n;i++)
        color[i] = -1;
    bool unused[n];
    for (i=0;i<n;i++)
        unused[i]=0;
    for (i = 1; i < n; i++)
    {
        for (j=0;j<graph[i].size();j++)
            if (color[graph[i][j]] != -1)
                unused[color[graph[i][j]]] = true;
        int cr;
        for (cr=0;cr<n;cr++)
            if (unused[cr] == false)
                break;
        color[i] = cr;
        for (j=0;j<graph[i].size();j++)
            if (color[graph[i][j]] != -1)
                unused[color[graph[i][j]]] = false;
    }
}
int main()
{
    int x,y;
    cout<<"Enter number of vertices and edges respectively:";
    cin>>n>>e;
    cout<<"\n";
    graph.resize(n);
    color.resize(n);
    memset(vis,0,sizeof(vis));
    for(i=0;i<e;i++)
    {
        cout<<"\nEnter edge vertices of edge "<<i+1<<" :";
        cin>>x>>y;
        x--; y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    greedyColoring();
    for(i=0;i<n;i++)
    {
        cout<<"Vertex "<<i+1<<" is coloured "<<color[i]+1<<"\n";
    }
}
 * */
>>>>>>> 85b40b385c5fa35bb1e2492905ea985b08494c90
