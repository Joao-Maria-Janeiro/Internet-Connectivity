#ifndef _MATRICE_H
#define _MATRICE_H

#include "file_handler.h"

int graphIsConnected(Graph * graph);
struct queue* createQueue(int n);
int * bfs(Graph * graph, int startVertex);
void enqueue(struct queue* q, int value, int n);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void AP(struct Graph* g);
void apUtil(struct Graph * g, int index, int* isVisited, int* d,int* parent,int* l,int* ap);
int min(int a,int b);

#endif