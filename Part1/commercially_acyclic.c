#include "commercially_acyclic.h"

int isCommerciallyCyclic (Graph * graph) {
  int * visited = (int *)malloc(graph->listSize * sizeof(int));
  int * cycleVertices = (int *)malloc(graph->listSize * sizeof(int));
  int * leftTheWhile = (int *)malloc(graph->listSize * sizeof(int));
  int cycleFoundFlag = -1, cycleFinished = 0, firstNode = 0;

  for (int i = 0; i < graph->listSize; i++ ) {
    visited[i] = 0;
    cycleVertices[i] = 0;
    leftTheWhile[i] = 0;
  }

  // If the graph is not connected, check on all different disconnected subgraphs
  for (int u = 0; u < graph->listSize; u++) {
    if (!visited[u] && (graph->array[u].head != NULL) && (cycleFoundFlag == -1)) {
      isCommerciallyCyclicUtil(graph, u, visited, -1, cycleVertices, &cycleFoundFlag, &cycleFinished, &firstNode, leftTheWhile);
      if (cycleFoundFlag != -1) {
        printf("There is at least one commercial cycle, the cycle found is: \n\n\n");
        for (int i = 0; i < graph->listSize; i++) {
          if(cycleVertices[i] == 1)
            printf("%d\n", i);
        }
        free(visited);
        return 1;
      }
        
    }
  }
  printf("There were no cycles found, the graph is acyclic\n");
  free(visited);
  free(cycleVertices);
  free(leftTheWhile);
  return 0;
}

void isCommerciallyCyclicUtil(Graph * graph, int v, int * visited, int parent, int * cycleVertices, int * cycleFoundFlag, int * cycleFinished, int * firstNode, int * leftTheWhile) {
  visited[v] = 1;
  struct AdjListNode* temp = graph->array[v].head;

  while ((temp != NULL) && (*cycleFoundFlag == -1)) { // We only need to find a single cycle, so once we find one we stop

    if(temp->hierarchy != 1) { // If it's a peer to peer it's not commercial
      temp = temp->next;
      continue;
    }

    // If an adjacent is not visited, then recur for that adjacent 
    if(!visited[temp->neighbour]) {
      isCommerciallyCyclicUtil(graph, temp->neighbour, visited, v, cycleVertices, cycleFoundFlag, cycleFinished, firstNode, leftTheWhile);
    } else if((temp->neighbour != parent) && (leftTheWhile[temp->neighbour] == 0)) { // If an adjacent is visited and  
      // not parent of current vertex, 
      // then there is a cycle.
      cycleVertices[v] = 1;
      cycleVertices[temp->neighbour] = 1;
      *firstNode = temp->neighbour;
      *cycleFoundFlag = 0;
    }

    temp = temp->next;
  }

  leftTheWhile[v] = 1;

  if(((*cycleFoundFlag) != -1) && (*cycleFinished == 0)) {
    if(v == *firstNode) {
      *cycleFinished = 1;
    } else {
      cycleVertices[v] = 1;
    }
  }
}

