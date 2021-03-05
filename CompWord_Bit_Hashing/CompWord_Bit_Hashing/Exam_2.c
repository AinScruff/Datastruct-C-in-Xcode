//
//  Exam_2.c
//  CompWord_Bit_Hashing
//
//  Created by Dominique Michael Abejar on 04/10/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 18
#define HASH_SIZE 7

/* Data structure Definition */
typedef  short  int  compWordSet;      /* Computer Word implementation of set */
typedef int setBitVector[SIZE];        /* Bit-vector implementation of set    */

/*Definition of Set and Dictionary */
typedef struct {
    unsigned int ID;
    char FN[24], LN[16], MI;
}student;

typedef struct node {
    student stud;
    struct node *link;
}ctype, *studSet;

typedef struct openD {
    studSet hashTable[HASH_SIZE];
    int ctr;   /*# of elements in the dictionary */
}*Dictionary;



/* PROBLEMS with function Prototypes */
/*****************************************************************************************
 * Problem 1: a) function displayBitPattern() is a platform independent function that    *
 *               will display the bit pattern of a given number                          *
 *            b) function dislaySetElements() will display the elements of the set in    *
 *               descending order.                                                       *
 ******************************************************************************************/
void displayBitPattern(compWordSet S);
void displaySetElements(compWordSet S, char nameOfSet);

/*******************************************************************************************
 * Problem 2:   Given a set implemented in memory using computer word, function            *
 *     createBitVec() is a the platform-independent function that will create an           *
 *     equivalent set in Bit-Vector implementation.  The function will return the new set  *
 *     to the calling function.                                                            *
 *******************************************************************************************/
setBitVector * createBitVec(compWordSet S);
void displayBitVector(setBitVector V);        /* Function is provided */

/*******************************************************************************************
 * Problem 3:                                                                               *
 *       a) findHashVal().  Given the student record, the hash function returns the hash    *
 *          value which is the sum of all the 1's in the binary representation of the ID    *
 *          number.  If the  sum exceeds the table size, the sum is divided by the table    *
 *          size and the remainder is returned as the hash value.
 *       b) convertToDic(). The function will convert a given SET of student records into  *
 *          a dictionary of student records. Each group is sorted in ascending order        *
 *          according to last name. The newly created dictionary will be returned  to the   *
 *          calling function.                                                               *
 *******************************************************************************************/
int findHashVal(student S);
studSet populateLinkedSet(void);              /* Function is Provided */
void displaySet(studSet L);               /* Function is Provided */
Dictionary convertToDic(studSet *L);
void displayDictionary(Dictionary D);     /* Function is Provided */
int main()
{
    compWordSet  A = -215;      /* A = { 15, 14, 13, 12, 11, 10, 9, 8, 5, 3, 0 }  */
    compWordSet  B =  73;      /*  B = { 6, 3, 0 } */
    
    setBitVector *retval;
    
    studSet L;
    Dictionary D;
    
    printf("\n\nProblem 1: Bit Pattern and Elements of the set");
    /* Call displayBitPattern twice for sets A and B,
     * Call displaySetElements twice for sets A and B */
    displayBitPattern(A);
    displayBitPattern(B);
    
    displaySetElements(A, 'y');
    displaySetElements(B, 'C');
    
    printf("\n\nProblem 2: Bit Vector");
    /* Call createBitVec() passing compWordSet A,then
     * call displayBitVector().
     */
    retval = createBitVec(A);
    displayBitVector(*retval);
    
    printf("\n\nProblem 3: Dictionary");
    /* Call populateLinkedList(),
     call convertToDic(), then displayDictionary().
     */
    L = populateLinkedSet();
    D = convertToDic(&L);

    displayDictionary(D);
    
    return 0;
    
}

/*******************************************************
 * PROBLEM 1 Functions                                  *
 *******************************************************/
