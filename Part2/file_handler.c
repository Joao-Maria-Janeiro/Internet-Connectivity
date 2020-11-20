#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handler.h"
#include "type_of_path.h"
#include "commercially_connected.h"
// Used in second hash function. 



int readInternetFromFile(char * fileName) {
    int tailIdentifier = 0, headIdentifier =0, providerOfTheHead = 0, edges = 0;
    FILE *input_file;
    int * allElements = (int *)malloc(500 * sizeof(int));
    int reallocs = 0;
    int maxElement = 0;

    input_file = fopen(fileName,"r");
    while (fscanf(input_file, "%d %d %d", &tailIdentifier, &headIdentifier, &providerOfTheHead) == 3 ) {
        if (edges >= reallocs * 500) {
            reallocs ++;
            allElements = (int *)realloc(allElements, reallocs * 500 * sizeof(int)); 
        }
        if (tailIdentifier > maxElement) {
            maxElement = tailIdentifier;
        }
        allElements[edges++] = tailIdentifier;
    }

    fclose(input_file);

    input_file = fopen(fileName,"r");

    int nodes = countDistinctElements(allElements, edges); // Radix Sort is O(n)
    struct Graph* graph = createGraph(nodes, edges/2, maxElement);
    

    while (fscanf(input_file, "%d %d %d", &tailIdentifier, &headIdentifier, &providerOfTheHead) == 3 ) {
        addEdge(graph, tailIdentifier, headIdentifier, providerOfTheHead);
    }
    fclose(input_file);

    int count[5];
    float totalCount = 0;
    for(int i = 0; i < 5; i++){
        count[i] = 0;
    }

    // pathType(graph, 4, 3, count);

    // printGraph(graph);
    int commercially_Connected = 0;
    int * tier1Nodes = (int*)malloc(graph->listSize * sizeof(int));
    int tier1Count = 0;

    
    tier1Count = findTier1(graph, tier1Nodes);
    commercially_Connected = commerciallyConnected(graph, tier1Nodes, tier1Count);   
    
    for(int i = 0; i< graph->listSize; i++){
        if ( graph->array[i].head != NULL){
            pathType(graph, i, 3, count,commercially_Connected);
        }
        
    }
    printf("\n");
    for(int i = 0; i < 5; i++){
        totalCount += count[i];
    }

    for(int i = 1; i < 5; i++){
        printf( " %d: %f ",i, count[i]/totalCount );
        for(int j = 0; j < count[i]; j++){
            printf( "| ");
            
        }
        printf("\n");
    }
    printf("\n");

    // select_option(graph);   
    freeGraph(graph);
    free(allElements);
    free(tier1Nodes);

    return 0;
    
}
