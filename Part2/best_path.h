#ifndef _BEST_PATH_H
#define _BEST_PATH_H

#include "graph_handler.h"
#include "heap.h"
#include "matrice_handler.h"
#include "type_of_path.h"

int bestPath(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , int * count);
void *bfsBestPath(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count);

#endif