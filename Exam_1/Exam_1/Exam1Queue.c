//
//  main.c
//  Exam_1
//
//  Created by Dominique Michael Abejar on 08/08/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

//Test 1
typedef struct studtype{
    char chocoID[16], name[16], desc[30]; //Chocolate id, name, descriptiokn
    float price;
    int quantity;
    int weight;
}chocolate;

typedef struct{
    chocolate chocos[MAX]; //Dynamic array of chocos(wa ra nako gi dynamic kay kapoy na AHAH)
    int front, rear;
    int ctr;  // # of choco in queue
}chocoQueue;

void initQueue(chocoQueue *Q);
void insertSorted(chocoQueue *Q, chocolate chocs);
void display(chocoQueue Q);
int main(){
    chocoQueue Q;
    chocolate chocs;

    initQueue(&Q);
    
    //First choco
    strcpy(chocs.chocoID, "444");
    strcpy(chocs.name, "Ferrero");
    strcpy(chocs.desc, "Okay lang");
    chocs.price = 60.00;
    chocs.quantity = 10;
    chocs.weight = 3;
    insertSorted(&Q, chocs);
    
    //Second choco
    strcpy(chocs.chocoID, "333");
    strcpy(chocs.name, "Toblerone");
    strcpy(chocs.desc, "Okay lang");
    chocs.price = 60.00;
    chocs.quantity = 10;
    chocs.weight = 3;
    insertSorted(&Q, chocs);
    
    //Third choco
    strcpy(chocs.chocoID, "111");
    strcpy(chocs.name, "Snickers");
    strcpy(chocs.desc, "Good");
    chocs.price = 25.00;
    chocs.quantity = 15;
    chocs.weight = 2;
    insertSorted(&Q, chocs);
    
    //Fourth choco
    strcpy(chocs.chocoID, "555");
    strcpy(chocs.name, "Mars");
    strcpy(chocs.desc, "Elon");
    chocs.price = 10.00;
    chocs.quantity = 10;
    chocs.weight = 3;
    insertSorted(&Q, chocs);
    
    //Fifth choco
    strcpy(chocs.chocoID, "222");
    strcpy(chocs.name, "Meiji");
    strcpy(chocs.desc, "Naruto");
    chocs.price = 10.00;
    chocs.quantity = 10;
    chocs.weight = 3;
    insertSorted(&Q, chocs);
    
    //Same choco
    strcpy(chocs.chocoID, "555");
    strcpy(chocs.name, "Mars");
    strcpy(chocs.desc, "Elon");
    chocs.price = 5000.00;
    chocs.quantity = 12310;
    chocs.weight = 3;
    insertSorted(&Q, chocs);
    
    display(Q);
    printf("TOTAL NUMBER OF CHOCOS: %d\n", Q.ctr);
    printf("Queue Front: %d\n", Q.front);
    printf("Queue Rear: %d\n", Q.rear);
    return 0;
}

void initQueue(chocoQueue *Q){
    Q->ctr = 0;
    Q->front = 1;
    Q->rear = 0;
}

void insertSorted(chocoQueue *Q, chocolate chocs){
    int i, trav, trav2;
    chocolate temp;
    
    
    trav = Q->front;
    
    //Loop to last element or if is chocoID is less than or it exists
    for(i = Q->ctr; i != 0 && strcmp(Q->chocos[trav].chocoID, chocs.chocoID) < 0; i--, trav = (trav + 1) % MAX){}
 
    //Queue is not Empty
    if(i != 0){
        //Check if the same ID or not
        if(strcmp(Q->chocos[trav].chocoID, chocs.chocoID) != 0){
            Q->rear = (Q->rear + 1) % MAX;
            Q->chocos[Q->rear] = chocs;
            Q->ctr++;
            
            //BUBBLE SORT
            for(trav = Q->front; trav != Q->rear + 1; trav = (trav + 1) % MAX){
                for(trav2 = (trav + 1) % MAX; trav2 != Q->rear + 1; trav2 = (trav2 + 1) % MAX){
                    if(strcmp(Q->chocos[trav2].chocoID, Q->chocos[trav].chocoID) < 0){
                        temp = Q->chocos[trav];
                        Q->chocos[trav] = Q->chocos[trav2];
                        Q->chocos[trav2] = temp;
                    }
                }
            }
        }else{ //If same ID add quantity and replace price
            Q->chocos[trav].quantity += chocs.quantity;
            Q->chocos[trav].price = chocs.price;
        }
    }else{ //Insert first
        Q->rear = (Q->rear + 1) % MAX;
        Q->chocos[Q->rear] = chocs;
        Q->ctr++;
    }
}

void display(chocoQueue Q){
    int i;
    
    i = Q.front;
    
    while(i != Q.rear + 1){
        printf("Index: %d\n", i);
        printf("ID: %s \nName: %s\n", Q.chocos[i].chocoID, Q.chocos[i].name);
        printf("Price: %f\n", Q.chocos[i].price);
        printf("Quantity: %d\n", Q.chocos[i].quantity);
        printf("\n\n");
        i = (i + 1) % MAX;
    }
}
