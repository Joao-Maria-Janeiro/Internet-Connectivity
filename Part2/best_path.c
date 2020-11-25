#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "best_path.h"
#include "heap.h"

#define INFINITY 65533



int bestPath(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , int * count) {
    int allocatedHeapSize = 500;
    int heapSize = 0;
    short toInsertSize = 0;
    //Todo(): Make function to free heap
    HeapNode * heap = (HeapNode *) malloc((graph->listSize)* sizeof(HeapNode));

    int * parent = (int *)malloc(graph->listSize * sizeof(int)); // Array that tells the node where we came from
    
    //Array initialization
    for(int i = 0; i< graph->listSize; i++) {
      parent[i] = -1;
      
    }

    parent[startVertex] = startVertex;
    bfsBestPath(graph,  startVertex, inputStartVertex, inputDestVertex,  heap,  &heapSize,  &allocatedHeapSize, count);
    //djikstraToFindPathType(graph, startVertex, endVertex, parent, previousHierarchy, heap, &heapSize, &allocatedHeapSize, count, commercially_Connected);
    //djikstraToFindPathLength(graph, startVertex, heap, &heapSize, &allocatedHeapSize, count);

    
  	//Free arrays
    free(parent);
    free(heap);
}

void *bfsBestPath(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count) {
   
    AdjListNode* tempListNode = graph->array[startVertex].head;
    HeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    currentListNode.pathLength = 0;
    addToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

    int **caminhosLegais;
    int i = 0;

    caminhosLegais = (int**)malloc(sizeof(int*)*3);
    for(i= 0; i<3; i++)
        caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

    caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
    caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
    caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;


    int** community_path = (int**)malloc(sizeof(int*)*2);
    for(i= 0; i<2; i++)
        community_path[i] = (int*) malloc(sizeof(int)*graph->listSize);

   

    for(i=0; i<2; i++){
        for(int k = 0; k<graph->listSize; k++)
            community_path[i][k] = 9999; //mais infinito
    }
   

    int** private_path = (int**)malloc(sizeof(int*)*2);
    for(i= 0; i<2; i++)
        private_path[i] = (int*) malloc(sizeof(int)*graph->listSize);


    for(i=0; i<2; i++){
        for(int k = 0; k<graph->listSize; k++)
            private_path[i][k] = 9999; //mais infinito
    }
   
    int TYPE = 0;
    int LENGHT = 1;

    int FLAG = 0;

    //ESTA É A PARTE IMPORTANTE
    while((*heapSize) != 0){
        currentListNode = popFromHeap(heapSize, heap);
        printf("popped %d \n", currentListNode.node);
        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
            FLAG = 0;
            
            if(currentListNode.node == startVertex){ //so acontece da primeira vez, quando curr = startvertex
                //melhora o caminho do vizinho
                community_path[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                community_path[LENGHT][tempListNode->neighbour] = 1;
                private_path[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                private_path[LENGHT][tempListNode->neighbour] = 1;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = 1;
                printf("n %d direto %d inverso %d \n", neighbourNode.node, tempListNode->hierarchy, caminhoInverso(tempListNode->hierarchy));
                addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
            }
            
            else{
                //COMMUNITY
                //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora o LENGHT comunitario do vizinho
                printf("Is legal %d, current path lenght %d, neighbour %d community lenght %d \n",caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][currentListNode.previousHierarchy - 1], currentListNode.pathLength + 1, tempListNode->neighbour,  community_path[LENGHT][tempListNode->neighbour]);
                if((tempListNode->neighbour != startVertex)
                        && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][currentListNode.previousHierarchy - 1] != 4) 
                        && ((currentListNode.pathLength + 1) < community_path[LENGHT][tempListNode->neighbour]) ) {
                    //melhora o caminho do vizinho
                    //adiciona vizinho ao heap
                    community_path[LENGHT][tempListNode->neighbour] = currentListNode.pathLength + 1;
                    community_path[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);

                    HeapNode neighbourNode;
                    neighbourNode.node = tempListNode->neighbour;
                    neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                    neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                    neighbourNode.pathLength = currentListNode.pathLength+ 1;
                    addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
                    FLAG = 1;

                   
                    
                }
                //PRIVATE
                if((tempListNode->neighbour != startVertex)  //se o tipo for melhor, atualizar so o private_path
                        && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][currentListNode.previousHierarchy - 1] != 4) 
                        && (caminhoInverso(tempListNode->hierarchy) < private_path[TYPE][tempListNode->neighbour])) {
                    
                    private_path[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                    private_path[LENGHT][tempListNode->neighbour] = currentListNode.pathLength + 1;


                    if (FLAG != 1){
                        HeapNode neighbourNode;
                        neighbourNode.node = tempListNode->neighbour;
                        neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                        neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                        neighbourNode.pathLength = currentListNode.pathLength+ 1;
                        addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
                    }

                }
                else if((tempListNode->neighbour != startVertex) //se o tipo for igual, mas lenght melhor, atualizar private path
                        && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][currentListNode.previousHierarchy - 1] != 4) 
                        && (caminhoInverso(tempListNode->hierarchy) == private_path[TYPE][tempListNode->neighbour]) 
                        && (private_path[LENGHT][tempListNode->neighbour] > (currentListNode.pathLength + 1))) {
                    
                    private_path[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                    private_path[LENGHT][tempListNode->neighbour] = currentListNode.pathLength+ 1;;

                    
                    if (FLAG != 1){

                        HeapNode neighbourNode;
                        neighbourNode.node = tempListNode->neighbour;
                        neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                        neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                        neighbourNode.pathLength = currentListNode.pathLength + 1;
                        addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
                    }
                }
            }


            tempListNode = tempListNode->next;
        }
    }

    for(i= 1; i<graph->listSize; i++){
        printf("no %d tipo %d comprimento %d \n",i,  private_path[TYPE][i], private_path[LENGHT][i]);
    }
   
    // if(startVertex == inputDestVertex) {
    //     printf("The length of the path from %d to %d is %d and the type of the path is: %d\n", inputStartVertex, inputDestVertex, previousPathSize[inputStartVertex],typeOfPath[TYPE][inputStartVertex]);
    // }

    // for(int i = 1; i < graph->listSize; i++ ) {
    //     // printf("Path type: %d\n", typeOfPath[TYPE][i]);
    //     count[previousPathSize[i]]++;
    // }

    free(caminhosLegais);
    free(private_path[0]);
    free(private_path[1]);
    free(community_path[0]);
    free(community_path[1]);

}

