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
      for(int i = 0; i < graph->V; i++) {
          if(visited[i] == 0) {
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
    int * visited = (int *)malloc(graph->V * sizeof(int));
    int position = getHash(graph, startVertex);

    visited[position] = 1;
    enqueue(q, position, graph->V);

    while (!isEmpty(q)) {
        int currentNodeIndex = dequeue(q);

        struct AdjListNode* currentListNode = graph->array[currentNodeIndex].head;
        while (currentListNode) {
          int neighbourIndex = getHash(graph, currentListNode->neighbour);
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

void AP(Graph* g)
{

  printf("line 123");

  int i;
  int* d = (int*)malloc(sizeof(int)*g->V);
  int* isVisited = (int*)malloc(sizeof(int)*g->V);
  int* parent = (int*)malloc(sizeof(int)*g->V);
  int* l = (int*)malloc(sizeof(int)*g->V);
  int* ap = (int*)malloc(sizeof(int)*g->V); 


  for(i=0;i<g->V;i++) //initializing the vectors
  {
    isVisited[i]=0;
    parent[i]=-1;
    ap[i]=0;
  }

  printf("line 134 \n");

  //this "for" returns all AP in a non-connected graph
  /*for(i=0;i<g->V;i++) //for each unvisited node (explores the entire graph)
  {
      if(isVisited[i]==0)
      {
          apUtil(g,i,isVisited,d,parent,l,ap);//i is the index of the node to be explored
      }
  }*/

  //if the graph is connected apUtil just needs to be executed once
  i= 0;
  apUtil(g,i,isVisited,d,parent,l,ap);//i is the index of the node to be explored


  
  for(i=0;i<g->V;i++)
  {
      struct AdjListNode* temp = g->array[i].head;
      printf(" %d ap, %d node name \n",ap[i], temp->node);
  }
}


//(all arrays respect the order of the AdjList array)
void apUtil(Graph *g, int index, int* isVisited, int* d,int* parent,int* l,int* ap)
{
  struct AdjListNode* temp = g->array[index].head;
  static int time=0;
  int children=0;
  isVisited[index]=1; 
  time++;


  d[index]=l[index]=time;

  while(temp!=NULL)
  {       
    int neighbourIndex = getHash(g, temp->neighbour);
    if(!isVisited[neighbourIndex])
      {

        children++;
        parent[neighbourIndex]= index;
        apUtil(g,neighbourIndex,isVisited,d,parent,l,ap);

      l[index]= min(l[index],l[neighbourIndex]);

      if(parent[index]==-1 && children>1){
            ap[index]=1;
      }

      if(parent[index]!=-1 && d[index]<=l[neighbourIndex]){
        ap[index]=1; 
      }
                    
      }    

    else if(temp->neighbour!=parent[index])
      {
          l[index]=min(l[index],d[neighbourIndex]);
      }
    temp= temp->next;
  }
}


int min(int a,int b)
{
    return(a<b?a:b);
}