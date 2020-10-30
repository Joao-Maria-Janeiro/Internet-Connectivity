#include "commercially_connected.h"
/*Tier1Nodes is an array that keeps the Tier1Nodes by whichever order they are found*/
int findTier1(Graph *graph, int * Tier1Nodes){
  struct AdjListNode* temp;
  int t0Flag = 1;
  int i = 0;
  int Tier1Count= 0;


  
  for(i = 0; i<graph->listSize; i++){
    t0Flag = 1;
    temp = graph->array[i].head;
    if(temp == NULL ) continue;
    while(temp != NULL){
      // printf(" i %d \n", i);
      // printf("t0flag = %d \t hierarchy = %d \n", t0Flag, temp->hierarchy);
      if(temp->hierarchy == 3){
        t0Flag = 0;
        break;
      } 
      temp = temp->next;
    }
    //printf("t0flag = %d \t SAIU DO WHILE\n", t0Flag);
    if(t0Flag == 1){
      Tier1Nodes[Tier1Count] = i;
      Tier1Count++;
    }
  }
  return Tier1Count;
}



void findAllCycles(Graph* graph, int u, int parent, int visited[], int marked[], int parents[], int *cyclenumber){
  
  struct AdjListNode* temp = graph->array[u].head;
  

  int *cycles = (int *)malloc(graph->listSize * sizeof(int));
  int *tempo = (int *)malloc(graph->listSize * sizeof(int));

  if(visited[u] == 2){
    return;
  }
  
  if( visited[u] == 1){
    (*cyclenumber)++;
    
    int current = parent;
    marked[current] = *cyclenumber;
  
    cycles[tempo[marked[current]]++] = current;
    printf("ciclos: %d %d %d\n", cycles[tempo[marked[current]]-1], marked[current],tempo[marked[current]] );

    while(current != u){
      current = parents[current];
      
      marked[current] = *cyclenumber;
      cycles[tempo[marked[current]]++] = current;
      printf("ciclos: %d %d %d\n", cycles[tempo[marked[current]]-1], marked[current],tempo[marked[current]]);
      
    }
    
    return;
  }
  

  parents[u] = parent;
  visited[u] = 1;
  
  while (temp != NULL){ // We only need to find a single cycle, so once we find one we stop



    // if(temp->hierarchy != 1) { // If it's a peer to peer it's not commercial
    //     printf("Parent: %d | Node: %d | Child: %d | Hierarchy: %d | Parents[u]: %d\n ",  parent, u, temp->neighbour, temp->hierarchy, parents[u]);
    //      temp = temp->next;
    //      continue;
    // }
    // else if((temp->neighbour == parents[u])&& (temp->hierarchy != 3 )){
    //   temp = temp->next;
    //      continue;
    //printf("Parent: %d | Node: %d | Child: %d | Hierarchy: %d | Parents[u]: %d ...... %d\n ",  parent, u, temp->neighbour, temp->hierarchy, parents[u]);
         //temp = temp->next;
  
    // printf("Parent: %d | Node: %d | Child: %d | Hierarchy: %d | Parents[u]: %d\n ",  parent, u, temp->neighbour, temp->hierarchy, parents[u]);
    // If an adjacent is not visited, then recur for that adjacent 
    //printf("Neighbour: %d\n",temp->neighbour);
    if((temp->neighbour == parents[u]) ) {
      temp = temp->next;
      //printf("While\n")    ;
      //isCommerciallyCyclicUtil(graph, temp->neighbour, visited, v, cycleVertices, cycleFoundFlag, cycleFinished, firstNode, leftTheWhile);
      continue;  
    } 
    findAllCycles(graph,  temp->neighbour,  u,  visited,  marked,  parents,  cyclenumber); 
    temp = temp->next;   
  }
  visited[u] = 2;
  
}


