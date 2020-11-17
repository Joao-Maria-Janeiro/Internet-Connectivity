#include "connected.h"



int graphIsConnected(Graph * graph) {
    int connected =1;
    int *visited;
    int j = 0;

    if (graph->E < graph->V - 1) {
        connected = 0;
    }
    else {
      while (graph->array[j].head == NULL) {
          j++;
      } 

      visited = bfs(graph, graph->array[j].head->node);
      for(int i = 0; i < graph->listSize; i++){
        if(graph->array[i].head != NULL) {
              if (visited[i] == 0)
                connected = 0;
            }
        } 
      
    }
    free(visited);
    if (connected == 1 )
      printf("The Graph is Connected\n");
    else 
      printf("The Graph is not connected\n");
    
  return connected;
}
