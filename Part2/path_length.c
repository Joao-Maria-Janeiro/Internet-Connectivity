#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path_length.h"
#include "heap.h"

#define INFINITY 65533



int pathLength(Graph * graph, int inputStartVertex, int inputDestVertex , int * count) {
    int allocatedHeapSize = graph->listSize;
    int heapSize = 0;
    short toInsertSize = 0;
    HeapNode * heap = (HeapNode *) malloc(graph->listSize* sizeof(HeapNode));

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

    for(int i = 0; i< graph->listSize; i++){
        if (i%1000 == 0) printf("iter: %d \n", i);
        if ( graph->array[i].head != NULL){
            bfsPathLength(graph, i, inputStartVertex, inputDestVertex, heap, typeOfPath, caminhosLegais);
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
    for (i= 0; i <3 ; i++){
        free(caminhosLegais[i]);
    }
    free(caminhosLegais);
    free(typeOfPath[0]);
    free(typeOfPath[1]);
    free(typeOfPath);
    free(heap);

    return total_paths;
}



/*tal como no djikstraToFindPathType, o heap guarda os nós que foram atualizados por prioridade de tipo de caminho*/
 
void *bfsPathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestinationVertex, HeapNode * heap, int ** typeOfPath, int **caminhosLegais) {

    
    int heapSize = 0;
    int allocatedHeapSize = graph->listSize;
    
    
    AdjListNode* tempListNode = graph->array[startVertex].head;
    HeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.previousHierarchy = -1;
    currentListNode.pathLength = 0;
    addToHeap(currentListNode, heap, &heapSize, &allocatedHeapSize);

    
    int TYPE = 0;
    int LENGTH = 1;



    //ESTA É A PARTE IMPORTANTE
    while((heapSize) != 0){
        currentListNode = popFromHeap(&heapSize, heap);
        tempListNode = graph->array[currentListNode.node].head;
        while (tempListNode) {
            // printf(" %d %d %d %d %d %d\n", currentListNode.node, tempListNode->neighbour, typeOfPath[LENGTH][tempListNode->neighbour] , currentListNode.pathLength + 1, caminhoInverso(tempListNode->hierarchy), typeOfPath[TYPE][tempListNode->neighbour]);
            //ve se pode melhorar os caminhos do vizinho, se os melhora, coloca-os no heap
            //verifica se pode melhorar && caminho resultante é legal
            //caso especial para o startvertex
            if(currentListNode.node == startVertex){ //so acontece da primeira vez
                //melhora o caminho do vizinho
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = 1;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = 1;
                addToHeap(neighbourNode, heap, &heapSize, &allocatedHeapSize);
            }
            //caso generico
            //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora a situação do vizinho
            else if((tempListNode->neighbour != startVertex) 
            && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) /* Valid path */
            && (caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]) ){ /* Better type of path */
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = typeOfPath[LENGTH][currentListNode.node] + 1;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy);//set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = currentListNode.pathLength + 1;
                addToHeap(neighbourNode, heap, &heapSize, &allocatedHeapSize);
            } 
            else if((tempListNode->neighbour != startVertex) 
            && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) /* Valid path */
            && (caminhoInverso(tempListNode->hierarchy) == typeOfPath[TYPE][tempListNode->neighbour]) /* Same type of path */
            && (typeOfPath[LENGTH][tempListNode->neighbour] > (currentListNode.pathLength + 1))) {  /* Shortest path */
                //melhora o caminho do vizinho
                //adiciona vizinho ao heap
                typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
                typeOfPath[LENGTH][tempListNode->neighbour] = currentListNode.pathLength + 1;
                HeapNode neighbourNode;
                neighbourNode.node = tempListNode->neighbour;
                neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy);//set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
                neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
                neighbourNode.pathLength = currentListNode.pathLength + 1;
                addToHeap(neighbourNode, heap, &heapSize, &allocatedHeapSize);
            }


            tempListNode = tempListNode->next;
        }
    }
    
    if(startVertex == inputDestinationVertex) {
        printf("The length of the path from %d to %d is %d and the type of the path is: %d\n", inputStartVertex, inputDestinationVertex, typeOfPath[LENGTH][inputStartVertex],typeOfPath[TYPE][inputStartVertex]);
    }
    
}


