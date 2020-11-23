
#include "menus.h"


void select_option(Graph* graph){
    //printGraph(graph); 
    int option = 0;
    
    
    do{
        printf("Select your option:\n");
        printf("1.Determine path type \n");
        printf("2.Determine path length \n");
        printf("3.Determine the fastest path \n");
        printf("5.Exit Programm \n\n");

       
        scanf("%d", &option);
        int Connected_Value = 0;
        int connected = 0;
        int inputStartVertex = 0;
        int inputDestVertex = 0;
        switch(option) {

            case 1:
                system("clear");
                
                int validVertex = 0;
                
                printf("Select your start vertex:");
                scanf( "%d", &inputStartVertex);
                printf("Select your destination vertex:");
                scanf( "%d", &inputDestVertex);

                int count[5];
                float totalCount = 0;
                for(int i = 0; i < 5; i++){
                    count[i] = 0;
                }
                // do{
                //     for(int i = 0; i<graph->listSize; i++) {
                        
                //         if(inputStartVertex == graph->array[i].head) {
                //             validVertex = 1;
                //             if(inputDestVertex == graph->array[i].head && inputDestVertex != inputStartVertex) {
                //                 validVertex = 2;
                //                 continue; 
                //             }
                            
                                   
                //         }
                //     }
                    
                //     if(validVertex == 0 ){
                //         printf("The selected starting vertex is not valid, select another vertex:");
                //         scanf(&d, inputStartVertex);
                //     }
                //     else if(validVertex == 1 ){
                //         printf("The selected ending vertex is not valid, select another vertex:");
                //         scanf(&d, inputDestVertex);
                //     }

                // }while(validVertex != 2);
                
                for(int i = 0; i< graph->listSize; i++){
                    if ( graph->array[i].head != NULL){
                        pathType(graph,  i, inputStartVertex , inputDestVertex,  count);
                    }
                }
                
                printf("The Path Statistics for this Graph is:\n");

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
                
                
                break;
                
            case 2:
                system("clear");

                printf("Select your start vertex:");
                scanf( "%d", &inputStartVertex);
                printf("Select your destination vertex:");
                scanf( "%d", &inputDestVertex);

                int *countLength = (int*)malloc(sizeof(int) * (graph->E));
                for(int i = 0; i < graph->E; i++){
                    countLength[i] = 0;
                }

            
                for(int i = 0; i< graph->listSize; i++){
                    if ( graph->array[i].head != NULL){
                        
                        pathLength(graph, i, inputStartVertex,inputDestVertex,countLength);
                    }
                }
                printf("\n");
                for(int i = 0; i < graph->E; i++){
                    totalCount += countLength[i];
                }

                for(int i = 1; i < graph->E; i++){
                    if (countLength[i] != 0) {
                        printf( " %d: %f ",i, countLength[i]/totalCount );
                        for(int j = 0; j < countLength[i]; j++){
                            printf( "| ");
                            
                        }
                        printf("\n");
                    }
                }
                printf("\n");
                break;

            case 3:
                system("clear");
                //isCommerciallyCyclic(graph);
                break;    
            case 4:
                break;
           }
    }while(option != 4);
}