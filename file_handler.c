#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handler.h"

int readInternetFromFile(char * fileName) {
    int tailIdentifier, headIdentifier, providerOfTheHead, nodeCounter, currentMatrixIndex = 0;
    int ** internetGraph;
    InternetNode * indexMatcher;
    // Opens the input file
    FILE * input_file = fopen(fileName, "r");
    if(input_file == NULL){
        exit(1);
    }

    indexMatcher = (InternetNode *)malloc(500 * sizeof(InternetNode));
    allocateInitialInternetGraph(internetGraph);

    while (fscanf(input_file, "%d %d %d", &tailIdentifier, &headIdentifier, &providerOfTheHead) == 3) {
        int tailIdentifierMatrixIndex = -1, headIdentifierMatrixIndex = -1;
        for(int i = 0; i < 500; i++) {
            if (indexMatcher[i].nodeValue == tailIdentifier) {
                tailIdentifierMatrixIndex = indexMatcher[i].matrixIndex;
            }
            if (indexMatcher[i].nodeValue == headIdentifier) {
                headIdentifierMatrixIndex = indexMatcher[i].matrixIndex;
            }
        }
        if (tailIdentifierMatrixIndex == -1) {
            if (headIdentifierMatrixIndex == -1) {
                indexMatcher[currentMatrixIndex].matrixIndex = currentMatrixIndex;
                indexMatcher[currentMatrixIndex].nodeValue = tailIdentifier;  
                currentMatrixIndex ++;  
            }
            // internetGraph[currentMatrixIndex]
            currentMatrixIndex ++;
        }
    }
}

void allocateInitialInternetGraph(int ** internetGraph) {
    internetGraph = (int **)malloc(500 * sizeof(int *));
    for (int i = 0; i < 500; i++) {
        internetGraph[i] = (int *)malloc(500 * sizeof(int));
    }
}
