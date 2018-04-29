
/*
Programmer's name: Ipsita Singh
Roll No. : 111601033
Program : Classification of edges in dfs
Date & Time: Tue Jan  2 23:33:50 IST 2018
*/

// Classify Tree and Front edges

// Add nodes at back

// Proof of correctness

// Try a new graph

#include<stdio.h>
#include<stdlib.h>

	struct node{

		int data;			// Vertex number

		struct node *next;

	};


	struct list{

		struct node *head;		// Each list of vertices has a head

	};

	struct graph{

		int N;				// Total number of vertices

		struct list *adj;		// List of adjacent vertices
		
		int *pre;			// Stores pre-time of all vertices
		
		int *post;			// Stores post-time of all vertices

	};
	
	struct stack{

	    int data[500];

	    int top;

	};

struct stack* newStack();

void stackPush(struct stack *s,int x);

int stackPop(struct stack *s);

int stackEmpty(struct stack *s);


struct graph* readGraph(char *filename);	//Makes lists from file

void addInList(int i,struct graph *g,int d);

void dfs(struct graph *g);

void Explore(struct graph *g,int i,int discovered[]);

void classifyEdges(struct graph *g);		// Classifies edges based on pre and post values

int main(){

char *filename;

int rootNumber;

printf("Enter file name\n");
scanf("%s",filename);
/*
printf("Enter root number\n");
scanf("%d",&rootNumber);
printf("Root entered is %d\n",rootNumber);
*/


struct graph* g = readGraph(filename);


printf("Adjacency list is-\n");
int v;

for(v=0;v<g->N;v++){

	struct node *u = g->adj[v].head;

	while(u){

	printf("%d, ",u->data);

	u = u->next;
	
	}

	printf("\n");

	}

	
	dfs(g);


}


struct graph* readGraph(char *filename){

	int i,j;

	int n;		

	FILE *amfile;

	amfile = fopen(filename,"r");	

	if(amfile == 0){

	printf("Error in opening file\n");

	}
	
	struct graph *g = (struct graph*)malloc(sizeof(struct graph));

	fscanf(amfile,"%d\n",&n);
	
	g->N = n;		// Define total number of vertices
	
	g->adj= (struct list*)malloc(n*sizeof(struct list));
	
	printf("Number of vertices = %d\n",n);

	for(i=0;i<n;i++){
		
		g->adj[i].head = NULL;
		
		while(1){
		
		int d;
		
		fscanf(amfile,"%d ",&d);
		
		if(d == -1){
			break;
		}
		
		addInList(i,g,d);
				
		
		}
		
		fscanf(amfile,"\n");		

	}

fclose(amfile);

return g;

}

void addInList(int i,struct graph *g,int d){

// Adding at back
/*
struct node* newNode= (struct node*)malloc(sizeof(struct node));

newNode->data = d;

g->array[i].head->next = newNode;

newNode = g->array[i].head;
*/


//Adding in front

struct node* newNode = (struct node*)malloc(sizeof(struct node));

newNode->data = d;

newNode->next = g->adj[i].head;

g->adj[i].head = newNode;


}


void dfs(struct graph *g){

int i,root;

printf("Enter value of root\n");
scanf("%d",&root);

int discovered[g->N];		// Keeps account of visited and non visited vertices

g->pre = (int*)malloc(sizeof(int)*(g->N));

g->post = (int*)malloc(sizeof(int)*(g->N));

for(i=0;i<g->N;i++){

       discovered[i] = 0;    		  
       g->pre[i] = -1;
       g->post[i] = -1;

    }



for(i=0;i<g->N;i++){

	if(discovered[i] == 0){

		 Explore(g,i,discovered);	//Explore undiscovered vertex 

	}

}



for(i=0;i<g->N;i++){

printf("pre[%d] = %d, post[%d] = %d\n",i,g->pre[i],i,g->post[i]);


}


classifyEdges(g);

free(g->pre);

free(g->post);

}

void Explore(struct graph *g,int i,int discovered[]){

static int clock = 1;		// static so that clock is not re-initialized everytime

g->pre[i] = clock++;

discovered[i] = 2;

struct node *u = g->adj[i].head;

	while(u){

		if(discovered[u->data] == 0){
		
		printf("%d -> %d : Tree Edge\n",i,u->data);

		Explore(g,u->data,discovered);

		}

	u = u->next;

	}

g->post[i] = clock++;		// Reach here when vertex exploration is finished


}


void classifyEdges(struct graph *g){

int i;

for(i=0;i<g->N;i++){

	struct node *u = g->adj[i].head;

	while(u){

	if(g->pre[i] < g->pre[u->data] && g->post[u->data] < g->post[i])
	printf("%d-> %d : Tree or Forward Edge\n",i,u->data);
	
	else if(g->pre[u->data] < g->pre[i] && g->post[i] < g->post[u->data] )
	printf("%d -> %d : Back Edge\n",i,u->data);
	
	else
	printf("%d -> %d : Cross Edge\n",i,u->data);

	u = u->next;
	
	}

	printf("\n");

	}






}



struct stack* newStack(){


    struct stack *new = malloc(sizeof( struct stack));

    //new->size = 10;

    new -> top = -1;

    return new;

}


void stackPush(struct stack *s,int x){

        /*if(s->top == s->size){

        printf("Stack Full !\n");

        return;

        }*/

        if(s->top == -1){

        s->top =0;

        s->data[s->top] = x;

        }

        else{

        s->top = s->top+1;
        s->data[s->top] = x;
        }

}

int stackEmpty(struct stack *s){

    if(s->top == -1){
   
    return 1;
   
    }

    else{
    return 0;

    }

}

int stackPop(struct stack *s){

    /*if(s->top == -1){

    printf("Stack empty\n");

    }

    else{*/
    int x = s->data[s->top];
    s->top = s->top -1;

    return x;
    //}

}




























































