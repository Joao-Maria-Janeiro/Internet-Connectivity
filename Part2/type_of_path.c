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

    while((*heapSize) != 0) {
        printHeap(*heapSize, heap);
        currentListNode = popFromHeap(heapSize, heap);
        if (parent[currentListNode.node] != -1) { // If this is true this node has never been visited
            tempListNode = graph->array[currentListNode.node].head;
            while (tempListNode) {
                // TODO() define the path type
                // if (currentListNode.previousHierarchy == -1) {
                //     pathTypeArray[currentListNode.node] = tempListNode->hierarchy;
                // }
                if ((currentListNode.previousHierarchy == 1) && (tempListNode->hierarchy == 2) // c/r
                || (currentListNode.previousHierarchy == 1) && (tempListNode->hierarchy == 3)  // c/p
                || (currentListNode.previousHierarchy == 2) && (tempListNode->hierarchy == 2)  // r/r
                || (currentListNode.previousHierarchy == 2) && (tempListNode->hierarchy == 3)  // r/p
                ) {
                    tempListNode = tempListNode->next;
                    continue;
                } else {
                    if ((*heapSize) >= (*allocatedHeapSize)) {
                        heap = (HeapNode *)realloc(heap, (*allocatedHeapSize+250) * sizeof(HeapNode));
                        (*allocatedHeapSize) += 250;
                    }
                    HeapNode neighbourNode;
                    neighbourNode.node = tempListNode->neighbour;
                    neighbourNode.previousHierarchy = tempListNode->hierarchy;
                    neighbourNode.parent = currentListNode.node;
                    addToHeap(neighbourNode, heap, heapSize, allocatedHeapSize);
                }
                tempListNode = tempListNode->next;
            }
            parent[currentListNode.node] = currentListNode.parent;
            pathTypeArray[currentListNode.node] = currentListNode.parent;
        }
    }

    for(int i = 0; i <= 5; i++ ) {
        printf("Path type: %d\n", pathTypeArray[i]);
    }

    printf("Reached the end");
}

