#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrice_handler.h"
#include "file_handler.h"

int graphIsConnected(Graph * graph) {
    if (graph->E < graph->V - 1) {
        return 0;
    } else {
      int i = 0;
      while (graph->array[i].head == NULL) {
        i++;
      }
      int * visited = bfs(graph, graph->array[i].head->node);
      for(int i = 0; i < graph->listSize; i++) {
          if(graph->array[i].head != NULL) {
            if (visited[i] == 0)
              return 0;
          }
      }
      return 1;
    }
}


struct queue {
  int * items;
  int front;
  int rear;
};

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

int min(int a,int b) {
  return(a<b?a:b);
}


///////////////////////////////////////////////////////////////////////////////////
void bridges(Graph* graph) {
  int i;
  int* d = (int*)malloc(sizeof(int)*graph->listSize);
  int* isVisited = (int*)malloc(sizeof(int)*graph->listSize);
  int* parent = (int*)malloc(sizeof(int)*graph->listSize);
  int* l = (int*)malloc(sizeof(int)*graph->listSize);
  int numberBridges = 0;
  struct AdjListNode* temp;
  
  struct Edge *bridgesArray;
  bridgesArray = malloc(sizeof(struct Edge));


  for(i=0;i<=graph->listSize;i++) { //initializing the vectors
    isVisited[i]=0;
    parent[i]=-1;
  }


  //if the graph is connected bridgesUtil just needs to be executed once

  while (graph->array[i].head == NULL) {
    i++;
  }
  numberBridges = bridgesUtil(graph,i,isVisited,d,parent,l,bridgesArray);//i is the index of the node to be explored

  printf("bridges count = %d \n", numberBridges);

  

  for(i=0;i< numberBridges;i++)
  {
      //printf(" %d bridge %d\n", bridgesArray[i].u, bridgesArray[i].v);
      temp = graph->array[bridgesArray[i].u].head;
      printf("%d unode \n", temp->node);
      temp = graph->array[bridgesArray[i].v].head;
      printf("%d vnode \n", temp->node);

      printf("\n \n");
      
  }
  free(d);
  free(isVisited);
  free(parent);
  free(l);
}


//(all arrays respect the order of the AdjList array)
int bridgesUtil(Graph *g, int u, int* isVisited, int* d,int* parent,int* l, Edge *bridgesArray) {
  struct AdjListNode* temp = g->array[u].head;
  static int time=0; //ya eu sei que isto é foleiro mas azar
  static int bridgesCount = 0; 
  static int arrebenta = 0;

  printf("arrebenta %d \n", arrebenta++);
  printf("RESPONSAVEL u = %d \n", u);

  isVisited[u]=1; 
  d[u]=l[u]=++time;
  
  while(temp!=NULL) {       
    // int vIndex = getHash(g, temp->neighbour);
    int v = temp->neighbour; printf("v = %d \n", v);
    
    struct AdjListNode* tempAux = g->array[v].head;

    if(!isVisited[v]) { //if neighbour was not visited
      parent[v] = temp->node;
      // printf("Debug line:179 %d  %d %d \n ", v, parent[v], temp->neighbour );
      bridgesUtil(g,v,isVisited,d,parent,l,bridgesArray);
      // printf("Debug line:181 %d  %d %d \n ", v, parent[v], temp->neighbour );

      l[u]= min(l[u],l[v]);

      if(d[u] < l[v]) {  //issa a madafucking bridge        
        bridgesArray[bridgesCount].u = u;
        bridgesArray[bridgesCount].v = v;
        bridgesCount++;
      }
                    
    } else if(temp->neighbour!=parent[u]) {
      l[u]=min(l[u],d[v]);
      // printf("Debug line:193\n");  
    }
    // printf("Debug line:196\n");
    temp= temp->next;
  }

  return bridgesCount;
}

//////////////////
// Commercially acyclic

int isCommerciallyCyclic (Graph * graph) {
  int * visited = (int *)malloc(graph->listSize * sizeof(int));
  int * cycleVertices = (int *)malloc(graph->listSize * sizeof(int));
  int cycleFoundFlag = -1, cycleFinished = 0, firstNode = 0;

  for (int i = 0; i < graph->listSize; i++ ) {
    visited[i] = 0;
    cycleVertices[i] = 0;
  }

  // If the graph is not connected, check on all different disconnected subgraphs
  for (int u = 0; u < graph->listSize; u++) {
    if (!visited[u] && (graph->array[u].head != NULL) && (cycleFoundFlag == -1)) {
      isCommerciallyCyclicUtil(graph, u, visited, -1, cycleVertices, &cycleFoundFlag, &cycleFinished, &firstNode);
      if (cycleFoundFlag != -1) {
        printf("Commercial cycle found: \n");
        for (int i = 0; i < graph->listSize; i++) {
          if(cycleVertices[i] == 1)
            printf("%d\n", i);
        }
        free(visited);
        return 1;
      }
        
    }
  }
  free(visited);
  return 0;
}

