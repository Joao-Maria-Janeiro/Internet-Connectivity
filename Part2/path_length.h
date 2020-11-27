#ifndef _PATH_LENGTH_H
#define _PATH_LENGTH_H

#include "graph_handler.h"
#include "heap.h"
#include "matrice_handler.h"
#include "type_of_path.h"

int pathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , int * count,HeapNode * heap);
void *bfsPathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count);

#endif