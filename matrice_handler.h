#ifndef _MATRICE_H
#define _MATRICE_H

#include "graph_handler.h"

typedef struct queue {
  int * items;
  int front;
  int rear;
} queue;



struct queue* createQueue(int n);
int * bfs(Graph * graph, int startVertex);
void enqueue(struct queue* q, int value, int n);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);








#endif