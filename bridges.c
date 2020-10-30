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
    struct Edge *bridgesArray = NULL;

    bridgesArray = malloc(sizeof(struct Edge));


    for(i=0;i<=graph->listSize;i++) { //initializing the vectors
        isVisited[i]=0;
        parent[i]=-1;
    }
    int bridgesCount = 0;
    for(i = 0; i< graph->listSize; i++){
        if((!isVisited[i]) && (graph->array[i].head != NULL)){
          bridgesCount = bridgesUtil(graph,i,isVisited,d,parent,l,bridgesArray);
          

        }

    }
    printf("There are %d bridges\n",bridgesCount );

    for(int k = 0; k<bridgesCount; k++){
        temp = graph->array[bridgesArray[k].u].head;
        //printf("%d unode \t", temp->node);
        temp = graph->array[bridgesArray[k].v].head;
        //printf("%d vnode \n", temp->node);
    }
  
  
  free(d);
 
  free(isVisited);
  
  //free(parent);

  //free(l);
}

//(all arrays respect the order of the AdjList array)
int bridgesUtil(Graph *g, int u, int* isVisited, int* d,int* parent,int* l, Edge *bridgesArray) {
  struct AdjListNode* temp = g->array[u].head;
  static int time=0; //ya eu sei que isto é foleiro mas azar
  static int bridgesCount = 0; 
  //printf("Bridges Count: %d\n", bridgesCount);
  /*if (bridgesCount > 800 ){
    return bridgesCount;
  }*/
  isVisited[u]=1; 
  d[u]=l[u]=++time;
  //printf("Time: %d\n", time);
  while(temp!=NULL) {       
    // int vIndex = getHash(g, temp->neighbour);
    int v = temp->neighbour; 
    // printf("v = %d \n", v);
    
    struct AdjListNode* tempAux = g->array[v].head;
    //printf("Nova estrutura\n");
    if(!isVisited[v]) { //if neighbour was not visited
      parent[v] = temp->node;
      // printf("Debug line:179 %d  %d %d \n ", v, parent[v], temp->neighbour );
      bridgesCount  = bridgesUtil(g,v,isVisited,d,parent,l,bridgesArray);
      /*if (bridgesCount > 800 ){
        return bridgesCount;
      }*/
      printf("Debug line:181 %d  %d %d \n ", v, parent[v], temp->neighbour );

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
    //printf("Debug line:196\n");
    temp= temp->next;
  }
  //printf("Sai linha:94\n");

  free(temp);
  return bridgesCount;
}
