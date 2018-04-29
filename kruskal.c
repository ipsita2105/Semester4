/*
Programmer's name: Ipsita Singh
Roll No. : 111601033
Program : Implementation of Kruskal's Algorithm
Date & Time: Tue Feb 18 18:40:29 IST 2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

	struct edge{		// Defines each edge

		int u;
		int v;
		int w;

	};

	struct list{	      // List of edges  		

		struct edge *edge_list;
		int V;
		int E;

	};

	struct vertexSet{	// Collection of all vertices

		struct vertex *vSet;

	};

	struct vertex{		// Defines each vertex

		int id;
		int rank;
		int parent;

	};


	struct list* readGraph();				// Retruns the edge list

	void mergeSort(struct list *elist, int l, int r);	// Sorts the edges
	void merge(struct list *elist, int l, int m, int r);

	void kruskal(struct list *l);		

	void makeSet(struct vertexSet *v,int num);
	void Union(struct vertexSet *v,int uVertex,int vVertex);
	int find(struct vertexSet *v,int u);


int main(){

	struct list *e_list;
	int i;

	e_list = readGraph();
	
	mergeSort(e_list,0,(e_list->E)-1);   // Sorts all the edges
	    
	printf("Edges in the MST are-\n");    
	kruskal(e_list);

}


void kruskal(struct list *l){

	struct vertexSet *v = (struct vertexSet*)malloc(sizeof(struct vertexSet));
	v->vSet = (struct vertex*)malloc((l->V)*sizeof(struct vertex));

	int i;
	int weight =0;

	for(i=0;i<l->V;i++){

		makeSet(v,i);		// Make set for each vertex

	}


	for(i=0;i<l->E;i++){		// Iterate over edges in increasing order of weight

		int uVertex = l->edge_list[i].u;
		int vVertex = l->edge_list[i].v;

	
		if(find(v,uVertex) != find(v,vVertex)){     // If not part of same component, add the edge
	
			Union(v,uVertex,vVertex);			
			printf("%d -> %d\n",uVertex,vVertex);
			weight = weight + l->edge_list[i].w;
	
		}

	}
	
	printf("Weight of MST =%d\n",weight);


}

void Union(struct vertexSet *v,int uVertex,int vVertex){

	int x = find(v,uVertex);
	int y = find(v,vVertex);
	

	if(x != y){
	
		
		if(v->vSet[x].rank == v->vSet[y].rank){
		
			v->vSet[y].parent = x;
			
			v->vSet[x].rank = v->vSet[x].rank + 1;
		
		}
		
		else if(v->vSet[x].rank > v->vSet[y].rank){
			
			v->vSet[y].parent = x;
		
		}
		
		else{
		
			v->vSet[x].parent = y;
		
		}
	
	}
	
	else
	return;


}




void makeSet(struct vertexSet *v,int num){

	v->vSet[num].id = num;
	v->vSet[num].parent = num;
	v->vSet[num].rank = 0;

}


int find(struct vertexSet *v,int u){

	if(v->vSet[u].parent != v->vSet[u].id){
	
		v->vSet[u].parent = find(v,v->vSet[u].parent);
	
	}

	return v->vSet[u].parent;

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

	l->edge_list[i].v = v1;
	l->edge_list[i].u = v2;
	l->edge_list[i].w = weight;     
  
    }

return l;

}

void merge(struct list *elist, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    struct list *L = (struct list*)malloc(sizeof(struct list));
    L->edge_list = (struct edge*)malloc((n1)*sizeof(struct edge));
    
    struct list *R = (struct list*)malloc(sizeof(struct list));
    R->edge_list = (struct edge*)malloc((n2)*sizeof(struct edge));
    
 
   
    for (i = 0; i < n1; i++){
        
         L->edge_list[i].u = elist->edge_list[l+i].u;
         L->edge_list[i].v = elist->edge_list[l+i].v;
         L->edge_list[i].w = elist->edge_list[l+i].w;
        
        }
        
    for (j = 0; j < n2; j++){
    
        R->edge_list[j].u = elist->edge_list[m+1+j].u;
        R->edge_list[j].v = elist->edge_list[m+1+j].v;
        R->edge_list[j].w = elist->edge_list[m+1+j].w;
        
        }

    i = 0; 
    j = 0; 
    k = l; 
    
    while (i < n1 && j < n2)
    {
        if (L->edge_list[i].w <= R->edge_list[j].w)
        {
            elist->edge_list[k].w = L->edge_list[i].w;
            elist->edge_list[k].u = L->edge_list[i].u;
            elist->edge_list[k].v = L->edge_list[i].v;
            i++;
        }
        else
        {
            elist->edge_list[k].w = R->edge_list[j].w;
            elist->edge_list[k].u = R->edge_list[j].u;
            elist->edge_list[k].v = R->edge_list[j].v;
            j++;
        }
        k++;
    }
 

    while (i < n1)
    {
        elist->edge_list[k].w = L->edge_list[i].w;
        elist->edge_list[k].u = L->edge_list[i].u;
        elist->edge_list[k].v = L->edge_list[i].v;
        i++;
        k++;
    }
 

    while (j < n2)
    {
        elist->edge_list[k].w = R->edge_list[j].w;
        elist->edge_list[k].u = R->edge_list[j].u;
        elist->edge_list[k].v = R->edge_list[j].v;
        j++;
        k++;
    }
    
    free(L);
    free(R);
}
 

void mergeSort(struct list *elist, int l, int r)
{
    if (l < r)
    {
  
        int m = (r+l)/2;
        mergeSort(elist, l, m);
        mergeSort(elist, m+1, r);
 
        merge(elist, l, m, r);
    }
}	
