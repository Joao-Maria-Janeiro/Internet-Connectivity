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
  
  struct Edge *bridgesArray;
  bridgesArray = malloc(sizeof(struct Edge));


  for(i=0;i<=graph->listSize;i++) { //initializing the vectors
    isVisited[i]=0;
    parent[i]=-1;
  }


  //if the graph is connected bridgesUtil just needs to be executed once
  i= 1;

  numberBridges = bridgesUtil(graph,i,isVisited,d,parent,l,bridgesArray);//i is the index of the node to be explored

  printf("bridges count = %d \n", numberBridges);

  struct AdjListNode* temp;

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

  isVisited[u]=1; 
  d[u]=l[u]=++time;
  
  while(temp!=NULL) {       
    // int vIndex = getHash(g, temp->neighbour);
    int v = temp->neighbour;
    
    struct AdjListNode* tempAux = g->array[v].head;

    if(!isVisited[v]) { //if neighbour was not visited
      parent[v] = temp->node;
      printf("Debug line:179 %d  %d %d \n ", v, parent[v], temp->neighbour );
      bridgesUtil(g,v,isVisited,d,parent,l,bridgesArray);
      printf("Debug line:181 %d  %d %d \n ", v, parent[v], temp->neighbour );

      l[u]= min(l[u],l[v]);

      if(d[u] < l[v]) {  //issa a madafucking bridge        
        bridgesArray[bridgesCount].u = u;
        bridgesArray[bridgesCount].v = v;
        bridgesCount++;
      }
                    
    } else if(temp->neighbour!=parent[u]) {
      l[u]=min(l[u],d[v]);
      printf("Debug line:193\n");  
    }
    printf("Debug line:196\n");
    temp= temp->next;
  }

  return bridgesCount;
}
