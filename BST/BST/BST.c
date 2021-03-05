#include<stdio.h>
#include<stdlib.h>
typedef struct cell{
    int data;
    struct cell *right;
    struct cell *left;
}*BST;

void initBST(BST *S);
void insertBST(BST *S, int x);
int deleteMin(BST *S);
int isMember(BST S, int x);
int searchBST(BST S, int x);
int deleteBST(BST *S, int x);
int deleteMax(BST *S);
int deleteMin(BST *S);
int heightTree(BST S);
void printPostorder(BST * S);
void printPreorder(BST * S);
void printInorder(BST* S);
int main(){
    BST S;
    int x;
    
    
    //INIT
    initBST(&S);
    
    //INSERT
    insertBST(&S, 10);
    insertBST(&S, 4);
    insertBST(&S, 5);
    insertBST(&S, 14);
    insertBST(&S, 7);
    insertBST(&S, 3);
    insertBST(&S, 12);
    insertBST(&S, 11);
    insertBST(&S, 20);
    insertBST(&S, 18);
    insertBST(&S, 15);
    
    x = isMember(S, 10);
    
    (x == 1)? printf("\n%d is a member\n", x) : printf("\n%d is not a member\n", x);
    
    
    printf("\n---BEFORE DELETE---");
    printPreorder(&S);
    
    x = heightTree(S);
    printf("\nHeight of Tree: %d\n", x);
    
    //DELETE
    x = deleteBST(&S, 10);
    
    if(x == -1){
        printf("\nNumber not found");
    }else{
        printf("\n---AFTER DELETE---");
        printPreorder(&S);
        
    }
    
    
    return 0;
}

void initBST(BST *S){
    *S = NULL;
}

void insertBST(BST *S, int x){ //INSERT IF NOT YET EXIST
    BST *trav, temp;
    
    for(trav = S; *trav != NULL && (*trav)->data != x;){
        trav = ((*trav)->data < x) ? &(*trav)->right : &(*trav)->left;
    }
    
    if((*trav) == NULL){
        
        temp = (BST)malloc(sizeof(struct cell));
        
        if(temp != NULL){
            temp->data = x;
            temp->left = NULL;
            temp->right = NULL;
            *trav = temp;
        }
    }
}

int isMember(BST S, int x){ //Check if given number exists
    BST trav;
    int retval = 0;
    
    
    for(trav = S; trav != NULL && trav->data != x; ){
        trav = (x > trav->data)? trav->right : trav->left;
    }
    
    if(trav != NULL){
        retval = 1;
    }
    
    return retval;
}

int searchBST(BST S, int x){
    BST trav;
    int retval = -1;
    
    for(trav = S; trav != NULL && trav->data != x;){
        trav = (trav->data < x) ? trav->left : trav->right;
    }
    
    if(trav != NULL){
        retval = trav->data;
    }
    
    return retval;
}

int deleteMin(BST *S){
    int retval;
    BST *trav, temp;
    
    for(trav = S; (*trav)->left != NULL; trav = &(*trav)->left){}
    
    temp = *trav;
    retval = temp->data;
    *trav = temp->right;
    free(temp);
    
    return retval;
}

int deleteMax(BST *S){
    int retval;
    BST *trav, temp;
    
    for(trav = S; (*trav)->right != NULL; trav = &(*trav)->right){}
    
    temp = *trav;
    retval = temp->data;
    *trav = temp->left;
    free(temp);
    
    return retval;
}



int deleteBST(BST *S, int x){
    BST *trav, temp;
    
    int retval = -1;
    
    
    if((*S)->data == x){
        retval = deleteMin(&(*S)->right);
        (*S)->data = retval;
    }else{
            
        for(trav = S; *trav != NULL && (*trav)->data != x;){
            trav = (x > (*trav)->data) ? &(*trav)->right : &(*trav)->left;
        }
        
        printf("\n\n\n");

        if((*trav)->data == x){
            
            retval = (*trav)->data;
            
            temp = *trav;
        
            if((*trav)->right != NULL){
                *trav = temp->right;
                (*trav)->left = temp->left;
            }else{
                *trav = temp->left;
            }
            
            free(temp);
        }else{
            printf("NUMBER DOES NOT EXIST!");
        }
    }
    
    return retval;
    
}

int heightTree(BST S){
    int left, right, max;
    
    if(S == NULL){
        return 0;
    }
    
    left = heightTree(S->left);
    right = heightTree(S->right);
    
    max = (left > right)? left : right;
    
    return 1 + max;
}

void printPostorder(BST *S)
{
     if (*S == NULL)
        return;
  
     // first recur on left subtree
     printPostorder(&(*S)->left);
  
     // then recur on right subtree
     printPostorder(&(*S)->right);
  
     // now deal with the node
     printf("\n%d\n", (*S)->data);
}
  
/* Given a binary tree, print its nodes in inorder*/
void printInorder(BST *S)
{
      if (*S == NULL)
          return;
  
     /* first recur on left child */
     printInorder(&(*S)->left);
  
     /* then print the data of node */
     printf("\n%d ", (*S)->data);
  
     /* now recur on right child */
     printInorder(&(*S)->right);
}
  
void printPreorder(BST *S)
{
     if (*S == NULL)
          return;
  
     /* first print data of node */
     printf("\n%d", (*S)->data);
  
     /* then recur on left sutree */
     printPreorder(&(*S)->left);
  
     /* now recur on right subtree */
     printPreorder(&(*S)->right);
}

