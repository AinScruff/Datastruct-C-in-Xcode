//
//  main.c
//  Graph_Dijkstra
//
//  Created by Dominique Michael Abejar on 23/07/2019.
//  Copyright © 2019 BSIT. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTEX 5           /* vertices 0 to  4 */
#define SENTINEL  999     /* for infinity */
#define SIZE 20            /* Array size   */

/**********************************************
 * Data structure Definition                  *
 *********************************************/

typedef unsigned char SET;              /* Computer Word Implementation of Set */
                                              
typedef int LabelAdjMatrix[VERTEX][VERTEX];  /* Definition of  Labeled Adjacency List */

typedef struct {
    int tail;    /* Tail Vertex */
    int head;    /* Head Vertex */
    int weight;  /* weight of the arc/edge */
}edgeType;
  
/*** Array Implementation of list of edges ***/
typedef struct {
  edgeType edges[SIZE];
  int last;      /* index of last element, -1 if list is empty */
}edgeList;

typedef struct node{
    edgeType edge;
    struct node * next;
}*List;

typedef List *AdjList;

typedef struct cell{
    int elem;
    struct cell *next;
}*QList;

typedef struct{
    QList front;
    QList rear;
}Queue;


typedef struct{
    QList top;
}Stack;

/**********************************************
 * Function Prototypes                        *
 *********************************************/
void populateLabAdjMatrix(LabelAdjMatrix C);         /* Code is provided */
void displayAdjMatrix(LabelAdjMatrix C);             /* Code is provided */
edgeList  createSortedList(LabelAdjMatrix  M);
void displayEdgeList(edgeList L);
int * dijkstraAlgo(LabelAdjMatrix C, int source);
void displayShortestPath(int D[], int source);       /* Code is provided */
void floyd(LabelAdjMatrix M);
void warshall(LabelAdjMatrix M);
void prim(LabelAdjMatrix M);
void kruskal(LabelAdjMatrix M);
AdjList * convertAdjMatrix(LabelAdjMatrix M);
void displayAdjList(AdjList *L);
void initQueue(Queue *Q);
void enqueue(Queue *Q, int elem);
int front(Queue Q);
void dequeue(Queue *Q);
void bfs(int startingVertex, LabelAdjMatrix M);
void initStack(Stack *S);
void push(Stack *Q, int elem);
void pop(Stack *Q);
void dfs(int startingVertex, LabelAdjMatrix M);
/*******************************************************************************************
 * Problem 1: Write the code of the following functions:                                   *
 *  A] createSortedEdgeList(). The function will create and return a sorted list of edges. *
 *     List of edges is sorted in ascending order according to weights.                    *
 *  B] displayEdgeList(). The function will list the elements of the edgeList, each element*
 *     information will be displayed per row. Format:  (tail, head) :: Value of Weight     *
 *******************************************************************************************/

/*******************************************************************************************
 * Problem 2: Write the code of the following function:                                   *
 *  A] dijkstraAlgo(). The function will return a 1 dimensional array containing the      *
 *     shortest path from any given vertex to the other the vertices.                     *
 * Note: Use computer word implementation for any set ADT; Other implementation will not  *
 *       be considered. The only single dimensional array used is the one returned by this*
 *       function.                                                                        *
 *                                                                                        *
 *  The main function will call dijkstraAlgo() as many times as the number of vertices in *
 *  the graph.                                                                            *
 *****************************************************************************************/
 
 
int main()
{
    /*** Put Declation of variables Here ***/
    LabelAdjMatrix A;
   //AdjList *L;
    
    int source, *D; //Counter for number of vertices
    
    /*** Problem 1:  ***/
    printf("\nProblem 1: Statements and Calls");
    populateLabAdjMatrix(A);
    displayAdjMatrix(A);

    /*** Problem 2:  ***/
    printf("\nProblem 2: Statements and Calls");
       
    for(source = 0; source < VERTEX; source++){
        D = dijkstraAlgo(A, source);
        displayShortestPath(D, source);
    }

    floyd(A);
    warshall(A);
    prim(A);
    kruskal(A);
    bfs(0, A);
    dfs(0, A);
    
    return 0;
}

 
void displayShortestPath(int D[], int source)
{
    int x;
    
    printf("\n\nShortest Path from %d::", source);
    for(x = 0; x < VERTEX; x++){
        if (D[x] == SENTINEL){
            printf("\nD[%d] = ∞", x);
        }else {
            printf("\nD[%d] = %d", x, D[x]);
        }
        
    }
}


void populateLabAdjMatrix(LabelAdjMatrix C)
{
    LabelAdjMatrix A = { {999,  10, 999,  30, 100}, {999, 999,  50, 999, 999},
                         { 20, 999, 999, 999,  10}, {999, 999,  20, 999,  60},
                         {999, 999, 999, 999, 999}
                           };
    memcpy(C, A, sizeof(LabelAdjMatrix));
    
}

 void displayAdjMatrix(LabelAdjMatrix A)
 {
     int row, col;
      
     printf("\n\nLabeled Adjacency Matrix");
    for(row = 0; row< VERTEX; row++){
          printf("\n");
          for(col = 0; col < VERTEX; col++){
              if (A[row][col] == SENTINEL){
                  printf("%7∞");
            } else {
                  printf("%7d", A[row][col]);
            }
        }
    }
    printf("\n");
}

