
#include "graph_handler.h"
#define PRIME 3


void printGraph(Graph* graph) {
    int v;
    for (v = 0; v < graph->listSize; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        if (pCrawl != NULL) {
            printf("\n Adjacency list of vertex %d\n head ", pCrawl->node);
            while (pCrawl) {
                printf("-> %d", pCrawl->neighbour);
                pCrawl = pCrawl->next;
            }
            printf("\n");
        }
    }
}

int countDistinctElements(int * arr, int n) {
    radixsort(arr, n);
    
    int res = 0; 
    for (int i = 0; i < n; i++) {  
        while (i < n - 1 && arr[i] == arr[i + 1]) 
            i++;
        res++; 
    }
    return res; 
}

// A utility function to get maximum value in arr[] 
int getMax(int arr[], int n)  { 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 
  
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp)  { 
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(int arr[], int n)  { 
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
}

// function to calculate first hash 
int hash1(int key, int n) { 
    return (key % n); 
} 

// function to calculate second hash 
int hash2(int key) { 
    return (PRIME - (key % PRIME)); 
} 

int getHash(Graph * graph, int node) { 
    // get index from first hash 
    int index = hash1(node, graph->V); 

    if (graph->array[index].head == NULL) {
        return index;
    } else {
        if (graph->array[index].head->node == node) {
            return index;
        } else {
            int index2 = hash2(node); 
            int i = 1; 
            while (1) {
                // get newIndex 
                int newIndex = (index + i * index2) % graph->V; 

                // if no collision occurs, store 
                // the key 
                if (graph->array[newIndex].head == NULL) { 
                    return newIndex;
                } else if (graph->array[newIndex].head->node == node) {
                    return newIndex;
                }
                i++; 
            } 
        }
    }
} 


// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int node, int neighour, int hierarchy) {
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(node, neighour, hierarchy);
    // int index = getHash(graph, node);
    int index = node;
    newNode->next = graph->array[index].head;
    graph->array[index].head = newNode;
}

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int node, int neighbour, int hierarchy) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->node = node;
    newNode->neighbour = neighbour;
    newNode->hierarchy = hierarchy;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V, int E, int maxElement) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->listSize = (maxElement + 1);
 
    // Create an array of adjacency lists.  Size of array will be of the size of the biggest element
    graph->array = (struct AdjList*) malloc((maxElement + 1) * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < (maxElement + 1); ++i)
        graph->array[i].head = NULL;
 
    return graph;
}

void freeGraph(Graph* graph){
    AdjListNode* temp;

    for(int j = 0; j< graph->listSize; j++){
        while(graph->array[j].head!= NULL){
            temp = graph->array[j].head;
            graph->array[j].head = graph->array[j].head->next;
            free(temp);
        }
    }

    free(graph->array);
    free(graph);


    
}