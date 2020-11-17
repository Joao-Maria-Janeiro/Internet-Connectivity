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