edgeList createSortedList(LabelAdjMatrix M){
    edgeList sorted;
    int i, j, trav;
    
    sorted.last = -1;

    for(i  = 0; i < VERTEX; i++){
        for(j = 0;j < VERTEX; j++){
            if(i != j && M[i][j] != SENTINEL){
                for(trav = sorted.last + 1; trav > 0 && sorted.edges[trav - 1].weight > M[i][j];trav--){
                    sorted.edges[trav] = sorted.edges[trav - 1];
                }
                
                sorted.edges[trav].tail = i;
                sorted.edges[trav].head = j;
                sorted.edges[trav].weight = M[i][j];
                sorted.last++;
            }
        }
    }
    
    return sorted;
}

void displayEdgeList(edgeList eL){
    int i;
    
    for(i = 0; i < eL.last + 1; i++){
        printf("\n Tail: %d :: Head: %d :: Weight: %d", eL.edges[i].tail, eL.edges[i].head, eL.edges[i].weight);
    }
}

int * dijkstraAlgo(LabelAdjMatrix M, int source){
    int *D, *visited, i, trav, min;
    
    D = (int *)malloc(sizeof(int)*VERTEX);
    visited = calloc(VERTEX, sizeof(int));
    
    if(D != NULL){
        
        //Copy Weight and Initialize path to itself to 0
        for(i = 0; i < VERTEX; i++){
            D[i] = (i != source)? M[source][i] : 0;
        }
        
        //Mark Source as Visited
        visited[source] = 1;
        
        for(trav = 0; trav < VERTEX; trav++){
            min = -1; //Initialize Min
            
            //Find the minimum node of unvisited nodes
            for(i = 0; i < VERTEX; i++){
                if(visited[i] != 1){
                    if(min != -1){
                        min = (D[i] < D[min])? i : min;
                    }else{
                        min = i;
                    }
                }
            }
            
            visited[min] = 1; //Mark minimum node as visited
            
            //Get smallest new path
            for(i = 0; i < VERTEX; i++){
                if(visited[i] != 1 && D[i] > D[min] + M[min][i]){
                    D[i] = D[min] + M[min][i];
                }
            }
        }
    }
    

    return D;
}

void floyd(LabelAdjMatrix M){
    int i, j, k;
    LabelAdjMatrix DisMat;
    
    
    //Copy AdjMatrix to make Distance Matrix and make path to itself as 0
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            DisMat[i][j] = (i == j)? 0 : M[i][j];
        }
    }
    
    for(k = 0; k < VERTEX; k++){
        for(i = 0; i < VERTEX; i++){
            for(j = 0; j < VERTEX; j++){
                if(DisMat[i][j] > DisMat[i][k] + DisMat[k][j]){
                    DisMat[i][j] = DisMat[i][k] + DisMat[k][j];
                }
            }
        }
    }
    
    printf("\n\n---Floyd---");
    displayAdjMatrix(DisMat);
}

void warshall(LabelAdjMatrix M){
    int i, j, k;
    LabelAdjMatrix A;
    
    //Copy AdjMatrix to make Distance Matrix and make path to itself as 0
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            A[i][j] = (i == j)? 0 : M[i][j];
        }
    }
    
    for(k = 0; k < VERTEX; k++){
        for(i = 0;i < VERTEX; i++){
            for(j = 0; j < VERTEX; j++){
                if(A[i][j] == 0){
                    A[i][j] = A[i][k] && A[k][j];
                }
            }
        }
    }
    
    printf("\n\n---Warshall---");
    displayAdjMatrix(A);
}

void prim(LabelAdjMatrix M){
    int i, j, numEdges, min, minCost = 0, *visited, *parent, *D;
    LabelAdjMatrix U;
    edgeList spanningTree;
    
    //Initialize spanning Tree to be empty
    spanningTree.last = -1;
    
    //Initialize visited to 0
    visited = calloc(VERTEX, sizeof(int));
    parent = calloc(VERTEX, sizeof(int));
    D = calloc(VERTEX, sizeof(int));
    
    //Convert Adj Matrix to Undirected Graph
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            U[i][j] = M[i][j];
            if(M[i][j] != SENTINEL){
                U[j][i] = U[i][j];
            }else{
                U[i][j] = M[j][i];
            }
        }
    }

    //Get Weight of Source
    for(i = 0; i < VERTEX; i++){
        D[i] = U[0][i];
    }

    //Num edges must be VERTEX - 1
    numEdges = VERTEX - 1;

    //Mark source to visited
    visited[0] = 1;
    
    printf("\n\n---Undirected Adjacency Matrix---");
    displayAdjMatrix(U);
    
    while(numEdges > 0){
        min = -1;
        
        //Get the smallest unvisited node
        for(i = 1; i < VERTEX; i++){
            if(visited[i] != 1){
                if(min != -1){
                    min = (D[i] < D[min])? i : min;
                }else{
                    min = i;
                }
            }
        }

        j = parent[min];
        visited[min] = 1;
        
        //Get Minimum
        for(i = 1; i < VERTEX; i++){
            if(visited[i] != 1 && D[i] > U[i][min]){
                D[i] = U[i][min];
                parent[i] = min;
            }
        }
    
        minCost += U[j][min];
        
        spanningTree.edges[++spanningTree.last].head = min;
        spanningTree.edges[spanningTree.last].tail = j;
        spanningTree.edges[spanningTree.last].weight = U[j][min];
        
        numEdges--;
        
    }
    
    printf("\n\nPrim Minimum Cost: %d", minCost);
    displayEdgeList(spanningTree);
}

