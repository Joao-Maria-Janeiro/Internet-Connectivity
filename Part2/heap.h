#ifndef _HEAP_H
#define _HEAP_H

#include "graph_handler.h"


// A structure to represent an adjacency list node
typedef struct HeapNode {
    int node;
    int neighbour;
    int parent;
    int previousHierarchy;
} HeapNode;


int getLeftChildIndex(int parentIndex);
int getRightChildIndex(int parentIndex);
int getParentIndex(int childIndex);


int hasLeftChild(int index, int size);
int hasRightChild(int index, int size);
int hasParent(int index);


HeapNode leftChild(int index, HeapNode * items);
HeapNode rightChild(int index, HeapNode * items);
HeapNode parent(int index, HeapNode * items);


void swap(int index1, int index2, HeapNode * items);

HeapNode popFromHeap(int *size, HeapNode * items);


void addToHeap(HeapNode item, HeapNode * items, int *size, int *allocatedSize);

void heapifyUp(int size, HeapNode * items);

void heapifyDown(int size, HeapNode * items);

void printHeap(int size, HeapNode * items);



#endif