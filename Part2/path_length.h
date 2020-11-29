#ifndef _PATH_LENGTH_H
#define _PATH_LENGTH_H

#include "graph_handler.h"
#include "heap.h"
#include "matrice_handler.h"
#include "type_of_path.h"

int pathLength(Graph * graph, int inputStartVertex, int inputDestVertex , int * count, int flag1Time);
void *bfsPathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestinationVertex, BestPathHeapNode * heap1, BestPathHeapNode* heap2, BestPathHeapNode * heap3 ,int ** typeOfPath, int **caminhosLegais);

#endif