#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct node{
    char elem;
    struct node *link;
}*LIST;

typedef struct{
    LIST front;
    LIST rear;
    int count;
}Queue;

void initQueue(Queue *Q);
void enqueue(Queue *Q, char data);
void dequeue(Queue *Q);
void display(Queue Q);
int main() {
    Queue Q;
    
    initQueue(&Q);
    printf("---Enqueue---\n");
    enqueue(&Q, 'a');
    enqueue(&Q, 'b');
    enqueue(&Q, 'c');
    display(Q);
    
    //First In First Out so goodbye a
    printf("\n---Dequeue First Letter---\n");
    dequeue(&Q);
    display(Q);
    
    return 0;
}

void initQueue(Queue *Q){
    Q->front = NULL;
    Q->rear = NULL;
    Q->count = 0;
}

void enqueue(Queue *Q, char data){
    LIST temp;
    
    temp = (LIST)malloc(sizeof(struct node));
    
    if(temp != NULL){
        temp->elem = data;
        temp->link = NULL;
        
        if(Q->count == 0){ //Or if no count Q->front == NULL
            Q->front = temp;
            Q->rear = temp;
        }else{
            Q->rear->link = temp;
        }
        
        Q->rear = temp;
        Q->count++;
    }
    
}

void dequeue(Queue *Q){
    LIST temp;
    
    if(Q->front != NULL){
        temp = Q->front;
        Q->front = temp->link;
        free(temp);
        Q->count--;
        
        if(Q->count == 0){
            Q->rear = NULL;
        }
    }
}

void display(Queue Q){
    LIST temp;
    
    if(Q.front != NULL){
        for(temp = Q.front; temp->link != NULL; temp = temp->link){
            printf("%c\n", temp->elem);
        }
        
        printf("%c\n", temp->elem);
    }else{
        printf("Queue is Empty");
    }
    
}

