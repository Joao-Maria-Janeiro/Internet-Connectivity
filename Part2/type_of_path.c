#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_of_path.h"
#include "heap.h"
#include "matrice_handler.h"

int pathType(Graph * graph,int inputStartVertex ,int inputDestVertex, int* count, int flag1Time ) {
    int allocatedHeapSize = 500;
    int heapSize = 0;
    short toInsertSize = 0;
    HeapNode * heap = (HeapNode *) malloc((graph->listSize)* sizeof(HeapNode));
    
    int **caminhosLegais;
    int i = 0;
    int total_paths =0;

    caminhosLegais = (int**)malloc(sizeof(int*)*3);
    for(i= 0; i<3; i++)
        caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

    caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
    caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
    caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

    /*type of path podia ser um vetor de estrutura
    É um vetor com duas linhas e listSize tamanho
    guarda o tipo de caminho do nó = Index ao alvo e o vizinho por onde passa (via)*/
    int** typeOfPath = (int**)malloc(sizeof(int*)*2);
    for(i= 0; i<2; i++)
        typeOfPath[i] = (int*) malloc(sizeof(int)*graph->listSize);

    for(i=0; i<2; i++){
        for(int k = 0; k<graph->listSize; k++)
            typeOfPath[i][k] = 9999; //mais infinito

    }

    int TYPE = 0;
    int VIA = 1;

    if(flag1Time){
        bfsPathType(graph, inputDestVertex, inputStartVertex, inputDestVertex, heap, &heapSize, &allocatedHeapSize, count, caminhosLegais, typeOfPath);
    }
    else{
        for(int i = 0; i< graph->listSize; i++){
            if ( graph->array[i].head != NULL){
                bfsPathType(graph, i, inputStartVertex, inputDestVertex, heap, &heapSize, &allocatedHeapSize, count, caminhosLegais, typeOfPath);
                for(int k = 0; k<graph->listSize; k++){
                    if(typeOfPath[TYPE][k] != 9999){
                        total_paths ++;
                    }
                    typeOfPath[TYPE][k] = 9999;
                    typeOfPath[VIA][k] = 9999; //mais infinito
                }
            }
        }
    }

    
  	//Free arrays
    free(heap);
    for(i = 0; i<3 ; i++){
        free(caminhosLegais[i]);
    }
    free(caminhosLegais);
    for(i = 0; i<2 ; i++){
        free(typeOfPath[i]);
    }
    free(typeOfPath);

    return total_paths;
}

int caminhoInverso(int caminho){
    if(caminho == 1) return 3;
    else if(caminho == 2) return 2;
    else if(caminho == 3) return 1;
}


void bfsPathType(Graph * graph, int startVertex,int inputStartVertex, int inputDestVertex, HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count, int ** caminhosLegais, int **typeOfPath) {
    AdjListNode* tempListNode = graph->array[startVertex].head;
    HeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    currentListNode.pathLength = 0;
    addToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

    int TYPE = 0;
    int VIA = 1;
    int i;

    while((*heapSize) != 0){
        currentListNode = popFromHeap(heapSize, heap);
        
        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
           
            if(currentListNode.node == startVertex){ //so acontece da primeira vez
                //melhora o caminho do vizinho
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[VIA][tempListNode->neighbour] = startVertex;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.pathLength = 0;
                neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
            }
            //caso generico
            //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora a situação do vizinho
            else if((tempListNode->neighbour != startVertex) 
            && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) 
            && (caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]) ){
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[VIA][tempListNode->neighbour] = currentListNode.node;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.pathLength = 0;
                neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
            }

            tempListNode = tempListNode->next;
        }
    }

    if(startVertex == inputDestVertex) {
        printf("The path type from %d to %d is %d\n", inputStartVertex, inputDestVertex, typeOfPath[TYPE][inputStartVertex] );
    }
 
    for(i = 1; i < graph->listSize; i++ ) {
        
        if (typeOfPath[TYPE][i] != 9999) {
            count[typeOfPath[TYPE][i]]++;
        }
    }
}

