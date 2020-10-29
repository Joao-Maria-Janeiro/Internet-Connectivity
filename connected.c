#include "connected.h"



int graphIsConnected(Graph * graph) {
    int connected = 0;
    if (graph->E < graph->V - 1) {
        connected =  0;
    } else {
      int i = 0;
      while (graph->array[i].head == NULL) {
        i++;
      }
      int * visited = bfs(graph, graph->array[i].head->node);
      for(int i = 0; i < graph->listSize; i++) {
          if(graph->array[i].head != NULL) {
            if (visited[i] == 0)
              connected = 0;
          }
      }
      connected = 1;
    }

    if (connected == 1 )
      printf("The Graph is Connected\n");
    else 
      printf("The Graph is not connected\n");
  return connected;
}
