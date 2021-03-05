//
//  main.c
//  closedHashing
//
//  Created by Dominique Michael Abejar on 07/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define EMPTY '/'
#define DELETED '$'

typedef struct{
    int elem;
    int link;
}LIST;

typedef struct{
    LIST L[MAX];
    int avail;
}Dictionary;

void initDict(Dictionary *D);
void displayDict(Dictionary D);
int hash(int x);
void insertDict(Dictionary *D, int elem);
int main(){
    Dictionary D;
    
    initDict(&D);
    
    insertDict(&D, 10);
    insertDict(&D, 50);
//    insertDict(&D, 11);
//
     displayDict(D);
    return 0;
}

void initDict(Dictionary *D){
    int trav;
    
    D->avail = (MAX / 2) - 1;
    
    for(trav = 0; trav < D->avail; trav++){
        D->L[trav].elem = EMPTY;
    }
    
    for(trav = 0; trav < MAX; trav++){
        D->L[trav].link = -1;
    }
    
    D->L[MAX-1].link = -1;
}

void displayDict(Dictionary D){
    
    int i, temp;
    for(i = 0; i < (MAX / 2) - 1; i++){
        for(temp = D.L[i].link; temp != -1; temp = D.L[temp].link){
            printf("%d", D.L[temp].elem);
        }
        
    }
}

int hash(int x){
    return x % 10;
}

void insertDict(Dictionary *D, int elem){
    int hashVal, temp;
    
    hashVal = hash(elem);
    

    
    if(D->L[hashVal].elem == EMPTY || D->L[hashVal].elem == DELETED){

        for(temp = D->L[hashVal].link; temp != -1 && D->L[temp].elem != elem; temp = D->L[temp].link){}
        
        if(temp != -1){
            temp = D->avail;
            D->avail = D->L[temp].link;
            D->L[temp].elem = elem;
            D->L[temp].link = D->L[hashVal].link;
            D->L[hashVal].link = temp;
        }
        
        
    }else{
        D->L[hashVal].elem = elem;
    }
}
