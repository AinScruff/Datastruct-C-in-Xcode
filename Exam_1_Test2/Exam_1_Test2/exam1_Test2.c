//
//  main.c
//  Exam_1_Test2
//
//  Created by Dominique Michael Abejar on 11/09/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 10

typedef struct{
    char data;
    int link;
}ctype;

typedef struct node{
    ctype cTable[SIZE];
    int avail;
}*Vheap;

typedef struct{
    int top;
    Vheap VH;
}Stack;


void initStack(Stack *S);
int VMalloc(Stack *S);
void push(Stack *S);
void pop(Stack *S);
bool checkIfExist(Stack S, char data);
void insertBottom(Stack *S, char data);

int main(){
    Stack S;
    int i;
    initStack(&S);
    
    for(i = 0; i < SIZE; i++){
        printf("%d\n", S.VH->cTable[i].link);
    }
    return 0;
    
}

void initStack(Stack *S){
    int i;
    
    S->VH->avail = 0;
    S->top = -1;
    
    for(i = 0; i < (SIZE - 1); i++){
        S->VH->cTable[i].link = i + 1;
    }
    
    S->VH->cTable[i].link = -1;
}

void pop(Stack *S){
    int temp;
    
    temp = S->top;
    
    if(temp != -1){
        S->top = S->VH->cTable[temp].link;
        S->VH->cTable[temp].link = S->VH->avail;
        S->VH->avail = temp;
    }
}

int VMalloc(Stack *S){
    int retval;
    
    retval = S->VH->avail;
    
    if(retval != -1){
        S->VH->avail = S->VH->cTable[retval].link;
    }
  
    return retval;
}

bool checkIfExist(Stack S, char data){
    bool retval;
    Stack temp;
    int i;
    
    temp = S;
    retval = true;
    
    for(i = temp.top; i != -1 && temp.VH->cTable[i].data != data; i = temp.VH->cTable[i].link){}//Check if exist or not
    
    return retval;
}

void insertBottom(Stack *S, char data){
    bool check;
    int temp, retval;
    Stack *tempStack;
    
    check = checkIfExist(*S, data);
 
    if(check != false){ //Check if exist or not
        
       
        retval = VMalloc(S); //Ask for available space
        
        temp = S->top;
        S->VH->cTable[retval].link = temp;
        
        S->top = retval;

        
        
        tempStack = S;
        
        if(S->top != -1){
            
            while(tempStack->VH->cTable[tempStack->top].link != -1){ //Pop temporary stack until last element
                
                if(temp != -1){
                    tempStack->top = tempStack->VH->cTable[temp].link;
                    tempStack->VH->cTable[temp].link = tempStack->VH->avail;
                    tempStack->VH->avail = temp;
                }
            }
            
            //Assign data to vmallocated space
            S->VH->cTable[temp].data = data;
            
            
        }
    }
}
