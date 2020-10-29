#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matrixIndex;
    int nodeValue;
} InternetNode;


typedef struct Conn {
    int node;
    int neighbour;
    int hierarchy;
    struct InternetConnection * prev;
    struct InternetConnection * next;
} InternetConnection;


// A structure to represent an adjacency list node
typedef struct AdjListNode {
    int node;
    int neighbour;
    int hierarchy;
    struct AdjListNode* next;
    // struct AdjListNode* prev;
} AdjListNode;
 
// A structure to represent an adjacency liat
typedef struct AdjList {
    struct AdjListNode *head; // pointer to head node of list
} AdjList;
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
typedef struct Graph {
    int V;
    int E;
    int listSize;
    struct AdjList* array;
} Graph;


int hash1(int key, int n);
int hash2(int key);
int getHash(Graph * graph, int node);
int countDistinctElements(int * arr, int n);
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void radixsort(int arr[], int n);
void addEdge(struct Graph* graph, int node, int neighour, int hierarchy);
struct AdjListNode* newAdjListNode(int node, int neighbour, int hierarchy);
struct Graph* createGraph(int V, int E, int maxElement);
void printGraph(Graph* graph);
int get_biggest_prime(int n);

#endif 