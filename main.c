#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_handler.h"

int checkFileName(int argc, char * fileName);

int main(int argc, char *argv[]) {
    if (checkFileName(argc, argv[1]) == 0) {
        printf("Filename is incorrect\n");
        exit(1);
    }
    readInternetFromFile(argv[1]);
        
}


int checkFileName(int argc, char * fileName) {
    if(argc == 1){
        // printf("You must provide a input file\n");
        exit(1);
    }
    if(argc >= 3){
        // printf("Too many arguments\n");
        exit(1);
    }
    if(strstr(fileName, ".inet") == 0) {
        // printf("Wrong file extension");
        exit(1);
    }
}


