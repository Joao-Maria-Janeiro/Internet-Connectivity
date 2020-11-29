#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path_length.h"
#include "heap.h"

#define INFINITY 65533



int pathLength(Graph * graph, int inputStartVertex, int inputDestVertex , int * count, int flag1Time) {
    int allocatedHeapSize = graph->listSize;
   
    short toInsertSize = 0;
    BestPathHeapNode * heapType1 = (BestPathHeapNode *) malloc((2*graph->listSize)* sizeof(BestPathHeapNode));
    BestPathHeapNode * heapType2 = (BestPathHeapNode *) malloc((2*graph->listSize)* sizeof(BestPathHeapNode));
    BestPathHeapNode * heapType3 = (BestPathHeapNode *) malloc((3*graph->listSize)* sizeof(BestPathHeapNode));

    int **caminhosLegais;
    int i = 0;
    int total_paths =0;

    caminhosLegais = (int**)malloc(sizeof(int*)*3);
    for(i= 0; i<3; i++)
        caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

    caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
    caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
    caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

    int** typeOfPath = (int**)malloc(sizeof(int*)*2);
    for(i= 0; i<2; i++)
        typeOfPath[i] = (int*) malloc(sizeof(int)*graph->listSize);

    int k = 0;

    for(i=0; i<2; i++){
        for(k = 0; k<graph->listSize; k++)
            typeOfPath[i][k] = 9999; //mais infinito

    }
    int TYPE = 0;
    int LENGTH = 1;

    if(flag1Time){
        bfsPathLength(graph, inputDestVertex, inputStartVertex, inputDestVertex, heapType1, heapType2, heapType3, typeOfPath, caminhosLegais);
    }
    else{
        for(int i = 0; i< graph->listSize; i++){
            if ( graph->array[i].head != NULL){
                bfsPathLength(graph, i, inputStartVertex, inputDestVertex, heapType1, heapType2, heapType3, typeOfPath, caminhosLegais);
                for(k = 0; k<graph->listSize; k++){
                    if(typeOfPath[LENGTH][k] != 9999){
                        count[typeOfPath[LENGTH][k]] += 1;
                        total_paths ++;
                    }
                    typeOfPath[TYPE][k] = 9999;
                    typeOfPath[LENGTH][k] = 9999; //mais infinito
                }

            }
        }
    }

    for (i= 0; i <3 ; i++){
        free(caminhosLegais[i]);
    }
    free(caminhosLegais);
    free(typeOfPath[0]);
    free(typeOfPath[1]);
    free(typeOfPath);
    free(heapType1);
    free(heapType2);
    free(heapType3);

    return total_paths;
}

 
void *bfsPathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestinationVertex, BestPathHeapNode * heap1,BestPathHeapNode * heap2, BestPathHeapNode* heap3 ,int ** typeOfPath, int **caminhosLegais) {

    
    int heapSize1 = 0;
    int heapSize2 = 0;
    int heapSize3 = 0;
    int allocatedHeapSize = graph->listSize;
    
    
    AdjListNode* tempListNode = graph->array[startVertex].head;
    BestPathHeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    currentListNode.pathLength = 0;
    bestPathAddToHeap(currentListNode, heap1, &heapSize1, &allocatedHeapSize);

    
    int TYPE = 0;
    int LENGTH = 1;



    while(((heapSize1) != 0) || ((heapSize2) != 0) || ((heapSize3) != 0)){
        if(heapSize1 != 0){
            currentListNode = bestPathPopFromHeap(&heapSize1, heap1);
        }
        else if (heapSize2 != 0){
            currentListNode = bestPathPopFromHeap(&heapSize2, heap2);
        }
        else {
            currentListNode = bestPathPopFromHeap(&heapSize3, heap3);
        }
        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
            //ve se pode melhorar os caminhos do vizinho, se os melhora, coloca-os no heap
            //verifica se pode melhorar && caminho resultante é legal
            //caso especial para o startvertex
            if(currentListNode.node == startVertex){ //so acontece da primeira vez
                //melhora o caminho do vizinho
                
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = 1;
                BestPathHeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = 1;
                if(typeOfPath[TYPE][tempListNode->neighbour]== 1){
                    bestPathAddToHeap(neighbourNode, heap1, &heapSize1, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 2){
                    bestPathAddToHeap(neighbourNode, heap2, &heapSize2, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 3){
                    bestPathAddToHeap(neighbourNode, heap3, &heapSize3, &allocatedHeapSize);
                }
  
            }
            //caso generico 
            //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora a situação do vizinho
            else if((tempListNode->neighbour != startVertex) 
            && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) /* Valid path */
            && (caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]) ){ /* Better type of path */
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = currentListNode.pathLength + 1;
                BestPathHeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy);//set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = currentListNode.pathLength + 1;
                if(typeOfPath[TYPE][tempListNode->neighbour]== 1){
                    bestPathAddToHeap(neighbourNode, heap1, &heapSize1, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 2){
                    bestPathAddToHeap(neighbourNode, heap2, &heapSize2, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 3){
                    bestPathAddToHeap(neighbourNode, heap3, &heapSize3, &allocatedHeapSize);
                }
            } 
            else if((tempListNode->neighbour != startVertex) 
            && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) /* Valid path */
            && (caminhoInverso(tempListNode->hierarchy) == typeOfPath[TYPE][tempListNode->neighbour]) /* Same type of path */
            && (typeOfPath[LENGTH][tempListNode->neighbour] > (typeOfPath[LENGTH][currentListNode.node] + 1))) {  /* Shortest path */
               
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = currentListNode.pathLength + 1;
                BestPathHeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy);//set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = currentListNode.pathLength + 1;
                
                if(typeOfPath[TYPE][tempListNode->neighbour]== 1){
                    bestPathAddToHeap(neighbourNode, heap1, &heapSize1, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 2){
                    bestPathAddToHeap(neighbourNode, heap2, &heapSize2, &allocatedHeapSize);
                }
                else if(typeOfPath[TYPE][tempListNode->neighbour]== 3){
                    bestPathAddToHeap(neighbourNode, heap3, &heapSize3, &allocatedHeapSize);
                }
            }


            tempListNode = tempListNode->next;
        }
    }
    
    if(startVertex == inputDestinationVertex) {
        printf("The length of the path from %d to %d is %d and the type of the path is: %d\n", inputStartVertex, inputDestinationVertex, typeOfPath[LENGTH][inputStartVertex],typeOfPath[TYPE][inputStartVertex]);
    }

   
}