void isCommerciallyCyclicUtil(Graph * graph, int v, int * visited, int parent, int * cycleVertices, int * cycleFoundFlag, int * cycleFinished, int * firstNode) {
  visited[v] = 1;
  struct AdjListNode* temp = graph->array[v].head;

  while ((temp != NULL) && (*cycleFoundFlag == -1)) { // We only need to find a single cycle, so once we find one we stop

    if(temp->hierarchy == 2) { // If it's a peer to peer it's not commercial
      temp = temp->next;
      continue;
    }

    // printf("Parent: %d | Node: %d | Child: %d\n",  parent, v, temp->neighbour);

    // If an adjacent is not visited, then recur for that adjacent 
    if(!visited[temp->neighbour]) {
      isCommerciallyCyclicUtil(graph, temp->neighbour, visited, v, cycleVertices, cycleFoundFlag, cycleFinished, firstNode);
        // return 1;
    } else if(temp->neighbour != parent) { // If an adjacent is visited and  
      // not parent of current vertex, 
      // then there is a cycle.
      cycleVertices[v] = 1;
      cycleVertices[temp->neighbour] = 1;
      *firstNode = temp->neighbour;
      *cycleFoundFlag = 0;
      // return 1;
    }

    temp = temp->next;
  }

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


///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///commercially connected

/*tier0Nodes is an array that keeps the tier0Nodes by whichever order they are found*/
int findTier0(Graph *graph, int * tier0Nodes){
  struct AdjListNode* temp;
  int t0Flag = 1;
  int i = 0;
  int tier0Count= 0;


  //printf("entrou aqui \n");
  for(i = 0; i<graph->listSize; i++){
    t0Flag = 1;
    temp = graph->array[i].head;
    if(temp == NULL ) continue;
    while(temp != NULL){
      //printf(" i %d \n", i);
      //printf("t0flag = %d \t hierarchy = %d \n", t0Flag, temp->hierarchy);
      if(temp->hierarchy == 3){
        t0Flag = 0;
        break;
      } 
      temp = temp->next;
    }
    //printf("t0flag = %d \t SAIU DO WHILE\n", t0Flag);
    if(t0Flag == 1){
      tier0Nodes[tier0Count] = i;
      tier0Count++;
    }
  }

  return tier0Count;
}

int commerciallyConnected(Graph *graph, int* tier0Nodes, int tier0Count){

  int leafNode;
  int * visited = (int *)malloc(graph->listSize*sizeof(int));
  for(int i= 0; i<graph->listSize; i++){
    visited[i] = 0;
  }
  

  if(tier0Count == 0){
    leafNode = findLeaf(graph);
    printf("LEaf %d \n", leafNode);
    printf("leafNode = %d \n", leafNode);
    dfsLeaf(graph, leafNode, 3, 0, visited);
    for(int i = 0; i < graph->listSize; i++) {
      if(graph->array[i].head != NULL) {
        if (visited[i] == 0)
          return 0;
      }
    }
    return 1;
  }

  
  if(tier0AllCon(graph, tier0Nodes, tier0Count) == 0) return 0;

  for(int i= 0; i<graph->listSize; i++){
    printf("%d ", visited[i]);
  }
  printf("\n");
  bfsTier0(graph, tier0Nodes[0], visited);
  printf("visited[2] %d \n", visited[2] );

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
        printf("node %d is not connected to every other tier0 node \n", tier0Nodes[i]);
        return 0;
      }
    }
  }

  //else they are all connected
  printf("all con\n");
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
              printf("%d down currenode %d neighbour %d \n", currentListNode->hierarchy, currentListNode->node, currentListNode->neighbour);
              enqueue(q, neighbourIndex, graph->V);
          }
          if ((visited[neighbourIndex] != 1) &&(currentNodeIndex == startVertex) && (currentListNode->hierarchy == 2)) {
              visited[neighbourIndex] = 1;
              printf("sideways\n");
              enqueue(q, neighbourIndex, graph->V);
          }
          currentListNode = currentListNode->next;
        }
    }
    printf("onde é que tu vais maroto?\n");
    return visited;
}

/*tier0Nodes is an array that keeps the tier0Nodes by whichever order they are found*/
int findLeaf(Graph *graph){
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

void dfsLeaf(struct Graph* graph, int startVertex, int prevMove, int sideways, int *visited) {

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
      else if(temp->hierarchy == 1){ //a node can always move downwards DOWN
        printf("down\n");
        prevMove = temp->hierarchy;
        dfsLeaf(graph, neighbour, prevMove, sideways, visited);
      }
    }
    temp = temp->next;
  }
  
}