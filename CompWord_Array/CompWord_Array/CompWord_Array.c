//
//  CompWord_Array.c
//  CompWord_Array
//
//  Created by Dominique Michael Abejar on 05/10/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 32
#define MAX 50

typedef int setCompWord;

typedef int setBitVector[SIZE];

typedef struct{
    int data[MAX];
    int count;
}setArray;

void initArray(setArray *S);
void displayArray(setArray S);
void displayBitVector(setBitVector B);
setArray convertCW(setCompWord CW);
setBitVector * intersectSet(setCompWord S, setArray Arr);
setCompWord convertInt(int unique);
int main(){
    setArray S;
    setCompWord CW = 255;
    setBitVector * B;
    
    S = convertCW(CW);
    
    displayArray(S);
    B = intersectSet(CW, S);
    displayBitVector(*B);
    
    CW = convertInt(123); //1110 BINARY
    printf("\n\nComputer Word of Unique: %d\n", CW);
    return 0;
}

void initArray(setArray *S){
    S->count = 0;
}

void displayArray(setArray S){
    int i, sum = 0;
    
    printf("Total Number of Elements: %d\n", S.count);
    for(i = 0; i < S.count; i++){
        sum += (int)pow(2, S.data[i]);
        printf("\nS[%d]: %d // %d", i, S.data[i], (int)(pow(2, S.data[i])));
    }
    
    printf("\nCOMPUTER WORD: %d", sum);
}

void displayBitVector(setBitVector B){
    int i = 0, sum = 0;
    
    printf("\n\nINTERSECTION: ");
    while(i != SIZE){
        if(B[i] == 1){
            printf("\nB[%d]: %d // %d", i, B[i], (int)(pow(2, i)));
            sum += (int)(pow(2, i));
        }
        i++;
    }
    printf("\nSUM: %d\n", sum);
}

setArray convertCW(setCompWord CW){
    setArray retval;
    int size, i = 0;
    
    initArray(&retval);
    
    size = sizeof(CW) * 8;
    
    while(CW != 0){
        if(CW&(int)pow(2, size)){
            CW -= pow(2, size);
            retval.data[i] = size;
            retval.count++;
            i++;
        }
        size--;
    }
    return retval;
}

setBitVector * intersectSet(setCompWord S, setArray Arr){
    setBitVector * retval;
    int size, ctr;
    
    retval = (setBitVector *)calloc(SIZE, sizeof(int));
    
    S = 204;
    size = sizeof(S) * 8;

    while(S != 0){
        if(S&(int)(pow(2, size))){
            S -= pow(2, size);
            for(ctr = 0; ctr < Arr.count && pow(2, Arr.data[ctr]) != pow(2, size); ctr++){}
     
            if(ctr < Arr.count){
                (*retval)[size] = 1;
            }
        }
        size--;
    }
    
    return retval;
}

setCompWord convertInt(int unique){
    setCompWord retval = 0;
    
    int temp = unique, factor = 1;
    
    while(temp){
        temp /= 10;
        factor *= 10;
    }
    
    while(factor > 1){
        factor /= 10;
        retval += pow(2, (unique / factor));
        unique %= factor;
    }
    

    return retval;
}
