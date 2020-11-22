#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_of_path.h"
#include "heap.h"
#include "matrice_handler.h"

int pathType(Graph * graph, int startVertex, int endVertex, int* count, int commercially_Connected) {
    int allocatedHeapSize = 500;
    int heapSize = 0;
    short toInsertSize = 0;
    //Todo(): Make function to free heap
    HeapNode * heap = (HeapNode *) malloc(500* sizeof(HeapNode));

    int * parent = (int *)malloc(graph->listSize * sizeof(int)); // Array that tells the node where we came from
    int * previousHierarchy = (int *)malloc(graph->listSize * sizeof(int)); // Array that tells the hierarchy of the edge where we came from
    
    //Array initialization
    for(int i = 0; i< graph->listSize; i++) {
      parent[i] = -1;
      previousHierarchy[i] = -1;
    }

    parent[startVertex] = startVertex;
    previousHierarchy[startVertex] = 0;

    //djikstraToFindPathType(graph, startVertex, endVertex, parent, previousHierarchy, heap, &heapSize, &allocatedHeapSize, count, commercially_Connected);
    bfsPathType(graph, startVertex, heap, &heapSize, &allocatedHeapSize, count);

    
  	//Free arrays
    free(parent);
    free(previousHierarchy);
    free(heap);
}

int caminhoInverso(int caminho){
    if(caminho == 1) return 3;
    else if(caminho == 2) return 2;
    else if(caminho == 3) return 1;
}


/*tal como no djikstraToFindPathType, o heap guarda os nós que foram atualizados por prioridade de tipo de caminho*/
void *bfsPathType(Graph * graph, int startVertex, HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count) {
    // printf("enttrou \n");
    AdjListNode* tempListNode = graph->array[startVertex].head;
    HeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    addToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

    int **caminhosLegais;
    int i = 0;

    caminhosLegais = (int**)malloc(sizeof(int*)*3);
    for(i= 0; i<3; i++)
        caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

    caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
    caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
    caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

    // printf("allocou bem esta matriz \n");
    /*type of path podia ser um vetor de estrutura
    É um vetor com duas linhas e listSize tamanho
    guarda o tipo de caminho do nó = Index ao alvo e o vizinho por onde passa (via)*/
    int** typeOfPath = (int**)malloc(sizeof(int*)*2);
    for(i= 0; i<2; i++)
        typeOfPath[i] = (int*) malloc(sizeof(int)*graph->listSize);

    // printf("allocou bem esta vettor \n");

    for(i=0; i<2; i++){
        for(int k = 0; k<graph->listSize; k++)
            typeOfPath[i][k] = 9999; //mais infinito
    }
    // printf("inicializou bem esta vettor \n");

    int TYPE = 0;
    int VIA = 1;



    //ESTA É A PARTE IMPORTANTE
    // printf("vai começar \n");
    while((*heapSize) != 0){
        currentListNode = popFromHeap(heapSize, heap);
        // printf("popped %d \n", currentListNode.node);
        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
            //ve se pode melhorar os caminhos do vizinho, se os melhora, coloca-os no heap
            //verifica se pode melhorar && caminho resultante é legal
            //caso especial para o startvertex

            printf("%d\n", tempListNode->neighbour != startVertex);
            printf("%d %d %d %d\n", tempListNode->hierarchy, currentListNode.node, tempListNode->neighbour, startVertex);
            printf("%d %d\n", typeOfPath[TYPE][currentListNode.node] -1, caminhoInverso(tempListNode->hierarchy) -1);
            printf("%d\n", caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]);
            printf("%d\n", caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1]);


            if(currentListNode.node == startVertex){ //so acontece da primeira vez
                //melhora o caminho do vizinho
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[VIA][tempListNode->neighbour] = startVertex;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
            }
            //caso generico
            //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora a situação do vizinho
            else if((tempListNode->neighbour != startVertex) && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) && (caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]) ){
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[VIA][tempListNode->neighbour] = currentListNode.node;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
            }


            tempListNode = tempListNode->next;
        }
    }
    // for(i= 1; i<graph->listSize; i++){
    //     printf("no %d tipo %d via %d \n",i,  typeOfPath[TYPE][i], typeOfPath[VIA][i]);
    // }

    for(int i = 1; i < graph->listSize; i++ ) {
        // printf("Path type: %d\n", typeOfPath[TYPE][i]);
        if (typeOfPath[TYPE][i] != 9999) {
            count[typeOfPath[TYPE][i]]++;
        }
    }
}

