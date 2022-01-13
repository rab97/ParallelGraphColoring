//
// Created by marta on 21/12/21.
//
#include <iostream>
#include "Greedy.h"

Greedy::Greedy(){

};

Greedy::Greedy(int numThreads){
    num_threads= numThreads;
}

int Greedy::getNumThreads(){
    return num_threads;
}

void Greedy::setNumThreads(int numThreads){
    num_threads= numThreads;
}

/*Rendiamo Greedy Friend di Graph così che possa accedere direttamente agli attributi o usiamo
 * i metodi get?*/

//Implementation of Greedy Algorithm without threads
void Greedy::runSimpleGreedy(Graph *graph){

    graph->addColor(0);
    vector<Vertex>* vertexList= graph->getVerticesList();
    int graphSize= vertexList->size();
    int graphNumColors= graph->getNumColors();

    //For each vertex in the graph
    for(int i=0; i < graphSize; i++){

        //Allocate a temporary vector containing possible neighbors colors
        //and initialize all its values to false
        bool neighborColors[graphNumColors];
        for(int j=0; j < graphNumColors; j++){
            neighborColors[j]= false;
        }

        //Verify neighbors colors and set to true the used ones
        Vertex currentVertex= vertexList->at(i);
        vector<Vertex> currentNeighbor= currentVertex.getNeighborList();

        int tempColor;
        for(int k=0; k< currentNeighbor.size(); k++){

            tempColor= currentNeighbor.at(k).getColor();

            if(tempColor==-1){ //Neighbor without color
                continue;
            } else{
                neighborColors[tempColor]= true;
            }
        }

        //Assign the smallest free color to the current vertex if possible,
        //add a new color in the list otherwise
        int candidateColor= 0;
        while( neighborColors[candidateColor] and candidateColor< graph->getNumColors()){
            cout << "candidateColor= " << candidateColor << endl;
            candidateColor++;
        }

        /*
        if(!neighborColors[candidateColor]){
            cout << "Found a color for Vertex " << currentVertex.getId() << " = " << candidateColor << endl;
        }*/

        if(candidateColor== graph->getNumColors()-1){
            cout << "A new color is needed;" << endl;
            candidateColor++;
            graph->addColor(candidateColor);
        }

        graph->colorVertex(&currentVertex, candidateColor);
        cout << "Color for Vertex " << currentVertex.getId() << " = " << candidateColor << endl;

    }

    //END OF THE GRAPH
    cout << "The graph is fully colored" << endl;

}