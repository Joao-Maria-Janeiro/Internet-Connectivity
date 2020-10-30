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
  printf("No cycles found, the graph commercially is acyclic\n");
  free(visited);
  free(cycleVertices);
  free(leftTheWhile);
  return 0;
}

void isCommerciallyCyclicUtil(Graph * graph, int v, int * visited, int parent, int * cycleVertices, int * cycleFoundFlag, int * cycleFinished, int * firstNode, int * leftTheWhile) {
  visited[v] = 1;
  struct AdjListNode* temp = graph->array[v].head;

  while ((temp != NULL) && (*cycleFoundFlag == -1)) { // We only need to find a single cycle, so once we find one we stop

    // printf("Parent: %d | Node: %d | Child: %d | Hierarchy: %d\n",  parent, v, temp->neighbour, temp->hierarchy);

    if(temp->hierarchy != 1) { // If it's a peer to peer it's not commercial
      temp = temp->next;
      continue;
    }

    // If an adjacent is not visited, then recur for that adjacent 
    if(!visited[temp->neighbour]) {
      isCommerciallyCyclicUtil(graph, temp->neighbour, visited, v, cycleVertices, cycleFoundFlag, cycleFinished, firstNode, leftTheWhile);
        // return 1;
    } else if((temp->neighbour != parent) && (leftTheWhile[temp->neighbour] == 0)) { // If an adjacent is visited and  
      // not parent of current vertex, 
      // then there is a cycle.
      
      // printf("Cycle ||| Parent: %d | Node: %d | Child: %d | Hierarchy: %d\n",  parent, v, temp->neighbour, temp->hierarchy);
      cycleVertices[v] = 1;
      cycleVertices[temp->neighbour] = 1;
      *firstNode = temp->neighbour;
      *cycleFoundFlag = 0;
      // return 1;
    }

    temp = temp->next;
  }

  leftTheWhile[v] = 1;

  if(((*cycleFoundFlag) != -1) && (*cycleFinished == 0)) {
    // printf("Inside Saving : Parent: %d | Node: %d\n",  parent, v);
    if(v == *firstNode) {
      // printf("I finished it %d\n", v);
      *cycleFinished = 1;
    } else {
      // printf("I was saved %d\n", v);
      cycleVertices[v] = 1;
    }
  }

  // printf("Outside : Parent: %d | Node: %d\n",  parent, v);

  // return 0;
}