// void *bfsPathLength(Graph * graph, int startVertex, int inputStartVertex, int inputDestVertex , HeapNode * heap, int * heapSize, int * allocatedHeapSize, int* count) {
//     // printf("enttrou \n");
//     AdjListNode* tempListNode = graph->array[startVertex].head;
//     HeapNode currentListNode;
//     currentListNode.node = tempListNode->node;
//     currentListNode.parent = tempListNode->node;
//     currentListNode.previousHierarchy = -1;
//     currentListNode.pathLength = 0;
//     addToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

//     int * previousPathSize = (int *)malloc(graph->listSize * sizeof(int));
//     for(int i= 0; i<graph->listSize; i++){
//         previousPathSize[i] = INFINITY;
//     }
    
//     previousPathSize[startVertex] = 0;

//     int **caminhosLegais;
//     int i = 0;

//     caminhosLegais = (int**)malloc(sizeof(int*)*3);
//     for(i= 0; i<3; i++)
//         caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

//     caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
//     caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
//     caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

//     // printf("allocou bem esta matriz \n");
//     /*type of path podia ser um vetor de estrutura
//     É um vetor com duas linhas e listSize tamanho
//     guarda o tipo de caminho do nó = Index ao alvo e o vizinho por onde passa (via)*/
//     int** typeOfPath = (int**)malloc(sizeof(int*)*2);
//     for(i= 0; i<2; i++)
//         typeOfPath[i] = (int*) malloc(sizeof(int)*graph->listSize);

//     // printf("allocou bem esta vettor \n");

//     for(i=0; i<2; i++){
//         for(int k = 0; k<graph->listSize; k++)
//             typeOfPath[i][k] = 9999; //mais infinito
//     }
//     // printf("inicializou bem esta vettor \n");

//     int TYPE = 0;
//     int VIA = 1;



//     //ESTA É A PARTE IMPORTANTE
//     // printf("vai começar \n");
//     while((*heapSize) != 0){
//         currentListNode = popFromHeap(heapSize, heap);
//         // printf("popped %d \n", currentListNode.node);
//         tempListNode = graph->array[currentListNode.node].head;
//         while (tempListNode) {
            
//             if(currentListNode.node == startVertex){ //so acontece da primeira vez
//                 //melhora o caminho do vizinho
//                 previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;
//                 typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
//                 typeOfPath[VIA][tempListNode->neighbour] = startVertex;
//                 HeapNode neighbourNode;
//                 neighbourNode.node = tempListNode->neighbour;
//                 neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
//                 neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
//                 neighbourNode.pathLength = 1;
//                 addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
//             }
//             //caso generico
//             //se o vizinho não é o startvertex && caminho proposto é legal && caminho proposto melhora a situação do vizinho
//             else if((tempListNode->neighbour != startVertex) 
//                     && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) 
//                     && (caminhoInverso(tempListNode->hierarchy) < typeOfPath[TYPE][tempListNode->neighbour]) ) {
//                 //melhora o caminho do vizinho
//                 //adiciona vizinho ao heap
//                 previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;
//                 typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
//                 typeOfPath[VIA][tempListNode->neighbour] = currentListNode.node;
//                 HeapNode neighbourNode;
//                 neighbourNode.node = tempListNode->neighbour;
//                 neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
//                 neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
//                 neighbourNode.pathLength = previousPathSize[tempListNode->node] + 1;
//                 addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
//             }
//             else if((tempListNode->neighbour != startVertex) 
//                     && (caminhosLegais[caminhoInverso(tempListNode->hierarchy) -1][typeOfPath[TYPE][currentListNode.node] - 1] != 4) 
//                     && (caminhoInverso(tempListNode->hierarchy) == typeOfPath[TYPE][tempListNode->neighbour]) 
//                     && (previousPathSize[tempListNode->neighbour] > (previousPathSize[tempListNode->node] + 1))) {
//                 //melhora o caminho do vizinho
//                 //adiciona vizinho ao heap
//                 previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;
//                 typeOfPath[TYPE][tempListNode->neighbour] = caminhoInverso(tempListNode->hierarchy);
//                 typeOfPath[VIA][tempListNode->neighbour] = currentListNode.node;
//                 HeapNode neighbourNode;
//                 neighbourNode.node = tempListNode->neighbour;
//                 neighbourNode.previousHierarchy = caminhoInverso(tempListNode->hierarchy); //set neighbour's previousHierarchy as the current neighbour hierarchy, for future reference
//                 neighbourNode.parent = currentListNode.node; //set neighbour's parent as the the node where it came from
//                 neighbourNode.pathLength = previousPathSize[tempListNode->node] + 1;
//                 addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
//             }


