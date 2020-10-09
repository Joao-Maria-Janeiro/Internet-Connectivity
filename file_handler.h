#ifndef _FILE_H
#define _FILE_H

typedef struct {
    int matrixIndex;
    int nodeValue;
} InternetNode;

int readInternetFromFile(char *);
void allocateInitialInternetGraph(int **);

#endif