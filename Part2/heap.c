#include <stdlib.h>
#include <stdio.h>

#include "graph_handler.h"
#include "heap.h"

#define INT_MAX 255


int getLeftChildIndex(int parentIndex){
  return 2 * parentIndex +1;
}

int getRightChildIndex(int parentIndex){
  return 2 * parentIndex +2;
}

int getParentIndex(int childIndex){
  return (childIndex - 1) / 2;
}

int hasLeftChild(int index, int size){
  if(getLeftChildIndex(index) < size){
    return 1;
  }else{
    return 0;
  }
}

int hasRightChild(int index, int size){
  if(getRightChildIndex(index) < size){
    return 1;
  }else{
    return 0;
  }
}

int hasParent(int index){
  if(getParentIndex(index) >= 0){
    return 1;
  }else{
    return 0;
  }
}

HeapNode leftChild(int index, HeapNode * items){
  return items[getLeftChildIndex(index)];
}

HeapNode rightChild(int index, HeapNode * items){
  return items[getRightChildIndex(index)];
}

HeapNode parent(int index, HeapNode * items){
  return items[getParentIndex(index)];
}

void swap(int index1, int index2, HeapNode * items){
  HeapNode temp = items[index1];
  items[index1] = items[index2];
  items[index2] = temp;
}


HeapNode popFromHeap(int *size, HeapNode * items){
  if(*size == 0){ //Caso em que o acervo está vazio damos return de -1
    HeapNode empty;
    empty.node=-1;
    empty.neighbour=-1;
    empty.previousHierarchy = INT_MAX;
    return empty;
  }else{
    //Removemos o elemento de maior prioridade e ajustamos o acervo
    HeapNode item = items[0];
    items[0] = items[*size - 1];
    (*size)--;
    heapifyDown(*size, items);
    return item;
  }
}


void addToHeap(HeapNode item, HeapNode * items, int *size, int *allocatedSize) {
  //Adicionar no último elemento do acervo
  items[*size] = item;
  (*size)++;
  heapifyUp(*size, items);
}

void heapifyUp(int size, HeapNode * items) {
  int index = size - 1;
  while((hasParent(index) == 1) && (parent(index, items)).previousHierarchy > (items[index]).previousHierarchy) {
    swap(getParentIndex(index), index, items);
    index = getParentIndex(index);
  }
  if((hasParent(index) == 1) && (parent(index, items)).previousHierarchy == (items[index]).previousHierarchy) {
    if((parent(index, items)).pathLength > (items[index]).pathLength) {
      swap(getParentIndex(index), index, items);
      index = getParentIndex(index);
    }
  }
}

void heapifyDown(int size, HeapNode * items){
  int index = 0;
  while(hasLeftChild(index, size) == 1){
    int smallerChildrenIdx = getLeftChildIndex(index);
    if((hasRightChild(index, size) == 1) && ((rightChild(index, items)).previousHierarchy < (leftChild(index, items)).previousHierarchy)){
      smallerChildrenIdx = getRightChildIndex(index);
    }

    if(items[index].previousHierarchy < items[smallerChildrenIdx].previousHierarchy){
      break;
    }else{
      swap(index, smallerChildrenIdx, items);
    }
    index = smallerChildrenIdx;
  }
}


void printHeap(int size, HeapNode * items) {
  for(int i=0; i<size; i++) {
    printf("(%d) -> %d\n", items[i].node, items[i].previousHierarchy);
  }
}







// ---- Heap for shortest paths -----




BestPathHeapNode bestPathLeftChild(int index, BestPathHeapNode * items){
  return items[getLeftChildIndex(index)];
}

BestPathHeapNode bestPathRightChild(int index, BestPathHeapNode * items){
  return items[getRightChildIndex(index)];
}

BestPathHeapNode bestPathParent(int index, BestPathHeapNode * items){
  return items[getParentIndex(index)];
}

void bestPathSwap(int index1, int index2, BestPathHeapNode * items){
  BestPathHeapNode temp = items[index1];
  items[index1] = items[index2];
  items[index2] = temp;
}


BestPathHeapNode bestPathPopFromHeap(int *size, BestPathHeapNode * items){
  if(*size == 0){ //Caso em que o acervo está vazio damos return de -1
    BestPathHeapNode empty;
    empty.node=-1;
    empty.neighbour=-1;
    empty.pathLength = INT_MAX;
    return empty;
  }else{
    //Removemos o elemento de maior prioridade e ajustamos o acervo
    BestPathHeapNode item = items[0];
    items[0] = items[*size - 1];
    (*size)--;
    bestPathHeapifyDown(*size, items);
    return item;
  }
}


void bestPathAddToHeap(BestPathHeapNode item, BestPathHeapNode * items, int *size, int *allocatedSize) {
  //Adicionar no último elemento do acervo
  items[*size] = item;
  (*size)++;
  bestPathHeapifyUp(*size, items);
}

void bestPathHeapifyUp(int size, BestPathHeapNode * items) {
  int index = size - 1;
  while((hasParent(index) == 1) && (bestPathParent(index, items)).pathLength > (items[index]).pathLength) {
    bestPathSwap(getParentIndex(index), index, items);
    index = getParentIndex(index);
  }
  if((hasParent(index) == 1) && (bestPathParent(index, items)).pathLength == (items[index]).pathLength) {
    if((bestPathParent(index, items)).previousHierarchy > (items[index]).previousHierarchy) {
      bestPathSwap(getParentIndex(index), index, items);
      index = getParentIndex(index);
    }
  }
}

void bestPathHeapifyDown(int size, BestPathHeapNode * items){
  int index = 0;
  while(hasLeftChild(index, size) == 1){
    int smallerChildrenIdx = getLeftChildIndex(index);
    if((hasRightChild(index, size) == 1) && ((bestPathRightChild(index, items)).pathLength < (bestPathLeftChild(index, items)).pathLength)){
      smallerChildrenIdx = getRightChildIndex(index);
    }

    if(items[index].pathLength < items[smallerChildrenIdx].pathLength){
      break;
    }else{
      bestPathSwap(index, smallerChildrenIdx, items);
    }
    index = smallerChildrenIdx;
  }
}


void bestPathPrintHeap(int size, BestPathHeapNode * items) {
  for(int i=0; i<size; i++) {
    printf("(%d) -> %d\n", items[i].node, items[i].pathLength);
  }
}