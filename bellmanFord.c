#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/********************* GRAPH STRUCTURE*************/

   	struct edge{		// Defines each edge

		int u;
		int v;
		int w;

	};

	struct list{	      // List of edges  		

		struct edge *edge_list;
		int V;
		int E;
		int source;

	};

	struct vertexSet{	// Collection of all vertices

		struct vertex *vSet;

	};

	struct vertex{		// Defines each vertex

		int id;
		int distance;
		int parent;

	};
  

/******************************************************/

struct list* readGraph();

void BellmanFord(struct list *g);


int main(){

	struct list *g = readGraph();
	BellmanFord(g);
}

void BellmanFord(struct list *g){

	struct vertexSet *v = (struct vertexSet*)malloc(sizeof(struct vertexSet));
	v->vSet = (struct vertex*)malloc((g->V)*sizeof(struct vertex));

	for(int i=0;i<g->V;i++){
	
		v->vSet[i].distance = 10000;
		v->vSet[i].parent   = -1;
	
	}
	
	v->vSet[g->source].distance = 0;
	
	for(int i=0;i<(g->V)-1;i++){
	
		for(int j=0;j<g->E;j++){
	
		int uVertex = g->edge_list[j].u;
		int vVertex = g->edge_list[j].v;
				
		
			if(v->vSet[uVertex].distance != 10000 && v->vSet[vVertex].distance > v->vSet[uVertex].distance +g->edge_list[j].w ){		// Relaxation Step
				
				v->vSet[vVertex].distance = v->vSet[uVertex].distance  + g->edge_list[j].w;
				v->vSet[vVertex].parent = uVertex;
				
			}
		
		}
	
	}
	
	// One more round for negative cycles
	
	for(int j=0;j<g->E;j++){
	
		int uVertex = g->edge_list[j].u;
		int vVertex = g->edge_list[j].v;
		
		
		if(v->vSet[vVertex].distance > v->vSet[uVertex].distance + g->edge_list[j].w ){		// Relaxation Step
				
				printf("Graph has negative cycle \n");
				
				// Printing the negative cycle
				
				int p = vVertex;
				int seen[g->V];
				
				for(int i=0;i<g->V;i++)
					seen[i] = 0;
				
				while(seen[p] != 2){
				
					seen[p]++;
					p = v->vSet[p].parent;
				}
				
					for(int i=0;i<g->V;i++){
					
						if(seen[i] == 2){
						
							printf("%d<-",i);
							int x = i;
							i = v->vSet[i].parent;
							
								while(i != x){
							
									printf("%d<-",i);
									i = v->vSet[i].parent;
								}
							
							printf("%d\n",x);
							
							return;
						
						
						}
					
					}
				
				return;
			}
		
		}
		
		
	
	printf("The distances are-\n");

	for(int i=0;i<g->V;i++){

	printf("distance[%d] = %d\n",i,v->vSet[i].distance);

	}

}



struct list* readGraph(){

    int V,E,i;	
  
  
    struct list *l = (struct list*)malloc(sizeof(struct list));
 

    int v1,v2,weight;

    scanf("%d\n",&l->V);
    scanf("%d\n",&l->E);

    l->edge_list = (struct edge*)malloc((l->E)*sizeof(struct edge));	
  
    for(i=0;i<l->E;i++){
  
  
        scanf("%d %d %d\n",&v1,&v2,&weight);

	l->edge_list[i].u = v1;
	l->edge_list[i].v = v2;
	l->edge_list[i].w = weight;     
  
    }
    
    scanf("%d\n",&l->source);

return l;

}
