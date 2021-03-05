//
//  main.c
//  CircularArray
//
//  Created by Dominique Michael Abejar on 13/09/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#define MAX 10
typedef struct{
    char elem[MAX];
    int front;
    int rear;
}Queue;

void initQueue(Queue *Q);
void enqueue(Queue *Q, char data);
void dequeue(Queue *Q);
void display(Queue Q);

int main(){
    Queue Q;
    
    initQueue(&Q);
    
    enqueue(&Q, 'a');
    enqueue(&Q, 'b');
    enqueue(&Q, 'c');
    enqueue(&Q, 'd');
    
    printf("---Display Queue---\n");
    display(Q);
    
    printf("\n---After Dequeue---\n");
    dequeue(&Q);
    display(Q);
    return 0;
}

void initQueue(Queue *Q){
    Q->front = 1;
    Q->rear = 0;
}

void enqueue(Queue *Q, char data){
    if((Q->rear + 2) % MAX != Q->front){ //Check if not full
        Q->rear = (Q->rear + 1) % MAX;
        Q->elem[Q->rear] = data;
    }
}

void dequeue(Queue *Q){
    if((Q->rear + 1) % MAX != Q->front){ //Check if not empty
        Q->front = (Q->front + 1) % MAX;
    }
}

void display(Queue Q){
    int i;
    
    i = Q.front;
    
    while(i != Q.rear + 1){ // Loop to Rear
        printf("%c\n", Q.elem[i]);
        i = (i + 1) % MAX;
    }
    
}
