//
//  main.c
//  StackCursorBased
//
//  Created by Dominique Michael Abejar on 13/09/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef int List;

typedef struct{
    char data;
    int link;
}Stack;

typedef struct{
    int availList;
    Stack stackArray[SIZE];
}VirtualHeap;

void StackInit(VirtualHeap *VH, List *L);
void StackPush(VirtualHeap *VH, char elem, List *L);
void StackPop(VirtualHeap *VH, List *L);
char StackTop(VirtualHeap *VH, List *L);
void display(VirtualHeap *VH, List L);
int main() {
    
    VirtualHeap VH;
    List L;

    StackInit(&VH, &L);
    StackPush(&VH, 'a', &L);
    StackPush(&VH, 'b', &L);
    StackPush(&VH, 'c', &L);
    StackPop(&VH, &L);
    
    display(&VH, L);
    return 0;
}

void StackInit(VirtualHeap *VH, List *L){
    List i;
    
    VH->availList = 0;
    *L = -1;
    
    for(i = 0; i < (SIZE-1); i++){
        
        VH->stackArray[i].link = i + 1;
        
    }
    
    VH->stackArray[i].link = -1;
}

void StackPush(VirtualHeap *VH, char elem, List *L){
    List temp;
    
    if(VH->availList != -1){
        temp = VH->availList;
        
        VH->availList = VH->stackArray[temp].link;
        VH->stackArray[temp].data = elem;
        VH->stackArray[temp].link = *L;
        *L = temp;
        
        printf("%d\n", *L);
    }
}

void StackPop(VirtualHeap *VH, List *L){
    List temp;
    
    if(*L > -1 && *L < SIZE){
        temp = *L;
        *L = VH->stackArray[temp].link;
        VH->stackArray[temp].link = VH->availList;
        VH->availList = temp;
    }
    
}

char StackTop(VirtualHeap *VH, List *L){
    char retval;
   
    retval = VH->stackArray[*L].data;
    
    return retval;
}

void display(VirtualHeap *VH, List L){
    List trav;
    
    for(trav = L; trav != -1;trav = VH->stackArray[trav].link)
    {
        printf("Elements: %c\n", VH->stackArray[trav].data);
    }
}