//             tempListNode = tempListNode->next;
//         }
//     }
//     // for(i= 1; i<graph->listSize; i++){
//     //     printf("no %d tipo %d via %d \n",i,  typeOfPath[TYPE][i], typeOfPath[VIA][i]);
//     // }

//     // for(int i = 1; i < graph->listSize; i++) {
//     //     printf("%d %d %d\n", i, previousPathSize[i],typeOfPath[TYPE][i]);
//     // }
//     if(startVertex == inputDestVertex) {
//         printf("The length of the path from %d to %d is %d and the type of the path is: %d\n", inputStartVertex, inputDestVertex, previousPathSize[inputStartVertex],typeOfPath[TYPE][inputStartVertex]);
//     }

//     for(int i = 1; i < graph->listSize; i++ ) {
//         // printf("Path type: %d\n", typeOfPath[TYPE][i]);
//         if(previousPathSize[i] != 9999)
//             count[previousPathSize[i]]++;
//     }
//     free(caminhosLegais);
//     free(typeOfPath[0]);
//     free(typeOfPath[1]);
// }

// void djikstraToFindPathLength(Graph * graph, int startVertex, LengthHeapNode * heap, int * heapSize, int * allocatedHeapSize, int * count) {
//     AdjListNode* tempListNode = graph->array[startVertex].head;
//     LengthHeapNode currentListNode;
//     currentListNode.node = tempListNode->node;
//     currentListNode.parent = tempListNode->node;
//     currentListNode.pathLength = 0;
//     currentListNode.previousHierarchy = -1;
//     pathAddToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

//     int * previousPathSize = (int *)malloc(graph->listSize * sizeof(int));
//     for(int i= 0; i<graph->listSize; i++){
//         previousPathSize[i] = INFINITY;
//     }
    
//     previousPathSize[startVertex] = 0;


//     int **caminhosLegais;
//     caminhosLegais = (int**)malloc(sizeof(int*)*3);
//     for(int i = 0; i < 3; i++)
//         caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

//     caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
//     caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
//     caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

//     while ((*heapSize) != 0) {
//         currentListNode = pathPopFromHeap(heapSize, heap);
//         // printf("Error: %d\n", currentListNode.node);
//         if(previousPathSize[currentListNode.node] != INFINITY) {
//             tempListNode = graph->array[currentListNode.node].head;
//             while (tempListNode != NULL) {
//                 if(currentListNode.node == startVertex){ //so acontece da primeira vez
//                     previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;

//                     LengthHeapNode neighbourNode;
//                     neighbourNode.node = tempListNode->neighbour;
//                     neighbourNode.parent = currentListNode.node;
//                     neighbourNode.pathLength = currentListNode.pathLength + 1;
//                     currentListNode.previousHierarchy = tempListNode->hierarchy;
//                     pathAddToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);

                    
//                 }   else if ((caminhosLegais[tempListNode->hierarchy -1][currentListNode.previousHierarchy - 1] != 4) && previousPathSize[tempListNode->neighbour] > (previousPathSize[tempListNode->node] + 1)) { // If the path from the node to the source is smaller than the neighbour's, we must update it
//                     previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;

//                     LengthHeapNode neighbourNode;
//                     neighbourNode.node = tempListNode->neighbour;
//                     neighbourNode.parent = currentListNode.node;
//                     neighbourNode.pathLength = currentListNode.pathLength + 1;
//                     currentListNode.previousHierarchy = tempListNode->hierarchy;
//                     pathAddToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);

//                 }
//                 tempListNode = tempListNode->next;
//             }
//         }
//     }

//     // for(int i = 0; i < graph->listSize; i++) {
//     //     printf("%d %d\n", i, previousPathSize[i]);
//     // }

//     for(int i = 1; i < graph->listSize; i++ ) {
//         count[previousPathSize[i]]++;
//     }
    


//     free(previousPathSize);   
// }