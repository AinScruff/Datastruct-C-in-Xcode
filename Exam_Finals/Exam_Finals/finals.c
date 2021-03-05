//
//  main.c
//  Exam_Finals
//
//  Created by Dominique Michael Abejar on 29/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define SENTINEL 999
#define VERTEX 5
#define SIZE 50

typedef int AdjMatrix[VERTEX][VERTEX];
typedef int LabelAdjMat[VERTEX][VERTEX];
typedef unsigned char set;

typedef struct{
    int u, v;
    int weight;
}edgetype;

typedef struct{
    edgetype edges[SIZE];
    int count;
}edgeList;


void populateEdgeList(LabelAdjMat arr);
edgeList createSortedList(LabelAdjMat arr);
int * Dijkstra(AdjMatrix arr);
void displayMatrix(LabelAdjMat mat);
void displayD(int *arr);
void displayEdgeList(edgeList list);
int main(){
    
    LabelAdjMat matrixBeta={
        {0, 50, 60, 999, 999},
        {999, 0, 80, 100, 25},
        {999, 999, 0, 999, 999},
        {110, 670, 145, 0, 240},
        {999, 55, 999, 500, 0}
    };
    
    AdjMatrix matrix={
        {0, 50, 60, 999, 999},
        {999, 0, 80, 100, 25},
        {999, 999, 0, 999, 999},
        {110, 670, 145, 0, 240},
        {999, 55, 999, 500, 0}
    };
    
    edgeList list;
    int *arr;
    
    displayMatrix(matrixBeta);
    printf("\n");
    list = createSortedList(matrixBeta);
    displayEdgeList(list);
    
    arr = Dijkstra(matrix);
    displayD(arr);
}

edgeList createSortedList(LabelAdjMat arr){
    edgeList sortedList;
    int i, j, k;
    
    sortedList.count = 0;
    
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            if(i != j && arr[i][j] != SENTINEL){
                for(k = sortedList.count; k != 0 && arr[i][j] < sortedList.edges[k-1].weight; k--){
                    sortedList.edges[k] = sortedList.edges[k-1];
                }
                sortedList.edges[k].u = i;
                sortedList.edges[k].v = j;
                sortedList.edges[k].weight = arr[i][j];
                sortedList.count++;
            }
        }
    }
    

    //Print
    for(i = 0; i < sortedList.count; i++){
        printf("\nA[%d]: row: %d column: %d weight: %d ", i, sortedList.edges[i].u,sortedList.edges[i].v,  sortedList.edges[i].weight);
    }
    
    return sortedList;
}



int * Dijkstra(AdjMatrix arr){
    unsigned mask;
    int *D, i, min, count, newPath;
    set S;
    
    D = (int *)malloc(sizeof(int)*VERTEX);
    
    printf("\nBefore Dijkstra\n");
    if(D != NULL){
        S = 0;
        S |= 1 << 0;
        
        for(i = 0; i < VERTEX; i++){
            D[i] = arr[0][i];
            printf("%d ", D[i]);
        }
        
        for(count = 1; count < VERTEX; count++){
            min = -1;
            
            for(mask = 1 << (VERTEX - 1), i = VERTEX - 1; mask != 0; mask >>= 1, i--){
                if((S & mask) != 1){
                    if(min != -1){
                        min = (D[i] < D[min]) ? i : min;
                    }else{
                        min = i;
                    }
                }
            }
            S |= 1 << min;
            
            for(mask = 1 << (VERTEX - 1), i = VERTEX - 1; mask != 0; mask >>= 1, i--){
                if((S & mask) != 1){
                    newPath = D[min] + arr[min][i];
                    D[i]=(newPath < D[i]) ? newPath : D[i];
                }
            }
        }
    }
    return D;
}

void displayMatrix(LabelAdjMat mat){
    int i, j;
    
    printf("Adjecency Matrix\n");
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void displayD(int *arr){
    int i;
    
    printf("\n\nAfter Dijkstra\n");
    for(i = 0; i < VERTEX; i++){
        printf("%d ", arr[i]);
    }
}

void displayEdgeList(edgeList list){
    int i;
    
    printf("Sorted Edge List\n");
    for(i = 0; i < list.count; i++){
        printf("%d -> %d: %d\n", list.edges[i].u, list.edges[i].v, list.edges[i].weight);
    }
}