void kruskal(LabelAdjMatrix M){
    int i, j, *visited, *D, mincost = 0;
    LabelAdjMatrix U;
    edgeList sorted, spanningtree;
    
    
    visited = calloc(VERTEX, sizeof(int));
    D = calloc(VERTEX, sizeof(int));
    
    //Initialize spanning Tree to be empty
    spanningtree.last = -1;
    
    //Convert Adj Matrix to Undirected Graph
    for(i = 0; i < VERTEX; i++){
        for(j = 0; j < VERTEX; j++){
            U[i][j] = M[i][j];
            if(M[i][j] != SENTINEL){
                U[j][i] = U[i][j];
            }else{
                U[i][j] = M[j][i];
            }
        }
    }
    
    //Sort Weight of the graph
    sorted = createSortedList(M);

    //Total Edges of MST must be VERTEX - 1
    for(i = 0, j = VERTEX - 1; j > 0 && i < sorted.last + 1; i++){
        if(visited[sorted.edges[i].head] != 1){ //Check if head is already visited
            visited[sorted.edges[i].head] = 1;  //Mark Head as visited to avoid cycle
            spanningtree.edges[i].tail = sorted.edges[i].tail;
            spanningtree.edges[i].head = sorted.edges[i].head;
            spanningtree.edges[i].weight = sorted.edges[i].weight;
            spanningtree.last++;
            mincost += spanningtree.edges[i].weight;
            j--;
        }
    }
    
    printf("\n\nKruskal Minimum Cost: %d", mincost);
    displayEdgeList(spanningtree);
}

void bfs(int startingVertex, LabelAdjMatrix M){
    int *S, i, j;
    Queue Q;
    
    //Initialize S to contain 0's
    S = calloc(VERTEX, sizeof(int));
    
    //Init Queue
    initQueue(&Q);
    
    //Mark source as visited
    S[startingVertex] = 1;
    
    //Enqueue source
    enqueue(&Q, startingVertex);
    
    
    printf("\n\n--BFS--");
    printf("\n%d", startingVertex);
    
    //While queue is not empty
    while(Q.front != NULL){
        dequeue(&Q);
        
        for(i = 0; i < VERTEX; i++){
            for(j = 0; j < VERTEX; j++){
                if(M[i][j] != SENTINEL && S[j] != 1){
                    enqueue(&Q, j);
                    S[j] = 1;
                    printf("\n%d", j);
                }
            }
        }
    }
}


void initQueue(Queue *Q){
    Q->front = NULL;
    Q->rear = NULL;
}

void enqueue(Queue *Q, int elem){
    QList temp;
    
    temp=(QList)malloc(sizeof(struct cell));
    
    if(temp != NULL){
        temp->elem = elem;
        temp->next = NULL;
        
        if(Q->rear == NULL){
            Q->front = temp;
        }else{
            Q->rear->next = temp;
        }
        
        Q->rear = temp;
    }
}

int front(Queue Q){
    return Q.front->elem;
}

void dequeue(Queue *Q){
    QList temp;
    
    temp = Q->front;
    Q->front = temp->next;
    free(temp);
}

void dfs(int startingVertex, LabelAdjMatrix M){
    int *visited, i, j;
    Stack S;
    
    //Initialize visited to 0's
    visited = calloc(VERTEX, sizeof(int));
    initStack(&S);
    
    push(&S, startingVertex);
    visited[startingVertex] = 1;

    printf("\n\n--DFS--");
    printf("\n%d", startingVertex);
    while(S.top != NULL){

        i = S.top->elem;
       
        for(j = 0; j < VERTEX;){
            if(M[i][j] != SENTINEL && visited[j] != 1){
                visited[j] = 1;
                i = j;
                push(&S, j);
                j = 0;
                printf("\n%d", S.top->elem);
            }else{
                j++;
            }
        }
    
        pop(&S);
    }
}

void initStack(Stack *S){
    S->top = NULL;
}

void push(Stack *Q, int elem){
    QList temp;
       
    temp = (QList)malloc(sizeof(struct cell));
    
    if(temp != NULL){
        temp->elem = elem;
        temp->next = Q->top;
        Q->top = temp;
    }
}

void pop(Stack *Q){
    QList temp;
    
    temp = Q->top;
    Q->top = temp->next;
    free(temp);
}