void displayBitPattern(compWordSet S){

    unsigned mask, size;
    
    size = sizeof(S) * 8;
    mask = 1 << size;
    
    printf("\nBit Pattern of %d: ", S);
    while(mask != 0){
        if((mask & S) != 0){
            printf(" 1");
        }else{
            printf(" 0");
        }
        
        mask >>= 1;
    }
    
    //printf("\nComputer Word: %d", sum);
}
void displaySetElements(compWordSet S, char nameOfSet){
    
}

/*******************************************************
 * PROBLEM 2 Functions                                  *
 *******************************************************/
void displayBitVector(setBitVector V)
{
    int x;
    
    printf("\n%s:", "Elements");
    for(x = 0; x < SIZE; x++){
        printf(" %d,", V[x]);
    }
}

setBitVector * createBitVec(compWordSet S){

    setBitVector * retval;
    unsigned size, mask, i, sum = 0;
    
    retval = (setBitVector *)calloc(SIZE, sizeof(int));
    
    size = sizeof(S) * 8 - 1;
    mask = 1 << size;
    i = size;
    
    while(mask != 0){
        if((mask & S) != 0){
            sum += pow(2, i);
            (*retval)[i] = 1;
        }
        
        mask >>= 1;
        i--;
    }
    
    printf("\nValue: %d", sum);
    
    return retval;
}
/*******************************************************
 * PROBLEM 3 Functions                                  *
 *******************************************************/
int findHashVal(student S){
    unsigned int size, mask, retval = 0;
    
    size = sizeof(S) * 8 - 1;
    mask = 1 << size;
    
    while(mask != 0){
        if((mask & S.ID) != 0){
            retval += mask;
        }
        mask >>= 1;
    }
    
    if(retval > HASH_SIZE){
        retval %= HASH_SIZE;
    }
    
    return retval;
}

studSet populateLinkedSet()
{
    student S[10] = {     {121010, "Jane", "Jumalon", 'J'}, { 121016 , "Paul", "Perez", 'P'},
        {121005, "Elaine", "Englis", 'E'}, { 121008, "Holly", "Hernandez", 'H'},
        {121001, "Abel", "Ang", 'A'}, {121023, "Fe", "Flores", 'F'},
        {121013, "Manny", "Mendoza", 'M'}, {121007, "Gwen", "Go", 'G'},
        {121019, "Susie", "Suson", 'S'}, {121003, "Carl", "Conan", 'C'}
    };
    
    studSet L, *p;
    int x;
    L = NULL;
    p = &L;
    for(x = 0; x < 10; x++) {
        *p = (studSet)malloc(sizeof(struct node));
        if (*p != NULL){
            (*p)->stud = S[x];
            p = &(*p)->link;
        }
    }
    *p = NULL;
    return L;
}

Dictionary convertToDic(studSet *L){
    Dictionary retval;
    int i, hashval;
    studSet *trav, *trav2, temp;
    
    //Init Dictionary
    retval = (Dictionary)malloc(sizeof(Dictionary));
    
    for(i = 0; i < HASH_SIZE; i++){
        retval->hashTable[i] = NULL;
    }
    
    retval->ctr = 0;
    
    for(trav = L; *trav != NULL; trav = &(*trav)->link){
        hashval = findHashVal((*trav)->stud);
        
        for(trav2 = &retval->hashTable[hashval]; *trav2 != NULL && strcmp((*trav)->stud.LN, (*trav2)->stud.LN) > 0; trav2 = &(*trav2)->link){}
        
        temp = (studSet)malloc(sizeof(struct node));
        
        if(temp != NULL){
            temp->stud = (*trav)->stud;
            temp->link = *trav2;
            *trav2 = temp;
            retval->ctr++;
        }
        
    }
    

    return retval;
}

void displaySet(studSet S)
{
    printf("Elements of the Linked Set");
    for ( ; S != NULL; S = S->link){
        printf("\n%-10d", S->stud.ID);
        printf("%-12s", S->stud.FN);
        printf("%-5c", S->stud.MI);
        printf("%-16s", S->stud.LN);
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
    
    printf("\n");
}
