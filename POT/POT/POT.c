//
//  main.c
//  POT
//
//  Created by Dominique Michael Abejar on 14/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef struct{
    int elem[MAX];
    int last;
}Heap;

void initHeap(Heap *H);
void insertMinHeap(Heap *H, int x);
void insertMaxHeap(Heap *H, int x);
void display(Heap H);
int deleteMin(Heap *H);
int deleteMax(Heap *H);
void heapSort(Heap *H);

int main(){
    Heap H;

    initHeap(&H);
    
    // MARK: - Min
//    insertMinHeap(&H, 2);
//    insertMinHeap(&H, 5);
//    insertMinHeap(&H, 7);
//    insertMinHeap(&H, 20);
//    insertMinHeap(&H, 10);
//    insertMinHeap(&H, 9);
//    insertMinHeap(&H, 16);
//    insertMinHeap(&H, 19);
//    insertMinHeap(&H, 15);
//    insertMinHeap(&H, 17);
    
    // MARK: - Max
    insertMaxHeap(&H, 2);
    insertMaxHeap(&H, 5);
    insertMaxHeap(&H, 7);
    insertMaxHeap(&H, 20);
    insertMaxHeap(&H, 10);
    insertMaxHeap(&H, 9);
    insertMaxHeap(&H, 16);
    insertMaxHeap(&H, 19);
    insertMaxHeap(&H, 15);
    insertMaxHeap(&H, 17);
    printf("---OLD TREE---");
    display(H);
    
    printf("\n\n---SORTED---");
    heapSort(&H);
    //display(H);
    return 0;
}

void initHeap(Heap *H){
    H->last = -1;
}

void insertMinHeap(Heap *H, int x){
    int trav;
    
    for(trav = H->last + 1; trav != 0 && H->elem[(trav - 1) / 2] > x; trav = (trav - 1) / 2){
        H->elem[trav] = H->elem[(trav - 1) / 2];
    }
    H->elem[trav] = x;
    H->last++;
}

void insertMaxHeap(Heap *H, int x){
    int trav;
    
    for(trav = H->last + 1; trav != 0 && H->elem[(trav - 1) / 2] < x; trav = (trav - 1) / 2){
        H->elem[trav] = H->elem[(trav - 1) / 2];
    }
    
    H->elem[trav] = x;
    H->last++;
}

void display(Heap H){
    int i;
    
    for(i = 0; i < H.last + 1; i++){
        printf("\nA[%d]: %d ", i, H.elem[i]);
    }
}

int deleteMin(Heap *H){
    int temp, trav, retval, left, right;
    
    //check the partially ordered tree if empty
    if(H->last != -1){
        //swap first element and last element and minus the last
        retval = H->elem[0];
        H->elem[0] = H->elem[H->last];
        H->elem[H->last--] = retval;
       
        //sort to satisfy partially ordered tree (parent must be smaller than the child)
        //stop if the index of child is above the specified last index
        
        trav = 0; //Initialize traversal to root
        
        while((trav * 2) + 1 < H->last){ //Check if last element or not by checking it has a left child
            
            //Formula for left and right child
            left = (trav * 2) + 1;
            right = (trav * 2) + 2;
            
            temp = H->elem[trav]; //SWAP
            
            if(H->elem[left] < H->elem[right]){
                H->elem[trav] = H->elem[left];
                H->elem[left] = temp;
                trav = left; //Go to left child
            }else{
                H->elem[trav] = H->elem[right];
                H->elem[right] = temp;
                trav = right; //Go to right child
            }
        }
        
    }else{
        retval = -1;
    }
    
    return retval;
}


int deleteMax(Heap *H){
    int temp, trav, retval, left, right;
    
    //check the partially ordered tree if empty
    if(H->last != -1){
        //Swap first element and last element and minus the last
        retval = H->elem[0];
        H->elem[0] = H->elem[H->last];
        H->elem[H->last--] = retval;
       
        //sort to satisfy partially ordered tree (parent must be smaller than the child)
        //stop if the index of child is above the specified last index
        
        trav = 0; //Traverse initialize to root
        
        while((trav * 2) + 1 < H->last){ //Check if last element or not by checking it has a left child
            
            //Formula for left and right child
            left = (trav * 2) + 1;
            right = (trav * 2) + 2;
            
            temp = H->elem[trav]; //SWAP
            
            if(H->elem[left] > H->elem[right]){
                H->elem[trav] = H->elem[left];
                H->elem[left] = temp;
                trav = left; //Go to left child
            }else{
                H->elem[trav] = H->elem[right];
                H->elem[right] = temp;
                trav = right; //Go to right child
            }
        }
        
    }else{
        retval = -1;
    }
    
    return retval;
}

void heapSort(Heap *H){
    int i = 0, retval, ctr;
    
    ctr = H->last;
    
    while(i < ctr){
        retval = deleteMax(H); //Or deleteMin if insertMin
        printf("\nDeleted: %d ", retval);
        i++;
    }
    H->last = ctr;
}
