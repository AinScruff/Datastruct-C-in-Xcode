//
//  Files.c
//  Files
//
//  Created by Dominique Michael Abejar on 04/10/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define HASH_SIZE 10
#define SIZE 10

typedef struct {
    unsigned int ID;
    char FN[24], LN[16], MI, course[24];
}student;

typedef struct node {
    student stud;
    struct node *link;
}ctype, *studRec;

typedef struct openD {
    studRec hashTable[HASH_SIZE];
    int ctr;
}*Dictionary;

void initList(studRec * S);
int findhashval(int ID);
studRec populateLinkedSet();
void insertDict(Dictionary D, studRec S, int hashval);
void displayDictionary(Dictionary D);
void displaySet(studRec S);
int main(){
    studRec S, *trav, temp;
    FILE *fptr;
    int i, hashval;
    Dictionary D;
    
    
    //Initialize
    initList(&S);
    S = populateLinkedSet();
    
    D = (Dictionary)malloc(sizeof(struct openD));
    D->ctr = 0;
    
    for(i = 0; i < HASH_SIZE; i++){
        D->hashTable[i] = NULL;
    }
    
    //FILE WRITE
    fptr = fopen("/Users/dominiquemichaelabejar/Desktop/DataStruct/Files/dcis.dat", "wb");
    
    if(fptr != NULL){
        for(trav = &S; *trav != NULL; trav = &(*trav)->link){
            fwrite(&(*trav), sizeof((*trav)), 1, fptr);
        }
    }
    
    fclose(fptr);
    
    
    //FILE READ
    fptr = fopen("/Users/dominiquemichaelabejar/Desktop/DataStruct/Files/dcis.dat", "rb");
    
    if(fptr != NULL){
        while(fread(&temp, sizeof(temp), 1, fptr)){
            if(strcmp(temp->stud.course, "IT") == 0 || strcmp(temp->stud.course, "CS") == 0){
                hashval = findhashval(temp->stud.ID);
                insertDict(D, temp, hashval);
            }
        }
    }
    
    displayDictionary(D);
    
    fclose(fptr);
    
 
    return 0;
}

void initList(studRec * S){
    *S = NULL;
}

int findhashval(int ID){
    unsigned int retval = 0, size;
    
    size = (ID) * 8 - 1;
    
    while(ID != 0){
        if(ID&(int)pow(2, size)){
            retval += size;
            ID -= pow(2, size);
        }
        size--;
    }
    
    if(retval >= 10){
        retval %= 10;
    }
    
    return retval;
}

studRec populateLinkedSet()
{
    student S[10] = {     {121010, "Jane", "Jumalon", 'J', "CS"}, { 121016 , "Paul", "Perez", 'P', "IS"},
        {121005, "Elaine", "Englis", 'E', "IT"}, { 121008, "Holly", "Hernandez", 'H', "IT"},
        {121001, "Abel", "Ang", 'A', "CS"}, {121023, "Fe", "Flores", 'F', "IS"},
        {121013, "Manny", "Mendoza", 'M', "IS"}, {121007, "Gwen", "Go", 'G', "IT"},
        {121019, "Susie", "Suson", 'S', "IS"}, {121003, "Carl", "Conan", 'C', "CS"}
    };
    
    studRec L, *p;
    int x;
    L = NULL;
    p = &L;
    for(x = 0; x < 10; x++) {
        *p = (studRec)malloc(sizeof(ctype));
        if (*p != NULL){
            (*p)->stud = S[x];
            p = &(*p)->link;
        }
    }
    *p = NULL;
    return L;
}

void insertDict(Dictionary D, studRec S, int hashval){
    studRec temp, *trav;

    for(trav = &D->hashTable[hashval]; *trav != NULL; trav = &(*trav)->link){}
    
    temp = (studRec)malloc(sizeof(ctype));
    
    if(temp != NULL){
        temp = S;
        temp->link = *trav;
        *trav = temp;
        D->ctr++;
    }
}

void displayDictionary(Dictionary D)
{
    int x;
    
    printf("\n\nElements of the Dictionary: %d", D->ctr);
    for(x = 0 ; x < HASH_SIZE; x++){
        printf("\n\n%d ::  ", x);
        displaySet(D->hashTable[x]);
    }
}

void displaySet(studRec S)
{
    printf("Elements of the Linked Set");
    for ( ; S != NULL; S = S->link){
        printf("\n%-10d", S->stud.ID);
        printf("%-12s", S->stud.FN);
        printf("%-5c", S->stud.MI);
        printf("%-5s", S->stud.course);
        printf("%-16s", S->stud.LN);
    }
}
