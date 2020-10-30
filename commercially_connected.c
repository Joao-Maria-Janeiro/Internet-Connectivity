#include "commercially_connected.h"
/*tier0Nodes is an array that keeps the tier0Nodes by whichever order they are found*/
int findTier0(Graph *graph, int * tier0Nodes){
  struct AdjListNode* temp;
  int t0Flag = 1;
  int i = 0;
  int tier0Count= 0;


  
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
      tier0Nodes[tier0Count] = i;
      

      printf("Tier 0: %d\n", i);
      tier0Count++;
    }
  }
  return tier0Count;
}



void findAllCycles(Graph* graph, int u, int parent, int visited[], int marked[], int parents[], int *cyclenumber){
  
  struct AdjListNode* temp = graph->array[u].head;

  if(visited[u] == 2){
    return;
  }
  
  if( visited[u] == 1){
    *cyclenumber ++;
    int current = parent;
    marked[current] = *cyclenumber;
  
    printf("Current fora While: %d %d\n", current, u);
  
    while(current != u){
      current = parents[current];
      marked[current] = *cyclenumber;
      if(current != 0)
        printf("Current dentro While: %d\n", current);
    }
    return;
  }
  parents[u] = parent;
  visited[u] = 1;
  
  while (temp != NULL){ // We only need to find a single cycle, so once we find one we stop

    printf("Parent: %d | Node: %d | Child: %d | Hierarchy: %d | Parents[u]: %d\n",  parent, u, temp->neighbour, temp->hierarchy, parents[u]);

    // if(temp->hierarchy != 1) { // If it's a peer to peer it's not commercial
    //   temp = temp->next;
    //   continue;
    // }

    // If an adjacent is not visited, then recur for that adjacent 
    //printf("Neighbour: %d\n",temp->neighbour);
    if((temp->neighbour == parents[u]) ) {
      temp = temp->next;

      //isCommerciallyCyclicUtil(graph, temp->neighbour, visited, v, cycleVertices, cycleFoundFlag, cycleFinished, firstNode, leftTheWhile);
      continue;  
    } 
    findAllCycles(graph,  temp->neighbour,  u,  visited,  marked,  parents,  cyclenumber); 
    temp = temp->next;   
  }
  marked[u] == 2;
}


// Function to print the cycles 
void printCycles(int listSize, int marked[], int cyclenumber) 
{ 
    int** cycles = (int**)malloc(cyclenumber* sizeof(int*));
    int* currentCycleIndexes = (int*)malloc(cyclenumber * sizeof(int));

    // push the edges that into the 
    // cycle adjacency list 
    for(int i = 0; i < cyclenumber; i++){
      cycles[i] = (int*)malloc(listSize/2 * sizeof(int));
    }

    for (int i = 1; i <= listSize; i++) { 
        if (marked[i] != 0) 
            cycles[marked[i]][currentCycleIndexes[marked[i]]++] = i;
         
    } 
  
    // print all the vertex with same cycle 
    for (int i = 1; i <= cyclenumber; i++) { 
        // Print the i-th cycle 
        printf("Cycle Number: %d\n ", i); 
        for (int x = 0; x < currentCycleIndexes[i]; x++) 
            printf("X: %d ", cycles[i][x]);
        printf("\n");
    } 
} 

// ###############################################
// ###############################################
// ###############################################
// ###############################################

int commerciallyConnected(Graph *graph, int* tier0Nodes, int tier0Count){
  

  int * visited = (int *)malloc(graph->listSize*sizeof(int));
  for(int i= 0; i<graph->listSize; i++){
    visited[i] = 0;
  }

  if( tier0Count == 0){
      
  }

  if(tier0AllCon(graph, tier0Nodes, tier0Count) == 0) return 0;

  
  // printf("\n");
  bfsTier0(graph, tier0Nodes[0], visited);
  // printf("visited[2] %d \n", visited[2] );

  for(int i = 0; i < graph->listSize; i++) {
    if(graph->array[i].head != NULL) {
      if (visited[i] !=  1)
        return 0;
    }
  }

  return 1;
}

