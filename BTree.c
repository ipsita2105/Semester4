#include<stdio.h>
#include<stdlib.h>

#define t 3


	struct BTree{

		struct node *root;

	};

	struct node{

		int n;				// size of node
		int leaf;			// Boolean value
		int key[2*t];			// So that index start at 1
		struct node *c[2*t+1];

	};


struct node *allocateNode();
void SplitChild(struct node **x, int i);
void BTreeInsertNonFull(struct node **x, int k);
void BTreeInsert(struct node **root, int k);
void BTreeSearch(struct node *x,int k);
void printTree(struct node *x);
void DeleteNode(struct node **x,struct node **p,int i,int childNumber);
void Delete(struct node **x,struct node **p,int k,int childNumber);

int main(){

	struct node *root = NULL;
	
	int i,inserts,k,s;
	
	
	while( i != 5){

			printf("\nWhat would you like to do?\n1.Insert Key\n2.Search\n3.Delete Key\n4.Print Tree\n5.Exit\n\n");
			scanf("%d",&i);

			switch(i){

				case 1 :  printf("\nEnter key value\n");
					  scanf("%d",&k);
					  BTreeInsert(&root,k);
					  printf("\n");	
					  printTree(root);
					  printf("\n");
					  break;


				case 2 : printf("Enter element to search\n");
					 scanf("%d",&k);
					 printf("root->");
					 BTreeSearch(root,k);
					 printf("\n");
					 break;
			
			
				case 3 : printf("\nEnter key value\n");
					 scanf("%d",&k); 
					 Delete(&root,&root,k,0);
					 break;
			

				case 4 : printTree(root);
					 break;

				case 5 : i=5;
					 break;

				default : printf("Wrong input\n");
			}


		}

}


struct node *allocateNode(){

	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->leaf = 0;
	newNode->n = 0;
	
	return newNode;
}



void BTreeInsert(struct node **root, int k){
// A wrapper function

	if(*root == NULL){
	
		*root = allocateNode();
		(*root)->key[1] = k;
		(*root)->n = 1;
		(*root)->leaf = 1;
		return;
	}


	// If root is full
	if((*root)->n == 2*t - 1){

		struct node *s = allocateNode();
		s->c[1] = *root;
		s->leaf = 0;
		s->n =0;
		SplitChild(&s,1);
		
		// Should update root
		(*root) = s;

	}

	BTreeInsertNonFull(root,k);
	

}



void BTreeInsertNonFull(struct node **x, int k){

	int i = (*x)->n;

	if((*x)->leaf == 1){
	
		
	
		while(i >=1 && (*x)->key[i] > k){
		
			(*x)->key[i+1] = (*x)->key[i];
			i = i-1;
		
		}
		
		(*x)->key[i+1] = k;
		(*x)->n = (*x)->n + 1;
		
	}
	
	else{
	
	
		while(i >= 1 && (*x)->key[i]>k){
			
			i = i - 1;
		}
		
		i = i + 1;
		
		if((*x)->c[i]->n == 2*t-1){
		
			SplitChild(x,i);
			
			if (k > (*x)->key[i]){
			
				i = i + 1;
			
			}
		
		}
		
		
		BTreeInsertNonFull(&((*x)->c[i]),k);
		
	}

}

void SplitChild(struct node **x, int i){

	struct node *z = allocateNode();
	struct node *y = (*x)->c[i];
	z->leaf = y->leaf;
	z->n = t-1;
	
	for(int j = 1;j<=t-1;j++){
	
		z->key[j] = y->key[j+t];	// copy last t-1 keys
	
	}
	
	if(y->leaf == 0){
	
		for(int j=1;j<=t;j++){
		
			z->c[j] = y->c[j+t];	// children also if its not leaf
		
		}
	
	}
	
	y->n = t-1;
	
	
	for(int j=(*x)->n+1;j>=i+1;j--)
		(*x)->c[j+1] = (*x)->c[j];	// Shift children of parent
		
		
	(*x)->c[i+1] = z;
	
	
	for(int j=(*x)->n;j>=i;j--)
		(*x)->key[j+1] = (*x)->key[j];	// Shift keys of parent
		
	
	(*x)->key[i] = y->key[t];
	
	(*x)->n = (*x)->n + 1;	

}


