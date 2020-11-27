#ifndef _PATH_TYPE_H
#define _PATH_TYPE_H

#include "graph_handler.h"
#include "heap.h"
#include "matrice_handler.h"

// typedef struct queue {
//   int * items;
//   int front;
//   int rear;
// } queue;



int pathType(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex, int* count,HeapNode * heap );
int* djikstraToFindPathType(Graph * graph, int startVertex, int endVertex, int * parent, int * visited, HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count, int commercially_Connected);
void *bfsPathType(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex, HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count);
int caminhoInverso(int caminho);




#endif