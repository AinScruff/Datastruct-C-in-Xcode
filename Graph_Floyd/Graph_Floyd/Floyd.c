//
//  main.c
//  Graph_Floyd
//
//  Created by Dominique Michael Abejar on 23/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include<stdio.h>
#define SIZE 10

int n;

void floyd(int arr[SIZE][SIZE]);
int main(){
    int i, j, adjMatrix[SIZE][SIZE];
    
    printf("Input the number of vertices: ");
    scanf("%d", &n);
    printf("\n\nInput the adjecency matrix of the graph--\n");
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("\nA[%d][%d]: ", i ,j);
            scanf("%d", &adjMatrix[i][j]);
        }
    }
    floyd(adjMatrix);
}

void floyd(int arr[SIZE][SIZE]){
    int A[n][n], i, j, k;
    
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            A[i][j] = arr[i][j];
        }
    }
    
    for(i = 0; i < n; i++){
        A[i][i] = 0;
    }
    
    for(k = 0; k < n; k++){
        for(i = 0;i < n; i++){
            for(j = 0; j < n; j++){
                if(A[i][k] + A[k][j] < A[i][j]){
                    A[i][j] = A[i][k] + A[k][j];
                    printf("\nNew Value of A[%d][%d]: from %d to %d\n", i, j, arr[i][j], A[i][j]);
                }
            }
        }
    }
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf ("%7d", A[i][j]);
        }
        printf("\n");
    }
    
}
