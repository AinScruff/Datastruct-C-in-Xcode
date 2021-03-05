//
//  main.c
//  Graph_Traversal
//
//  Created by Dominique Michael Abejar on 23/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include<stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct cell{
    int elem;
    struct cell *next;
}*List;

typedef struct{
    List front;
    List rear;
}Queue;

int n;

void floyd(int arr[SIZE][SIZE]);
void dfs(int startingVertex, int arr[SIZE][SIZE]);
void bfs(int startingVertex, int arr[SIZE][SIZE]);
void initQueue(Queue *Q);
void enqueue(Queue *Q, int elem);
int front(Queue Q);
void dequeue(Queue *Q);

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
    
    //floyd(adjMatrix);
    
    bfs(0, adjMatrix);
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

void dfs(int startingVertex, int arr[SIZE][SIZE]){
    
}

void bfs(int startingVertex, int arr[SIZE][SIZE]){
    int S[n], retval, y;
    Queue Q;
    
    for(y = 0; y < n; y++){
        S[y] = 0;
    }
    
    S[startingVertex] = 1;
    
    enqueue(&Q, startingVertex);
    
    while (Q.front != NULL) {
        retval = front(Q);
        dequeue(&Q);
        
        for(y = 0; y < n; y++){
            if(arr[n][y] != 1){
                S[y] = 1;
                printf("\n%d", y);
                enqueue(&Q, arr[n][y]);
            }
        }
    }
}


void initQueue(Queue *Q){
    Q->front=NULL;
    Q->rear=NULL;
}

void enqueue(Queue *Q, int elem){
    List temp;
    
    temp=(List)malloc(sizeof(struct cell));
    
    if(temp!=NULL){
        temp->elem=elem;
        temp->next=NULL;
        
        if(Q->rear == NULL){
            Q->front = temp;
        }else{
            Q->rear->next=temp;
        }
        
        Q->rear=temp;
    }
}

int front(Queue Q){
    printf("%d", Q.front->elem);
    return Q.front->elem;
}

void dequeue(Queue *Q){
    List temp;
    
    temp=Q->front;
    Q->front=temp->next;
    free(temp);
}
