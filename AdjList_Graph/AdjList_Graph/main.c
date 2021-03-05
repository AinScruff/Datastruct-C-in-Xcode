//
//  main.c
//  AdjList_Graph
//
//  Created by Dominique Michael Abejar on 12/7/19.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define VERTEX 5

typedef struct node
{
    int vertex;
    int tail;
    struct node* next;
}*LIST;

typedef struct
{
    LIST *adjLists;
}Graph;

typedef int AdjMatrix[VERTEX][VERTEX];

void initGraph(Graph *G);
void convertADJ(AdjMatrix M, Graph *G);
void display(Graph G);
int main() {
    Graph G;

    AdjMatrix matrix={
        {0, 50, 60, 999, 999},
        {999, 0, 80, 100, 25},
        {999, 999, 0, 999, 999},
        {110, 670, 145, 0, 240},
        {999, 55, 999, 500, 0}
    };

    initGraph(&G);
    convertADJ(matrix, &G);
    display(G);
    return 0;
}

void initGraph(Graph *G){
    int i;
    
    G->adjLists = (LIST *)malloc(sizeof(LIST) * VERTEX);
    
    for(i = 0; i < VERTEX; i++){
        G->adjLists[i] = NULL;
    }
}

void convertADJ(AdjMatrix M, Graph *G){
    int i, j;
    LIST temp, *trav;
    
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            if(M[i][j] != 0 && M[i][j] != 999){
                for(trav = &G->adjLists[i]; *trav != NULL; trav = &(*trav)->next){}
                
                temp = (LIST)malloc(sizeof(struct node));
                if(temp != NULL){
                    temp->tail = j;
                    temp->vertex = M[i][j];
                    temp->next = *trav;
                    *trav = temp;

                }
            }
        }
    }

    
    
}
void display(Graph G){
    LIST trav;
    int i;
    
    
    for(i = 0; i < VERTEX; i++){
        printf("\nINDEX: %d", i);
        for(trav = G.adjLists[i]; trav != NULL; trav = trav->next){
            printf("\nTail: %d, Weight %d", trav->tail, trav->vertex);
        }
    }
}