void BTreeSearch(struct node *x,int k){

int i =1;

	while( i <= x->n && k > x->key[i]){

		i = i + 1;

	}
	
	if(i <= x->n && k == x->key[i]){
	
	
		printf("Key(= %d) found at %d!\n",k,i);
		return;
	
	}


	else if(x->leaf == 1){
	

		printf("key(= %d) doesn't exist\n",k);
		return;
	
	}
	
	else{
	
		printf("c[%d]->",i);
		return BTreeSearch(x->c[i],k);
	
	}

}

void printTree(struct node *x){

	
	// print that node
	
	int j = 1;
		
		while(j <= x->n){		
			
			printf("%d,",x->key[j]);
			j = j + 1;
		}
		
		printf("\n");
	
	
	// then call for childern
	
	if(x->leaf == 0){
	
		int i = 1;
	
		while( i <= x->n + 1){
		
			printTree(x->c[i]);
			i = i + 1;
		}
	
	}
	

}

void Delete(struct node **x,struct node **p,int k,int childNumber){

	int i =1;

	while( i <= (*x)->n && k > (*x)->key[i]){

		i = i + 1;

	}
	
	if(i <= (*x)->n && k == (*x)->key[i]){
	
	
		DeleteNode(x,p,i,childNumber);
		return;
	
	}


	else if((*x)->leaf == 1){
	

		printf("key(= %d) doesn't exist\n",k);
		return;
	
	}
	
	else{
		p = x;
		childNumber = i;
		return Delete(&(*x)->c[i],p,k,childNumber);
	
	}

}

