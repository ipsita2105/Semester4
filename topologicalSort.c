/*
Programmer's name: Ipsita Singh
Roll No. : 111601033
Program : Topological Sort
Date & Time: Tue Jan  20 23:33:50 IST 2018
*/


#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct vertex
{

    int previous;

    int pre;

    int post;

};


struct list
{

    struct node *head;		// Each list of vertices has a head

};

struct graph
{

    int N;				// Total number of vertices

    struct list *adj;		// List of adjacent vertices

    struct vertex *v;

};

struct stack
{

    int data[500];

    int top;

};

struct stack* newStack();

void stackPush(struct stack *s,int x);

int stackPop(struct stack *s);

int stackEmpty(struct stack *s);


struct graph* readGraph(char *filename);	//Makes lists from file

int Explore(struct graph *g,int i,int discovered[],struct stack *s);

int classifyEdges(struct graph *g);		// Classifies edges based on pre and post values

void TopologicalSort(struct graph *g);

int main()
{

    char *filename;

    int rootNumber;


    struct graph* g = readGraph(filename);


    printf("Adjacency list is-\n");
    int i;

    for(i=0; i<g->N; i++)
        {

            struct node *u = g->adj[i].head;

            while(u)
                {

                    printf("%d, ",u->data);

                    u = u->next;

                }

            printf("\n");

        }



    TopologicalSort(g);


}


struct graph* readGraph(char *filename)
{

    int i,j;

    int n;

    struct graph *g = (struct graph*)malloc(sizeof(struct graph));

    scanf("%d\n",&n);

    g->N = n;		// Define total number of vertices

    g->adj= (struct list*)malloc(n*sizeof(struct list));


    for(i=0; i<n; i++)
        {

            g->adj[i].head = NULL;


            int d;

            scanf("%d ",&d);

            if(d != -1)
                {

                    struct node *newNode = (struct node*)malloc(sizeof(struct node));
                    newNode->data = d;

                    newNode->next = g->adj[i].head;
                    g->adj[i].head = newNode;


                    struct node *current = g->adj[i].head;



                    while(1)
                        {

                            scanf("%d ",&d);

                            if(d == -1)
                                {
                                    break;
                                }

                            current->next = (struct node*)malloc(sizeof(struct node));
                            current->next->data = d;
                            current = current->next;


                        }

                    current->next = NULL;
                    scanf("\n");


                }

        }


    return g;

}



void TopologicalSort(struct graph *g)
{

    int i;

    int discovered[g->N];

    g->v = (struct vertex*)malloc((g->N)*sizeof(struct vertex));

    struct stack *s = newStack();

    for(i=0; i<g->N; i++)
        {

            discovered[i] = 0;
            g->v[i].pre = -1;
            g->v[i].post = -1;
            g->v[i].previous = -1;

        }

    int r;

    for(i=0; i<g->N; i++)
        {

            if(discovered[i] == 0)
                {

                    r = Explore(g,i,discovered,s);	//Explore undiscovered vertex

                    if(r == 0)
                        return;

                }

        }

    printf("Graph is a DAG\n");
    printf("Topological Sorting\n");



    while(!stackEmpty(s))
        {

            printf("%d ,",stackPop(s));

        }

    printf("\n");

    free(g->v);

    return;

}



int Explore(struct graph *g,int i,int discovered[],struct stack *s)
{

    static int clock = 1;		// static so that clock is not re-initialized everytime

    int r;

    g->v[i].pre = clock++;

    discovered[i] = 2;

    struct node *u = g->adj[i].head;

    while(u)
        {

            if(discovered[u->data] == 0)
                {

                    g->v[u->data].previous = i;
                    r = Explore(g,u->data,discovered,s);

                    if(r == 0)
                        return 0;

                }

            else
                {


                    if(g->v[i].pre > g->v[u->data].pre && g->v[i].post == -1 &&g->v[u->data].post == -1)
                        {

                            // A back edge found

                            printf("Not a DAG\n");

                            // Print cycle here

                            int p = i ;

                            printf("%d<-",i);

                            while(g->v[p].previous != u->data)
                                {

                                    printf("%d <-",g->v[p].previous);

                                    p = g->v[p].previous;

                                }

                            printf("%d <- %d\n",u->data,i);

                            return 0;


                        }




                }

            u = u->next;

        }

    g->v[i].post = clock++;		// Reach here when vertex exploration is finished


    stackPush(s,i);
    return 1;

}



struct stack* newStack()
{
    struct stack *new = malloc(sizeof( struct stack));

    new -> top = -1;

    return new;

}


void stackPush(struct stack *s,int x)
{

    if(s->top == -1)
        {

            s->top =0;

            s->data[s->top] = x;

        }

    else
        {

            s->top = s->top+1;
            s->data[s->top] = x;
        }

}

int stackEmpty(struct stack *s)
{

    if(s->top == -1)
        {

            return 1;

        }

    else
        {
            return 0;

        }

}

int stackPop(struct stack *s)
{

    int x = s->data[s->top];
    s->top = s->top -1;

    return x;
}


