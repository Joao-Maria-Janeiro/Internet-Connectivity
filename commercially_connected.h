#ifndef _COMCONNECTED_H
#define _COMCONNECTED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice_handler.h"
#include "graph_handler.h"

int findTier0(Graph *graph, int * tier0Nodes);
int commerciallyConnected(Graph *graph, int* tier0Ndes, int tier0Count);
int  tier0AllCon(Graph *graph, int *tier0Nodes, int tier0Count);
int * bfsTier0(Graph *graph, int startVertex, int* visited );
void findAllCycles(Graph* graph, int u, int parent, int visited[], int marked[], int parents[], int *cyclenumber);
void printCycles(int listSize, int marked[], int cyclenumber);
// int findLeaf(Graph *graph);
// void dfsLeaf(struct Graph* graph, int startVertex, int prevMove, int sideways, int *visited);


#endif 