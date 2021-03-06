
/*
Programmer's name: Ipsita Singh
Roll No. : 111601033
Program : Implementation og Dijkstra Algorithm
Date & Time: Tue Jan 31 18:35:03 IST 2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/********************* GRAPH STRUCTURE*************/

    struct node{

        int data;            // Vertex number
        int w;
        struct node *next;

    };


    struct list{

        struct node *head;        // Each list of vertices has a head
        struct node *tail;

    };

    struct graph{

        int V;                // Total number of vertices
        int E;                //Total number of edges
        int start;
        int *previous;
        struct list *adj;        // List of adjacent vertices
      
    };


/******************************************************/

struct graph* readGraph();

/****************** HEAP STRUCTRE**********************/

    struct heap{

        struct heapNode **hnode;
        int N;
    	int *position;

    };
  
    struct heapNode{
  
        int id;
        int key_value;
  
    };
  

/****************************************************/

struct heap* makeHeap(struct graph *g);

void minHeapify(struct heap *h,int index);

void swap(struct heapNode **a,struct heapNode **b);

struct heapNode* newHeapNode(struct heap *h,int name,int key);

int parentIndex(int posn);

struct heapNode* deleteMin(struct heap *h);

void printArray(struct heap *h1);


void dijkastra(struct graph *g);

void decreaseKey(struct heap *h,int v,int key);

int allInS(int S[],int n);

int main(){


    struct graph* g = readGraph();
  
    dijkastra(g);

}

void dijkastra(struct graph *g){


	struct heap *h = makeHeap(g);

	g->previous = (int*)malloc(sizeof(int)*(g->V));

	int i;
	int dis[h->N];
	int S[h->N];

	    
	    
	    for(i=0;i<=h->N;i++){
	    
	       dis[i] = 10000;
	       h->hnode[i] = newHeapNode(h,i,dis[i]);
	       h->position[i] = i;
	       g->previous[i] = -1;
	       S[i] = 0;
	    
	    }
	    
	        h->hnode[g->start] = newHeapNode(h,g->start,dis[g->start]);
		dis[g->start] = 0;
		decreaseKey(h,g->start,0);
		g->previous[g->start] = g->start;


    while(h->N >= 0){

        struct heapNode *uNode = deleteMin(h);      
        int u = uNode->id;  
   
        S[u] = 1;      
        struct node *vNode = g->adj[u].head;
      
      
            while(vNode){
          
                int v = vNode->data;
                

                if(S[v] != 1 && dis[u] != 10000){
                
              
                    	if(dis[v] > dis[u] + vNode->w){
                     
                        dis[v] = dis[u] + vNode->w;
                        decreaseKey(h,v,dis[u] + vNode->w);                
            		g->previous[v] = u;
                    }
                             
              
                }
                vNode = vNode->next; 
            }

    }


    // Print the result

    for(i=0;i<g->V;i++){

        printf("d for %d = %d , previous for %d = %d\n",i,dis[i],i,g->previous[i]);

    }

}


void decreaseKey(struct heap *h,int v,int key){


    int i = h->position[v];

    h->hnode[i]->key_value = key;

       while(i && h->hnode[i]->key_value < h->hnode[parentIndex(i)]->key_value){

       
        h->position[h->hnode[i]->id] = parentIndex(i);
        h->position[h->hnode[parentIndex(i)]->id] = i;

        swap(&h->hnode[i],&h->hnode[parentIndex(i)]);

        i = parentIndex(i);

    }

}


int allInS(int S[],int n){

int i;

    for(i=0;i<n;i++){

        if(S[i] == 0)
        return 0;

    }

return 1;

}


void printArray(struct heap *h1){
  
    int j;

        for(j=0;j<=h1->N;j++){

            printf("%d (%d),",h1->hnode[j]->id,h1->hnode[j]->key_value);

        }
  
    printf("\n");  

}






struct graph* readGraph(){

  
    struct graph *g = (struct graph*)malloc(sizeof(struct graph));
  