/*checks if all tier 0 Nodes present in the array tier0Nodes are connected */
int  tier0AllCon(Graph *graph, int *tier0Nodes, int tier0Count){
  struct AdjListNode* temp;
  int alright = 0;

  if(tier0Count == 1) return 1;

  for(int i= 0; i<tier0Count-1; i++){
    for(int j = i+1; j<tier0Count; j++){    
      temp = graph->array[tier0Nodes[i]].head;
      alright= 0;
      while(temp != NULL){       
        if(temp->neighbour == tier0Nodes[j]){
          alright = 1;
          break;
        }
        temp = temp->next;
      }
      if(alright == 0){
        printf("Node %d is not connected to every other Tier 1 node \n", tier0Nodes[i]);
        return 0;
      }
    }
  }

  //else they are all connected
  //printf("All connected\n");
  return 1;
}

/*basicaly a bfs with restrictions regarding the moves
tier0Nodes can only move downwards (to customers)*/
int* bfsTier0(Graph *graph, int startVertex, int *visited ){
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
    // printf("onde é que tu vais maroto?\n");
    return visited;
}









/*tier0Nodes is an array that keeps the tier0Nodes by whichever order they are found*/
/*int findLeaf(Graph *graph){
  struct AdjListNode* temp;
  int leafFlag = 1;
  int i = 0;


  for(i = 0; i<graph->listSize; i++){
    leafFlag = 1;
    temp = graph->array[i].head;
    if(temp == NULL ) continue;
    while(temp != NULL){
      if((temp->hierarchy == 1) || (temp->hierarchy == 2)){
        leafFlag = 0;
        break;
      } 
      temp = temp->next;
    }
    if(leafFlag == 1){
      return i;
    }
  }

}
*/
/*tries to access all nodes from the startLeaf
Contrary to the Tier0's case, the moves permited this time are:
    - up (x times)
    - up (x times) + sideways (1 time)
    - up (x times) + down (x times)
    - up (x times) + sideways (1 time) + down (x times)

Since it is useful to know whether the sideways move has been done or not,
a dfs will be used, because this algorithm tries to complete a path before 
exploring other possibilities, and such path will have a flag indicating what was the previous move
and if the sideways move was already taken

prevMove: 1 - down
          2 - sideways
          3 - up

IMPORTANT: The first time that dsfLeaf is called prevMove = 3, sideways = 0
*/

/*void dfsLeaf(struct Graph* graph, int startVertex, int prevMove, int sideways, int *visited) {

  struct AdjListNode* temp = graph->array[startVertex].head;

  visited[startVertex] = 1;

  while (temp != NULL) {
    int neighbour = temp->neighbour;
    printf("neighbour %d \t hierarchy %d \t prevMove = %d \t visited = %d \n", neighbour, temp->hierarchy, prevMove, visited[neighbour]);
    if (visited[neighbour] == 0)  {
      if((temp->hierarchy == 3) && (prevMove == 3)){ //a node can only go up if its last move was also upwards UP
        printf("up\n");
        prevMove = temp->hierarchy;
        dfsLeaf(graph, neighbour, prevMove, sideways, visited);
      }
      else if((temp->hierarchy == 2) && (prevMove == 3) && (sideways == 0) ){//a node can only move sideways once SIDEWAYS
        sideways == 1;
        prevMove = temp->hierarchy;
        dfsLeaf(graph, neighbour, prevMove, sideways, visited);
      }
      else if((temp->hierarchy == 1) ){ //a node can always move downwards DOWN
        printf("down\n");
        prevMove = temp->hierarchy;
        dfsLeaf(graph, neighbour, prevMove, sideways, visited);
      }
    }
    temp = temp->next;
  }
  
}*/