#ifndef _PATH_LENGTH_H
#define _PATH_LENGTH_H

#include "graph_handler.h"
#include "heap.h"
#include "matrice_handler.h"


int pathLength(Graph * graph, int startVertex, int * count);
void djikstraToFindPathLength(Graph * graph, int startVertex, LengthHeapNode * heap, int * heapSize, int * allocatedHeapSize, int * count);


#endif