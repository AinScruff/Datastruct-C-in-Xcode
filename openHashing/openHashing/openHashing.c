//
//  main.c
//  openHashing
//
//  Created by Dominique Michael Abejar on 07/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct cell{
    int elem;
    struct cell *link;
}*LIST;

typedef LIST Dictionary[SIZE];

void initDict(Dictionary *dict);
void insert(Dictionary *dict, int x);
int hash(int x);

int main(){
    Dictionary dict;
    
    initDict(&dict);
    insert(&dict, 11);
    printf("%d", dict[1]->elem);
    return 0;
}

void initDict(Dictionary *dict){
    dict = NULL;
}

int hash(int x){
    return x % 10;
}

void insert(Dictionary *dict, int x){
    LIST *trav, temp;
    int hashValue;
    
    hashValue = hash(x);
    
    for(trav = &(*dict[hashValue]); (*trav) != NULL && (*trav)->elem < x; trav = &(*trav)->link){
        printf("%d", (*trav)->elem);
    }
    
    if(*trav != NULL && (*trav)->elem != x){
        temp = (LIST)malloc(sizeof(struct cell));
        temp->elem = x;
        temp->link = *trav;
        *trav = temp;
    }
}
