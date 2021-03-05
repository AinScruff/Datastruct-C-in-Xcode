//
//  main.c
//  List
//
//  Created by Dominique Michael Abejar on 15/06/2019.
//  Copyright © 2019 DataStruct. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define MAX 100

typedef struct{
    int data[MAX];
    int count;
}setArray;

typedef int setBitVector[SIZE];
typedef int setCompWord;

void initArray(setArray * arr);
void displayBit(setCompWord compWord);
void displayArray(setArray arr);
setArray convertToArray(setCompWord compWord);
setCompWord convertToComputerWord(int data);
int * intersection(setCompWord A, setArray B);
int main(){
    int data = 123;
    setCompWord compWord = 43;
    setArray arr;
    setBitVector * bitVect;
    int * i;

    initArray(&arr);

    arr = convertToArray(compWord);

    i = intersection(compWord, arr);
    
 
    return 0;
}

void initArray(setArray * arr){
    arr->count = 0;
}

void displayBit(setCompWord compWord){
    unsigned int size = (sizeof(int)*8) - 1;
    int mask = 1 << (size - 1), i;

    for(i = size - 1; mask != 0; mask >>= 1, i--){
        printf("\n%d: %d\n", i, (compWord & mask) == 0 ? 0:1);
    }
}

void displayArray(setArray arr){
    int i = 0;

    for(i = 0; i < arr.count; i++){
        printf("\nArr[%d]: %d\n", i, arr.data[i]);
    }
}

setArray convertToArray(setCompWord compWord){
    setArray retVal;
    unsigned int count, ndx, mask;

    ndx = 0;
    retVal.count = 0;

    count = (sizeof(setCompWord)*8) - 1;

    for(mask = 1 << count; mask != 0 ; mask >>= 1){
        if((compWord & mask) != 0){
            retVal.data[ndx] = count;
            retVal.count++;
            ndx++;
        }
        count++;
    }

    return retVal;
}

int * intersection(setCompWord A, setArray B){
    int * retval;
    unsigned int count, mask, ndx;

    retval = (int *)malloc(sizeof(int)*SIZE);

    count  = (sizeof(setCompWord)*8)-1;

    for(mask = 1 << count;mask != 0; mask >>= 1){
        if((A & mask) != 0){
            for(ndx = B.count - 1; ndx >= 0 && count != B.data[ndx]; ndx--){}

            if(ndx >=0){
                *(retval+ndx) = 1;
            }
        }

        count--;
    }
    return retval;
}

//setCompWord convertToComputerWord(int data){
//    setCompWord retVal;
//    unsigned int mask, retval, temp;
//
//
//
//
//    return retVal;
//}

