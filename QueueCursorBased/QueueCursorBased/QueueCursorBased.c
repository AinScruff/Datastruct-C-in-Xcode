//
//  main.c
//  QueueCursorBased
//
//  Created by Dominique Michael Abejar on 13/09/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct{
    char data;
    int link;
}Node;

typedef int List;

typedef struct{
    Node nodeArray[SIZE];
    int availList;
}VirtualHeap;

typedef struct{
    List front;
    List rear;
}Queue;


void initVHeap(VirtualHeap *VH);
void initQueue(Queue *Q);
void enqueue(VirtualHeap *VH, Queue *Q, char elem);
void dequeue(VirtualHeap *VH, Queue *Q);
void display(VirtualHeap VH, Queue Q);
int main() {
    VirtualHeap VH;
    Queue Q;
    
    
    initVHeap(&VH);
    initQueue(&Q);
    enqueue(&VH, &Q, 'a');
    enqueue(&VH, &Q, 'b');
    enqueue(&VH, &Q, 'c');
    enqueue(&VH, &Q, 'd');
    
    display(VH, Q);
    return 0;
    
    return 0;
}

void initVHeap(VirtualHeap *VH){
    List i;
    
    VH->availList = 0;
    
    for(i = 0; i < (SIZE - 1); i++){
        VH->nodeArray[i].link = i + 1;
    }
   
    VH->nodeArray[i].link = -1;
}

void initQueue(Queue *Q){
    Q->front = -1;
    Q->rear = -1;
}

void enqueue(VirtualHeap *VH, Queue *Q, char elem){
    List temp;
    
    if(VH->availList != -1){
        temp = VH->availList;
        VH->availList = VH->nodeArray[temp].link;
        VH->nodeArray[temp].data = elem;
        VH->nodeArray[temp].link = -1;
        
        if(Q->front == -1){
            Q->front = temp;
        }else{
            VH->nodeArray[Q->rear].link = temp;
        }
         Q->rear = temp;
    }
}

void dequeue(VirtualHeap *VH, Queue *Q){
    List temp;
    
    if(Q->front != -1 && Q->rear != -1){
        temp = Q->front;
        Q->front = VH->nodeArray[temp].link;
        VH->nodeArray[temp].link = VH->availList;
        VH->availList = temp;
        if(Q->front == -1){
            Q->rear = -1;
        }
    }
}

void display(VirtualHeap VH, Queue Q){
    List i;
    
    for(i = Q.front; i != -1; i = VH.nodeArray[i].link){
        printf("%c\n", VH.nodeArray[i].data);
    }
}


