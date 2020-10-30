#ifndef _ACYCLIC_H
#define _ACYCLIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_handler.h"

int isCommerciallyCyclic (Graph * graph);
void isCommerciallyCyclicUtil(Graph * graph, int v, int * visited, int parent, int * cycleVertices, int * cycleFoundFlag, int * cycleFinished, int * firstNode, int * leftTheWhile);

#endif  