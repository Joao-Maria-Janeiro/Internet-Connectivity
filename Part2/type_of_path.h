#ifndef _PATH_TYPE_H
#define _PATH_TYPE_H

#include "graph_handler.h"
#include "heap.h"

typedef struct queue {
  int * items;
  int front;
  int rear;
} queue;



int pathType(Graph * graph, int startVertex, int endVertex);
int djikstraToFindPathType(Graph * graph, int startVertex, int endVertex, int * parent, int * visited, HeapNode * heap, int * heapSize, int * allocatedHeapSize);








#endif