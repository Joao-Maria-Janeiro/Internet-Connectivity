
#include "menus.h"
#include "type_of_path.h"
#include "path_length.h"
#include "best_path.h"

void select_option(Graph* graph){

    int option = 0;
    float totalCount = 0; 
    
    do{
        
        printf("Select your option:\n");
        printf("1.Determine path type \n");
        printf("2.Determine path length \n");
        printf("3.Determine the fastest path \n");
        printf("4.Exit Programm \n\n");

       
        scanf("%d", &option);
        int Connected_Value = 0;
        int connected = 0;
        int inputStartVertex = 0;
        int inputDestVertex = 0;
        switch(option) {

            case 1:
                system("clear");
                
                int count[5];
                
                for(int i = 0; i < 5; i++){
                    count[i] = 0;
                }
                int option_1 = 0;
                

                printf("Select your option:\n");
                printf("1.From 1 node to another\n");
                printf("2.Stats from all pairs\n");
                printf("3.Change Mode\n");
                scanf( "%d", &option_1);

                switch (option_1){
               
                case 1:
                    system("clear");
                    printf("Select your start vertex:");
                    scanf( "%d", &inputStartVertex);
                    printf("Select your destination vertex:");
                    scanf( "%d", &inputDestVertex);

                    pathType(graph,inputStartVertex , inputDestVertex,  count,  /*flag1time =*/1);
                   
                    break;
                
                case 2:
                
                    totalCount = pathType(graph,inputStartVertex , inputDestVertex,  count,  /*flag1time =*/0);
                    printf("The Path Statistics for this Graph is:\n");
                    printf("\n");
                   

                    for(int i = 1; i < 5; i++){
                        printf( " %d: %f ",i, count[i]/totalCount );
                        printf("\n");
                    }
                    printf("\n");
                    
                    break;
                case 3:
                    break;
                
                }
                
                break;
                
            case 2:
                system("clear");

                int *countLength = (int*)malloc(sizeof(int) * (graph->listSize));
                
                for(int i = 0; i < graph->listSize; i++){
                    countLength[i] = 0;
                }
                int option_2 = 0;

                printf("Select your option:\n");
                printf("1.From 1 node to another\n");
                printf("2.Stats from all pairs\n");
                printf("3.Change Mode\n");
                scanf( "%d", &option_2);

                switch(option_2) {
                
               
                case 1:
                    system("clear");
                    printf("Select your start vertex:");
                    scanf( "%d", &inputStartVertex);
                    printf("Select your destination vertex:");
                    scanf( "%d", &inputDestVertex);

                    pathLength(graph, inputStartVertex,inputDestVertex,countLength, /*flag1time =*/1); 
                    break;

                case 2:
                    totalCount = pathLength(graph, inputStartVertex,inputDestVertex,countLength,/*flag1time =*/ 0);
                    for(int i = 1; i < graph->listSize; i++){
                        if (countLength[i] != 0) {
                            int sum = 0;
                            for(int j = 1; j <= i; j++){
                                sum += countLength[j];
                            }
                            printf("sum %d \n", sum);
                            printf( " %d: %f ",i, (1-(sum/totalCount)) );
                            printf("\n");
                        }
                    }
                    printf("\n");
                    break;
                case 3:
                    break;
                }
                free(countLength);
                break;

            case 3:
                system("clear");
                int option_3 = 0;
                int *countLengthBestPath = (int*)malloc(sizeof(int) * (graph->listSize));
                for(int i = 0; i < graph->listSize; i++){
                    countLengthBestPath[i] = 0;
                }
                printf("Select your option:\n");
                printf("1.From 1 node to another\n");
                printf("2.Stats from all pairs\n");
                printf("3.Change Mode\n");
                scanf("%d", &option_3);

                switch(option_3) {
                    
                case 1:
                    system("clear");
                    printf("Select your start vertex:");
                    scanf( "%d", &inputStartVertex);
                    printf("Select your destination vertex:");
                    scanf( "%d", &inputDestVertex);
                    bestPath( graph,  inputStartVertex,  inputDestVertex , countLengthBestPath, /*flag1Time = */1);
                    break;
                case 2:
                    totalCount = bestPath( graph, inputStartVertex, inputDestVertex , countLengthBestPath, /*flag1Time = */0);
                    
                    for(int i = 1; i < graph->listSize; i++){
                        if (countLengthBestPath[i] != 0) {
                            int sumBestPath = 0;
                            for(int j = 1; j <= i; j++){
                                sumBestPath += countLengthBestPath[j];
                            }
                            printf("sum %d \n", sumBestPath);
                            printf( " %d: %f ",i, (1-(sumBestPath/totalCount)) );
                            printf("\n");
                        }
                    }
                    printf("\n");
                    break;
                case 3:
                    break;
                }
                free(countLengthBestPath);
                break; 
                   
            case 4:
                break;
           }
    }while(option != 4);
}