    scanf("%d\n",&g->V);
    scanf("%d\n",&g->E);
  
    int i;
  
    g->adj = (struct list*)malloc((g->V)*sizeof(struct list));
  
    for(i=0;i<g->V;i++){
  
        g->adj[i].head = NULL;
        g->adj[i].tail = NULL;
  
    }
  
    int v1,v2,weight;
  
    for(i=0;i<g->E;i++){
  
  
        scanf("%d %d %d\n",&v1,&v2,&weight);
      
      
        // Adding first element
        if(g->adj[v1].head == NULL){
      
      
            struct node *newNode = (struct node*)malloc(sizeof(struct node));
            newNode->w = weight;
            newNode->data = v2;
          
            g->adj[v1].head = newNode;
            g->adj[v1].tail = newNode;
          

        }
      
        else{

            struct node *newNode = (struct node*)malloc(sizeof(struct node));
            newNode->w = weight;
            newNode->data = v2;  
          
            g->adj[v1].tail->next = newNode;
            g->adj[v1].tail = newNode;
            //newNode->next = g->adj[v1].tail;
      
      
        }
      
        // Since graph is undirected
        // Add the other edge also
      
      
        if(g->adj[v2].head == NULL){
      
      
            struct node *newNode = (struct node*)malloc(sizeof(struct node));
            newNode->w = weight;
            newNode->data = v1;
          
            g->adj[v2].head = newNode;
            g->adj[v2].tail = newNode;
          

        }
      
        else{

            struct node *newNode = (struct node*)malloc(sizeof(struct node));
            newNode->w = weight;
            newNode->data = v1;  
          
            g->adj[v2].tail->next = newNode;
            g->adj[v2].tail = newNode;
            //newNode->next = g->adj[v1].tail;
      
      
        }
  
      
  
    }
  
    scanf("%d\n",&g->start);

return g;

}

struct heap* makeHeap(struct graph *g){

    struct heap *NewHeap = (struct heap*)malloc(sizeof(struct heap));
    NewHeap->hnode = (struct heapNode**)malloc((g->V - 1)*sizeof(struct heapNode*));
    NewHeap->position = (int*)malloc(sizeof(int)*(g->V - 1));   
    NewHeap->N = g->V - 1;
    return NewHeap;
}



void minHeapify(struct heap *h,int index){

    int s_index = index;

    int lchild_index = 2*index + 1;
    int rchild_index = 2*index + 2;

// Check if lchild and rchild exist and find min of these three

        if(lchild_index <= h->N){

            if(h->hnode[lchild_index]->key_value < h->hnode[s_index]->key_value){
      
                s_index = lchild_index;

            }

        }


        if(rchild_index <= h->N){

            if(h->hnode[rchild_index]->key_value < h->hnode[s_index]->key_value){
      
                s_index = rchild_index;

            }

        }


        // Property voilated => swap

        if(s_index != index){

            swap(&h->hnode[s_index],&h->hnode[index]);

            minHeapify(h,s_index);
          
        }



}

void swap(struct heapNode **a,struct heapNode **b){


    struct heapNode *temp;

    temp = *a;

    *a = *b;

    *b = temp;

}

struct heapNode* newHeapNode(struct heap *h,int name,int key){


    struct heapNode *newNode = (struct heapNode*)malloc(sizeof(struct heapNode));
    newNode->key_value = key;
    newNode->id = name;
  
    //h->N = h->N + 1;    // Increase N


    return newNode;


}

int parentIndex(int posn){


    if(posn == 1)
    return 0;

    if(posn%2 == 0)
    return (posn-2)/2;

    else
    return (posn-2)/2 + 1;

}

struct heapNode* deleteMin(struct heap *h){


    struct heapNode *root = h->hnode[0];

        h->hnode[0] = h->hnode[h->N];
       
    h->position[0] = h->N;
    h->position[h->N] = 0;
   
   
    h->N = h->N -1;
        minHeapify(h,0);

        return root;

}

