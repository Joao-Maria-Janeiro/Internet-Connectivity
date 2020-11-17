#ifndef _STACK_H
#define _STACK_H

#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>

// A structure to represent a stack 
typedef struct Stack { 
    int top; 
    int capacity; 
    int* array; 
} Stack; 

struct Stack* createStack(int capacity);
int isFull(struct Stack* stack);
int stackIsEmpty(struct Stack* stack);
void push(struct Stack* stack, int item);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
  

#endif 