#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path_length.h"
#include "heap.h"

#define INFINITY 65533



int pathLength(Graph * graph, int startVertex, int * count) {
    int allocatedHeapSize = 500;
    int heapSize = 0;
    short toInsertSize = 0;
    //Todo(): Make function to free heap
    LengthHeapNode * heap = (LengthHeapNode *) malloc(500* sizeof(LengthHeapNode));

    int * parent = (int *)malloc(graph->listSize * sizeof(int)); // Array that tells the node where we came from
    
    //Array initialization
    for(int i = 0; i< graph->listSize; i++) {
      parent[i] = -1;
      
    }

    parent[startVertex] = startVertex;

    //djikstraToFindPathType(graph, startVertex, endVertex, parent, previousHierarchy, heap, &heapSize, &allocatedHeapSize, count, commercially_Connected);
    djikstraToFindPathLength(graph, startVertex, heap, &heapSize, &allocatedHeapSize, count);

    
  	//Free arrays
    free(parent);
    free(heap);
}


void djikstraToFindPathLength(Graph * graph, int startVertex, LengthHeapNode * heap, int * heapSize, int * allocatedHeapSize, int * count) {
    AdjListNode* tempListNode = graph->array[startVertex].head;
    LengthHeapNode currentListNode;
    currentListNode.node = tempListNode->node;
    currentListNode.parent = tempListNode->node;
    currentListNode.pathLength = 0;
    currentListNode.previousHierarchy = -1;
    pathAddToHeap(currentListNode, heap, heapSize, allocatedHeapSize);

    int * previousPathSize = (int *)malloc(graph->listSize * sizeof(int));
    for(int i= 0; i<graph->listSize; i++){
        previousPathSize[i] = INFINITY;
    }
    
    previousPathSize[startVertex] = 0;


    int **caminhosLegais;
    caminhosLegais = (int**)malloc(sizeof(int*)*3);
    for(int i = 0; i < 3; i++)
        caminhosLegais[i] = (int*) malloc(sizeof(int)*3);

    caminhosLegais[0][0] = 1; caminhosLegais[0][1] = 4; caminhosLegais[0][2] = 4;
    caminhosLegais[1][0] = 2; caminhosLegais[1][1] = 4; caminhosLegais[1][2] = 4;
    caminhosLegais[2][0] = 3; caminhosLegais[2][1] = 3; caminhosLegais[2][2] = 3;

    while ((*heapSize) != 0) {
        currentListNode = pathPopFromHeap(heapSize, heap);
        // printf("Error: %d\n", currentListNode.node);
        if(previousPathSize[currentListNode.node] != INFINITY) {
            tempListNode = graph->array[currentListNode.node].head;
            while (tempListNode != NULL) {
                if(currentListNode.node == startVertex){ //so acontece da primeira vez
                    previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;

                    LengthHeapNode neighbourNode;
                    neighbourNode.node = tempListNode->neighbour;
                    neighbourNode.parent = currentListNode.node;
                    neighbourNode.pathLength = currentListNode.pathLength + 1;
                    currentListNode.previousHierarchy = tempListNode->hierarchy;
                    pathAddToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);

                    if ((*heapSize) >= (*allocatedHeapSize)) {
                        heap = (LengthHeapNode *)realloc(heap, (*allocatedHeapSize+250) * sizeof(LengthHeapNode));
                        (allocatedHeapSize) += 250;
                    }
                }   else if ((caminhosLegais[tempListNode->hierarchy -1][currentListNode.previousHierarchy - 1] != 4) && previousPathSize[tempListNode->neighbour] > (previousPathSize[tempListNode->node] + 1)) { // If the path from the node to the source is smaller than the neighbour's, we must update it
                    previousPathSize[tempListNode->neighbour] = previousPathSize[tempListNode->node] + 1;

                    LengthHeapNode neighbourNode;
                    neighbourNode.node = tempListNode->neighbour;
                    neighbourNode.parent = currentListNode.node;
                    neighbourNode.pathLength = currentListNode.pathLength + 1;
                    currentListNode.previousHierarchy = tempListNode->hierarchy;
                    pathAddToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);

                    if ((*heapSize) >= (*allocatedHeapSize)) {
                        heap = (LengthHeapNode *)realloc(heap, (*allocatedHeapSize+250) * sizeof(LengthHeapNode));
                        (allocatedHeapSize) += 250;
                    }
                }
                tempListNode = tempListNode->next;
            }
        }
    }

    for(int i = 0; i < graph->listSize; i++) {
        printf("%d %d\n", i, previousPathSize[i]);
    }

    for(int i = 1; i < graph->listSize; i++ ) {
        count[previousPathSize[i]]++;
    }
    


    free(previousPathSize);   
}