// Function to print the cycles 
void printCycles(int listSize, int marked[], int cyclenumber) 
{ 
    int** cycles = (int**)malloc(cyclenumber* sizeof(int*));
    int* currentCycleIndexes = (int*)malloc(cyclenumber * sizeof(int));

    // push the edges that into the 
    // cycle adjacency list 
    printf("CycleCount: %d\n", cyclenumber);
    
    for(int i = 0; i < cyclenumber; i++){
      cycles[i] = (int*)malloc(listSize * sizeof(int));
      printf("Marked: %d\n",marked[i] );
    }

    for (int i = 1; i <= cyclenumber; i++) { 
         if (marked[i] != 0) 
            cycles[marked[i]][currentCycleIndexes[marked[i]]++] = i;
         
    } 
  
 
} 


int commerciallyConnected(Graph *graph, int* Tier1Nodes, int Tier1Count){
  

  int * visited = (int *)malloc(graph->listSize*sizeof(int));
  for(int i= 0; i<graph->listSize; i++){
    visited[i] = 0;
  }

  if( Tier1Count == 0){
      
  }

  if(Tier1AllCon(graph, Tier1Nodes, Tier1Count) == 0) return 0;

  
  // printf("\n");
  bfsTier1(graph, Tier1Nodes[0], visited);
  // printf("visited[2] %d \n", visited[2] );

  for(int i = 0; i < graph->listSize; i++) {
    if(graph->array[i].head != NULL) {
      if (visited[i] !=  1){
        printf("The Network is not Commercially Connecte\n\n\n");
        return 0;
      }
    }
  }
  printf("The Network is Commercially Connected\n\n\n");
  free(visited);
  return 1;
}

/*checks if all tier 0 Nodes present in the array Tier1Nodes are connected */
int  Tier1AllCon(Graph *graph, int *Tier1Nodes, int Tier1Count){
  struct AdjListNode* temp;
  int alright = 0;

  if(Tier1Count == 1) return 1;

  for(int i= 0; i<Tier1Count-1; i++){
    for(int j = i+1; j<Tier1Count; j++){    
      temp = graph->array[Tier1Nodes[i]].head;
      alright= 0;
      while(temp != NULL){       
        if(temp->neighbour == Tier1Nodes[j]){
          alright = 1;
          break;
        }
        temp = temp->next;
      }
      if(alright == 0){
        printf("Node %d is not connected to every other Tier 1 node \n", Tier1Nodes[i]);
        return 0;
      }
    }
  }

  //else they are all connected
  //printf("All connected\n");
  return 1;
}

/*basicaly a bfs with restrictions regarding the moves
Tier1Nodes can only move downwards (to customers)*/
int* bfsTier1(Graph *graph, int startVertex, int *visited ){
  struct queue* q = createQueue(graph->V);
  
  struct AdjListNode* startVertexNode = graph->array[startVertex].head;

  visited[startVertex] = 1;
  enqueue(q, startVertex, graph->V);


  while (!isEmpty(q)) {
        int currentNodeIndex = dequeue(q);

        struct AdjListNode* currentListNode = graph->array[currentNodeIndex].head;
        while (currentListNode) { //add neighbours if they are peers of the startVertex or customers of currentListNode
          int neighbourIndex = currentListNode->neighbour;
          if ((visited[neighbourIndex] != 1) &&(currentListNode->hierarchy == 1)) {
              visited[neighbourIndex] = 1;
              // printf("%d down currenode %d neighbour %d \n", currentListNode->hierarchy, currentListNode->node, currentListNode->neighbour);
              enqueue(q, neighbourIndex, graph->V);
          }
          if ((visited[neighbourIndex] != 1) &&(currentNodeIndex == startVertex) && (currentListNode->hierarchy == 2)) {
              visited[neighbourIndex] = 1;
              // printf("sideways\n");
              enqueue(q, neighbourIndex, graph->V);
          }
          currentListNode = currentListNode->next;
        }
    }
    free(q->items);
    free(q);
    
    return visited;
}








