#include <iostream>
#include <vector>

#include "classes/Vertex.h"
#include "classes/Graph.h"


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
        actualNode.printVertex();
    }

    cout<< vertList->at(3).printVertex();
    return 0;
}




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