void DeleteNode(struct node **x,struct node **p,int i,int childNumber){
// To delete key at x[i]

	// if its a non minimal leaf
	if((*x)->leaf == 1 && (*x)->n > t -1){

		while(i < (*x)->n){

			(*x)->key[i] = (*x)->key[i+1];
			i++;

		}

	(*x)->n = (*x)->n -1;
	return;

	}
	
	// if leaf and minimal
	if((*x)->leaf == 1 && (*x)->n == t-1){
	
		if((*p)->c[childNumber-1] != NULL && (*p)->c[childNumber-1]->n > t-1){
	
		// if non minimal left sibling exists
		// perform a local rotate
		
		int j = (*x)->n;
		
		while(j >= 1){
		
		     (*x)->key[j+1] = (*x)->key[j];	// shift key right
		     j = j-1;
		
		}
		
		(*x)->key[1] = (*p)->key[childNumber-1];
		(*x)->n = (*x)->n + 1;
		
		struct node *s = (*p)->c[childNumber-1];
		
		(*p)->key[childNumber-1] = s->key[s->n];
		s->n = s->n - 1;
		
		DeleteNode(x,p,i+1,childNumber);
		
		}
		
		else if((*p)->c[childNumber+1] != NULL && (*p)->c[childNumber+1]->n > t-1){
	
		// if non minimal right sibling exists
		// perform a local rotate
		
		int j=1;
		
		struct node *s = (*p)->c[childNumber + 1];
		
		(*x)->n = (*x)->n + 1;
		(*x)->key[(*x)->n] = (*p)->key[childNumber];
		(*p)->key[childNumber] = s->key[1];
		
		while( j < s->n){
		
			s->key[j] = s->key[j+1];
			j++;
		
		}
		
		s->n = s->n -1;
				
		DeleteNode(x,p,i,childNumber);
	
		}
		
		
		//If x is leaf and no non minimal sibling
		// Including both end nodes
		
		else if((*p)->c[childNumber-1] != NULL && (*p)->c[childNumber-1]->n == t-1 && (*p)->c[childNumber+1] != NULL && (*p)->c[childNumber+1]->n == t-1 ){
		
		
			// perform merge	
			struct node *s = (*p)->c[childNumber + 1];
			
			
			int j = (*x)->n;
			
			int recurDelete = j;
			
			j++;
			(*x)->key[j] = (*p)->key[childNumber];
			j++;
			
			int l = 1;
			
				while(l <= s->n){
			
					(*x)->key[j] = s->key[l];
					j++;
					l++;
					(*x)->n = (*x)->n + 1;
				}
			
			(*x)->n = (*x)->n + 1;	
			j = childNumber;
			
			
			while( j < (*p)->n){
			
			
			(*p)->key[j] = (*p)->key[j+1];
			
			j++;
			
			}
			
			j = childNumber + 1;
			
			while( j <= (*p)->n){
			
			(*p)->c[j] = (*p)->c[j+1];
			j++;
			
			}
			
			(*p)->n = (*p)->n - 1;
			
			DeleteNode(x,p,i,childNumber);
		
		
		
		
		
		
		}
		
		else if((*p)->c[childNumber-1] == NULL && (*p)->c[childNumber+1]->n == t-1){
		
		
			// perform merge	
			struct node *s = (*p)->c[childNumber + 1];
			
			
			int j = (*x)->n;
			
			int recurDelete = j;
			
			j++;
			(*x)->key[j] = (*p)->key[childNumber];
			j++;
			
			int l = 1;
			
				while(l <= s->n){
			
					(*x)->key[j] = s->key[l];
					j++;
					l++;
					(*x)->n = (*x)->n + 1;
				}
			
			(*x)->n = (*x)->n + 1;	
			j = childNumber;
			
			
			while( j < (*p)->n){
			
			
			(*p)->key[j] = (*p)->key[j+1];
			
			j++;
			
			}
			
			j = childNumber + 1;
			
			while( j <= (*p)->n){
			
			(*p)->c[j] = (*p)->c[j+1];
			j++;
			
			}
			
			(*p)->n = (*p)->n - 1;
			
			DeleteNode(x,p,i,childNumber);
				
		}
		
		else if((*p)->c[childNumber + 1] == NULL && (*p)->c[childNumber-1]->n == t-1){
		
		
			// perform merge	
			struct node *s = (*p)->c[childNumber - 1];
			
			
			int j = s->n;
			
			int store = j;
			
			j++;
			s->key[j] = (*p)->key[childNumber-1];
			j++;
			
			int l = 1;
			
				while(l <= (*x)->n){
			
					s->key[j] = (*x)->key[l];
					j++;
					l++;
					s->n = s->n + 1;
				}
			
			s->n = s->n + 1;	
			
			(*p)->n = (*p)->n - 1;
			
			DeleteNode(&s,p,store+1+i,childNumber-1);
				
		}
	
	
	}
	
	//For an intermediate node
	if((*x)->leaf == 0){
	
		if((*x)->c[i] != NULL){
		
		
		struct node *p_new = (*p);
		struct node *x_temp = (*x)->c[i];
		int temp_childNumber = i;
		int original_key = (*x)->key[i];
		
			while(x_temp->leaf != 1){
			
			  p_new = x_temp;
			  temp_childNumber = x_temp->n+1;
			  x_temp = x_temp->c[x_temp->n+1];
			  
	
			}
	
		//x = x->c[x->n+1];
		
		int predValue = x_temp->key[x_temp->n];
		DeleteNode(&x_temp,&p_new,x_temp->n,temp_childNumber);
		
		//(*x) = x_temp;
		
		
		// replace with predecessor
		int j = 1;
		int flag = 0;
			while(j <= x_temp->n){
		
				if(x_temp->key[j] == original_key){
					x_temp->key[j] =  predValue;
					flag = 1;
					break;
				}	
				
				j++;	
		
			}
		
			if(flag == 0){
		
				j=1;
			
				while(j <= (*x)->n){
			
					if((*x)->key[j] == original_key){
						(*x)->key[j] = predValue;
						break;
					}
			
				j++;
			
				}
		
		
			}
		
		
		
		
		}
		
	
	}
	

	



return;
}








