#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrice_handler.h"

// Create a queue
struct queue* createQueue(int n) {
    struct queue* q = malloc(sizeof(struct queue));
    q->items = (int *)malloc(n * sizeof(int));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}


// BFS algorithm
int * bfs(Graph * graph, int startVertex) {
    struct queue* q = createQueue(graph->V);
    int * visited = (int *)malloc(graph->listSize * sizeof(int));
    // int position = getHash(graph, startVertex);
    int position = startVertex;

    visited[position] = 1;
    enqueue(q, position, graph->V);

    while (!isEmpty(q)) {
        int currentNodeIndex = dequeue(q);

        struct AdjListNode* currentListNode = graph->array[currentNodeIndex].head;
        while (currentListNode) {
          // int neighbourIndex = getHash(graph, currentListNode->neighbour);
          int neighbourIndex = currentListNode->neighbour;
          if (visited[neighbourIndex] != 1) {
              visited[neighbourIndex] = 1;
              enqueue(q, neighbourIndex, graph->V);
          }
          currentListNode = currentListNode->next;
        }
    }
    return visited;
}


// Adding elements into queue
void enqueue(struct queue* q, int value, int n) {
  if (q->rear == n - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}


// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
    //   printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}



///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Commercially acyclic

///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///commercially connected
