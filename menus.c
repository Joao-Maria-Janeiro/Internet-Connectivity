#include "menus.h"


void select_option(Graph* graph){
    //printGraph(graph); 
    int option = 0;
    
    
    do{
        printf("Select your option:\n");
        printf("1.Determine if an input is connected \n");
        printf("2.Determine if an input if link-biconnected \n");
        printf("3.Determine if an input is acyclic \n");
        printf("4.Determine if an input is commercially connected \n");
        printf("5.Exit Programm \n\n");

       
        scanf("%d", &option);
        int Connected_Value = 0;
        int connected = 0;
        
        switch(option) {

            case 1:
                system("clear");
                graphIsConnected(graph);
                break;
                
            case 2:
                system("clear");
                bridges(graph);
                break;

            case 3:
                system("clear");
                isCommerciallyCyclic(graph);
                break; 

            case 4: {
                system("clear");
                connected = graphIsConnected(graph);

                int * tier1Nodes = (int*)malloc(graph->listSize * sizeof(int));
                int tier1Count = 0;
                int commercially_connected = 0;

                if(connected == 1) {
                    tier1Count = findTier1(graph, tier1Nodes);
                    commerciallyConnected(graph, tier1Nodes, tier1Count);   
                }
                else{
                    printf("The Network must be Connected\n");
                }
                free(tier1Nodes);
                
                
                }
                break;    
            case 5:
                break;
            
        }
    }while(option != 5);
}
