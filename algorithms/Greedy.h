//
// Created by marta on 21/12/21.
//

#ifndef PARALLELGRAPHCOLORING_GREEDY_H
#define PARALLELGRAPHCOLORING_GREEDY_H

#include "../classes/Graph.h"

using namespace std;

class Greedy {

private:
    int num_threads;

public:
    Greedy();
    Greedy(int numThreads);

    int getNumThreads();
    void setNumThreads(int numThreads);

    void runSimpleGreedy(Graph *graph);

};



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


 * */

#endif //PARALLELGRAPHCOLORING_GREEDY_H
