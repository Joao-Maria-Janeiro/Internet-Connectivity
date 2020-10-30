#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handler.h"

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


    /*
    //printGraph(graph);
    //bridges(graph);
    int connected = 0;
    connected = graphIsConnected(graph);
    printf("valor : %d\n",connected);
    int * tier0Nodes;
    int tier0Count = 0;
    int commercially_connected = 0;

    if(connected == 1){
        tier0Count = findTier0(graph, tier0Nodes);
        for(int i= 0; i<tier0Count; i++){
            printf("tier0node %d \n", tier0Nodes[i]);
        }
        printf("tier0count = %d \n", tier0Count);
        if (connected == 1){
            printf("COMERCIALMENTE CONEXA = %d \n", commerciallyConnected(graph, tier0Nodes, tier0Count));
         }
    }*/
  
    
    select_option(graph);   
    freeGraph(graph);
    free(allElements);

    return 0;
    
}
