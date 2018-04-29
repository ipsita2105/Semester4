#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct heap{

	int H[100];

	int N;

};

struct heap* makeHeap();

void minHeapify(struct heap *h,int index);

void swap(struct heap *h,int s_index,int index);

void insert(struct heap *h,int value);

int parentIndex(int posn);

int deleteMin(struct heap *h);

void heapSort(struct heap *h);

void printfArray(struct heap *h1);

void viewHeap(struct heap *h);


int main(){

	int i,j;
	int insert_value;
	struct heap *h1;

	while( i != 7){

			printf("What would you like to do?\n1.Create new Heap\n2.Insert element\n3.Delete Min\n4.Heap Sort\n5.View Heap\n6.View Heap Array\n7.Exit\n\n");
			scanf("%d",&i);

			switch(i){

				case 1 :  h1 = makeHeap();
					  printf("Heap made\n");	
					  break;


				case 2 : printf("Enter element to insert\n");
					 scanf("%d",&insert_value);
					 insert(h1,insert_value);
					 printf("Inserted\n");
					 break;
			
			
				case 3 : printf("Deleted min element =%d\n",deleteMin(h1));
					 break;
			

				case 4 :heapSort(h1); 
					break;

				case 5 : viewHeap(h1);
					 break;

				case 6 : printfArray(h1);
					 break;
				
				case 7 : i = 7;
					break;	

				default : printf("Wrong input\n");
			}


		}


}



struct heap* makeHeap(){

	int n,i;

	struct heap *NewHeap = (struct heap*)malloc(sizeof(struct heap));

	printf("Enter number of elements\n");
	scanf("%d",&n);

		NewHeap->N = n-1;

// Enter all values in heap

		for(i=0;i<NewHeap->N+1;i++){

			printf("Enter node value\n");

			scanf("%d",&NewHeap->H[i]);

		}


// Use Minheapify method
// Bottom up

	int index = n-1;

	while(index != 0){

		
		minHeapify(NewHeap,index);
		index--;
	}


	minHeapify(NewHeap,0);
	return NewHeap;

}



void minHeapify(struct heap *h,int index){

	int s_index = index;

	int lchild_index = 2*index + 1;
	int rchild_index = 2*index + 2;

// Check if lchild and rchild exist and find min of these three

		if(lchild_index <= h->N){

			if(h->H[lchild_index] < h->H[s_index]){
		
				s_index = lchild_index;

			}

		}


		if(rchild_index <= h->N){

			if(h->H[rchild_index] < h->H[s_index]){
		
				s_index = rchild_index;

			}

		}


		// Property voilated => swap

		if(s_index != index){

			swap(h,s_index,index);

			minHeapify(h,s_index);
			
		}



}

void swap(struct heap *h,int s_index,int index){


	int temp;

	temp = h->H[index];

	h->H[index] = h->H[s_index];

	h->H[s_index] = temp;

}

void insert(struct heap *h,int value){

	
	h->N = h->N + 1;	// Increase N

	h->H[h->N] = value;

	int posn = h->N;

	while(posn >= 0 && h->H[posn] < h->H[parentIndex(posn)]){

		swap(h,posn,parentIndex(posn));

		posn = parentIndex(posn);

	}


}

int parentIndex(int posn){


	if(posn == 1)
	return 0;

	if(posn%2 == 0)
	return (posn-2)/2;

	else
	return (posn-2)/2 + 1;

}

int deleteMin(struct heap *h){


	int root_value = h->H[0];

		h->H[0] = h->H[h->N];
		h->N = h->N -1;

		minHeapify(h,0);



		return root_value;

}


void heapSort(struct heap *h){

	int i = 0;

	int j;

	printf("Sorted heap\n");

	int originalSize = h->N;

			for(i=0;i<originalSize;i++){


				printf("%d ,",deleteMin(h));		

			}
			
		
	printf("%d\n",deleteMin(h));


}

void printfArray(struct heap *h1){
	
	int j;

		for(j=0;j<h1->N+1;j++){

			printf("%d ,",h1->H[j]);

		}
	
	printf("\n");	

}


void viewHeap(struct heap *h){



	int position[h->N];
	int i;
	
	
	// Root positioned at 50

	position[0] = 50;


	double level = 1;
	double depth;
	
	depth = log((h->N)+1)/log(2);
	depth = floor(depth);
	printf("depth = %lf\n",depth);
	double children;
	int j;
	int node_num = 1;
	int parent_index;
	int width_last = 6;
	

	for(level = 1;level<=depth;level++){

		children = pow(2.0,level);
		
		int current_width = (1 + depth - level)*width_last;
		
		
		
			for(j=0;j<children;j++){
			
			
			
				if(node_num <= h->N){
		
	
					parent_index = parentIndex(node_num);
				
					// Is Left
				
					if((2*parent_index)+1 == node_num){
				
				
				
					 position[node_num] = position[parent_index] - (current_width)/2;
					 
					 //A small correction
					 
					 if(position[node_num] == position[(node_num-1)]){
					 
					 	position[node_num] = position[node_num] + 1;
					 
					 }
				
				
					}
				
					// Is right child
				
					else{
				
					position[node_num] = position[parent_index] + (current_width)/2;
					
					//A small correction
					 
					 if(position[node_num] == position[(node_num-1)]){
					 
					 	position[node_num] = position[node_num] + 1;
					 
					 }
				
				
					}		
		
		
				node_num++;
			
				}
		
		
			}		

	}

		for(i=0;i<position[0];i++){
	
			printf(" ");
	
		}
	
	printf("%d\n",h->H[0]); 
	
	
	level = 1;
	int space = 0;
	node_num = 1;
	int child_num_level;
	
	for(level = 1;level<=depth;level++){
	
	
		children = pow(2.0,level);
		child_num_level = 0;
		
			
	
				for(space = 0;space<=position[node_num];space++){
				
				
					if(child_num_level<=children && node_num <= h->N){
				
				
						if(space < position[node_num]){
					
							printf(" ");
					
						}
					
						else{
					
							printf("%d",h->H[node_num]);
							node_num++;
							child_num_level++;
						}
					
					}	
				
				
					else
					break;				
					
			        }
			    
			    if(node_num == h->N)
			    break;
			    
			    else
			    printf("\n");
			
	
	
	}




}











