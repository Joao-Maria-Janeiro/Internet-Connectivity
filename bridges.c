#include "bridges.h"

int min(int a,int b) {
  return(a<b?a:b);
}

void bridges(Graph* graph) {
    int i = 0;
    int* d = (int*)malloc(sizeof(int)*graph->listSize);
    int* isVisited = (int*)malloc(sizeof(int)*graph->listSize);
    int* parent = (int*)malloc(sizeof(int)*graph->listSize);
    int* l = (int*)malloc(sizeof(int)*graph->listSize);
    int numberBridges = 0;
    struct AdjListNode* temp = NULL;
    struct Edge *bridgesArray = malloc(sizeof(struct Edge)*graph->E);
    int bridgesCount = 0;

    for(i=0;i<graph->listSize;i++) { //initializing the vectors
        isVisited[i]=0;
        parent[i]=-1;
    }
    
    for(i = 0; i< graph->listSize; i++){
        if((!isVisited[i]) && (graph->array[i].head != NULL)){
          bridgesCount = bridgesUtil(graph,i,isVisited,d,parent,l,bridgesArray);
          
        }
    }

    printf("There are %d bridges\n\n\n\n",bridgesCount );
    bridgesCount = 0;
    
    // for(int k = 0; k<bridgesCount; k++){
    //     temp = graph->array[bridgesArray[k].u].head;
    //     printf("%d \t", temp->node);
    //     temp = graph->array[bridgesArray[k].v].head;
    //     printf("%d \n", temp->node);
    //     if(bridgesCount)
    // }
  
  free(d);
  free(isVisited);
  free(parent);
  free(l);
  free(bridgesArray);
}

//(all arrays respect the order of the AdjList array)
int bridgesUtil(Graph *g, int u, int* isVisited, int* d,int* parent,int* l, Edge *bridgesArray) {
  struct AdjListNode* temp = g->array[u].head;
  static int time = 0; 
  static int bridgesCount = 0;
  int auxiliar = 0; 
  
  isVisited[u]=1; 
  d[u]=l[u]=++time;
  
  while(temp!=NULL) {       
    // int vIndex = getHash(g, temp->neighbour);
    int v = temp->neighbour; 

    struct AdjListNode* tempAux = g->array[v].head;
    
    if(!isVisited[v]) { //if neighbour was not visited
      parent[v] = temp->node;
      
      bridgesCount  = bridgesUtil(g,v,isVisited,d,parent,l,bridgesArray);
      
      l[u]= min(l[u],l[v]);

      if(d[u] < l[v]) {       
        bridgesArray[bridgesCount].u = u;
        bridgesArray[bridgesCount].v = v;
        bridgesCount++;
      }             
    }else if(temp->neighbour!=parent[u]) {
      l[u]=min(l[u],d[v]);
    }
    temp= temp->next;
  }
  auxiliar = bridgesCount;
  bridgesCount = 0;
  free(temp);
  return auxiliar;
}
