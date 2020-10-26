#ifndef _MATRICE_H
#define _MATRICE_H

#include "file_handler.h"

typedef struct Edge {
    int u; //index of u
    int v; //index of v
} Edge;


int graphIsConnected(Graph * graph);
struct queue* createQueue(int n);
int * bfs(Graph * graph, int startVertex);
void enqueue(struct queue* q, int value, int n);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);

void bridges(Graph* g);
int min(int a,int b);
int bridgesUtil(Graph *g, int uIndex, int* isVisited, int* d,int* parent,int* l, Edge *bridgesArray);

int isCommerciallyCyclic (Graph * graph);
void isCommerciallyCyclicUtil(Graph * graph, int v, int * visited, int parent, int * cycleVertices, int * cycleFoundFlag, int * cycleFinished, int * firstNode);


int findTier0(Graph *graph, int * tier0Nodes);
int commerciallyConnected(Graph *graph, int* tier0Ndes, int tier0Count);
int  tier0AllCon(Graph *graph, int *tier0Nodes, int tier0Count);
int * bfsTier0(Graph *graph, int startVertex );
int findLeaf(Graph *graph);
void dfsLeaf(struct Graph* graph, int startVertex, int prevMove, int sideways, int *visited);

#endif