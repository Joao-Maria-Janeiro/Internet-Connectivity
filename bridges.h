#ifndef _BRIDGES_H
#define _BRIDGES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice_handler.h"

typedef struct Edge {
    int u; //index of u
    int v; //index of v
} Edge;

void bridges(Graph* g);
int min(int a,int b);
int bridgesUtil(Graph *g, int uIndex, int* isVisited, int* d,int* parent,int* l, Edge *bridgesArray);

#endif 
