//
//  main.c
//  Tournament_Tree
//
//  Created by Dominique Michael Abejar on 11/19/19.
//  Copyright © 2019 BSIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    char name[16];
    int age;
}PlayerInfo;

typedef struct cell{
    PlayerInfo player_info;
    struct cell * next;
}List;

typedef struct{
    PlayerInfo player_info;
    char rank[10];
}TreeNode;

typedef struct{
    TreeNode node[MAX];
    int last;
}TournaTree;

void initList(List * L);
List populateList(void);
void initTree(TournaTree * T);
int main() {
    List players;
    
    
    initList(&players);
    players = populateList();
    return 0;
}

//List populateLinkedSet(){
//    student S[10] = {     {121010, "Jane", "Jumalon", 'J'}, { 121016 , "Paul", "Perez", 'P'},
//        {121005, "Elaine", "Englis", 'E'}, { 121008, "Holly", "Hernandez", 'H'},
//        {121001, "Abel", "Ang", 'A'}, {121023, "Fe", "Flores", 'F'},
//        {121013, "Manny", "Mendoza", 'M'}, {121007, "Gwen", "Go", 'G'},
//        {121019, "Susie", "Suson", 'S'}, {121003, "Carl", "Conan", 'C'}
//    };
//
//    studSet L, *p;
//    int x;
//    L = NULL;
//    p = &L;
//    for(x = 0; x < 10; x++) {
//        *p = (studSet)malloc(sizeof(struct node));
//        if (*p != NULL){
//            (*p)->stud = S[x];
//            p = &(*p)->link;
//        }
//    }
//    *p = NULL;
//    return L;
//}
