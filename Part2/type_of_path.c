#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_of_path.h"
#include "heap.h"


int pathType(Graph * graph, int startVertex, int endVertex) {
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

    djikstraToFindPathType(graph, startVertex, endVertex, parent, previousHierarchy, heap, &heapSize, &allocatedHeapSize);


    
  	//Free arrays
    free(parent);
    free(previousHierarchy);

}

int djikstraToFindPathType(Graph * graph, int startVertex, int endVertex, int * parent, int * pathTypeArray, HeapNode * heap, int * heapSize, int * allocatedHeapSize) {
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
        printf("popped %d \n", currentListNode.node);
        visited[currentListNode.node] += 1;

        //CAN'T REACH 2!!!!!!!!!!

        // TODO(): On path3 the visited restriction does not allow us to find the best path for the node 2. This path must pass node 1 that is already visited and won't be visited again


        if(visited[currentListNode.node] == 0){ //only executes 1 time, the first time
            //printf("currListnode %d \t parent %d \t pathtype Parent %d \n", currentListNode.node, currentListNode.parent,pathTypeArray[currentListNode.parent] );
            //once we have popped the node from the heap we know that the "optimum" path was taken:
            if((pathTypeArray[currentListNode.parent] == 0) && (currentListNode.parent != currentListNode.node)){ //startvertex's neighbours
                printf("vizinhos do startvertex, current %d \n", currentListNode.node);
                pathTypeArray[currentListNode.node] = currentListNode.previousHierarchy;
            }
            else{
                pathTypeArray[currentListNode.node] = pathTypeArray[currentListNode.parent]; //propagate path type from parent
            }
            parent[currentListNode.node] = currentListNode.parent;//define node's best parent
        }
        printf("pathrype atualizado %d visited %d %d\n", pathTypeArray[currentListNode.node], visited[currentListNode.node], currentListNode.parent);
    

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

                    printf(" 75 Adicionado à heap %d peso %d \n", neighbourNode.node, neighbourNode.previousHierarchy);
                    printHeap(*heapSize, heap);
                }
                tempListNode = tempListNode->next;
            }
            else
            {
                tempListNode = tempListNode->next;
            }
            

        }
    }

    for(int i = 1; i < graph->listSize; i++ ) {
        printf("Path type: %d\n", pathTypeArray[i]);
    }

    printf("Reached the end");
}

