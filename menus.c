#include "menus.h"

void select_option(Graph* graph){
    //printGraph(graph);  
    printf("Select your option:\n");
    printf("1.Determine if an input is connected \n");
    printf("2.Determine if an input if link-biconnected \n");
    printf("3.Determine if an input is acyclic \n");
    printf("4.Determine if an input is commercially connected \n");
    printf("5.Exit Programm \n");

    int option = 0;
    scanf("%d", &option);
    int Connected_Value = 0;
    int connected = 0;
    //bridges(graph);
    /*connected = graphIsConnected(graph);
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

        printf("Saiu \n");
                //printf("distinct nodes %d \n", nodes);
    }*/
    
    switch(option){
        case 1:
            
            Connected_Value = graphIsConnected(graph);
            printf("valor : %d\n",Connected_Value);

            break;
            
        case 2:
            
            bridges(graph);
            break;
            
        case 3:
            printf("Graph has a commercial cycle %d\n", isCommerciallyCyclic(graph));
            break;
            
        case 4:
            
            
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
                //printf("distinct nodes %d \n", nodes);
            }
            break;
            
        case 5:
            printf("Closing Programm...\n");
            break;

    }
}