int* djikstraToFindPathType(Graph * graph, int startVertex, int endVertex, int * parent, int * pathTypeArray, HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count, int commercially_Connected) {
    AdjListNode* tempListNode = graph->array[startVertex].head;
    HeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    addToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

    int * visited = (int*) malloc(sizeof(int)*graph->listSize);
    for(int i= 0; i<graph->listSize; i++){
        visited[i] = -1;
    }

    while((*heapSize) != 0) {
        //printHeap(*heapSize, heap);
        currentListNode = popFromHeap(heapSize, heap);
       
        // printf("popped %d \n", currentListNode.node);
        visited[currentListNode.node] += 1;

        //CAN'T REACH 2!!!!!!!!!!

        // TODO(): On path3 the visited restriction does not allow us to find the best path for the node 2. This path must pass node 1 that is already visited and won't be visited again


        if(visited[currentListNode.node] == 0){ //only executes 1 time, the first time
            //printf("currListnode %d \t parent %d \t pathtype Parent %d \n", currentListNode.node, currentListNode.parent,pathTypeArray[currentListNode.parent] );
            //once we have popped the node from the heap we know that the "optimum" path was taken:
            if((pathTypeArray[currentListNode.parent] == 0) && (currentListNode.parent != currentListNode.node)){ //startvertex's neighbours
                // printf("vizinhos do startvertex, current %d \n", currentListNode.node);
                pathTypeArray[currentListNode.node] = currentListNode.previousHierarchy;
            }
            else{
                pathTypeArray[currentListNode.node] = pathTypeArray[currentListNode.parent]; //propagate path type from parent
            }
            parent[currentListNode.node] = currentListNode.parent;//define node's best parent
        }
        // printf("pathrype atualizado %d visited %d %d\n", pathTypeArray[currentListNode.node], visited[currentListNode.node], currentListNode.parent);
    

        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
             if ((visited[tempListNode->neighbour] <5) && (tempListNode->neighbour != currentListNode.parent)) {
                 // If this is true this node has never been visited
            
                // // For the neighbours of the startvertex
                // if (currentListNode.previousHierarchy == -1) {
                //     printf("63 ATENTAI neighbour %d %d \n", tempListNode->neighbour, currentListNode.node);
                //     pathTypeArray[tempListNode->neighbour] = tempListNode->hierarchy;
                // }
                if ((currentListNode.previousHierarchy == 1) && (tempListNode->hierarchy == 2) // c/r
                || (currentListNode.previousHierarchy == 1) && (tempListNode->hierarchy == 3)  // c/p
                || (currentListNode.previousHierarchy == 2) && (tempListNode->hierarchy == 2)  // r/r
                || (currentListNode.previousHierarchy == 2) && (tempListNode->hierarchy == 3)  // r/p
                ) { //if the move is ilegal, skip to next neighbour, disregarding this path
                    // printf("neighbour %d \n", tempListNode->neighbour);
                    tempListNode = tempListNode->next;
                    continue;
                } else { //the move is legal
                    if ((*heapSize) >= (*allocatedHeapSize)) {
                        heap = (HeapNode *)realloc(heap, (*allocatedHeapSize+250) * sizeof(HeapNode));
                        (*allocatedHeapSize) += 250;
                    }
                    HeapNode neighbourNode;
                    neighbourNode.node = tempListNode->neighbour;
                    neighbourNode.previousHierarchy = tempListNode->hierarchy; //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                    neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                    addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);

                    // printf(" 75 Adicionado à heap %d peso %d \n", neighbourNode.node, neighbourNode.previousHierarchy);
                    // printHeap(*heapSize, heap);
                }
                tempListNode = tempListNode->next;
            }
            else
            {
                tempListNode = tempListNode->next;
            }
            

        }
    }
    //TODO(): Commercially connected
    for(int i = 1; i < graph->listSize; i++ ) {
        if ( graph->array[i].head != NULL){
            if(visited[i] == -1){
                if(commercially_Connected == 1){// TODO(): Switch for commercially connected flag
                    pathTypeArray[i] = 3;
                }
                else{
                    pathTypeArray[i]  = 4;
                }
            }
            
        }
        // printf("Path type: %d\n", pathTypeArray[i]);
        count[pathTypeArray[i]]++;
        
    }
    free(visited);

    // printf("Reached the end");
}

