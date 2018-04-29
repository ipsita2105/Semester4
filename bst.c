#include<stdio.h>
#include<stdlib.h>

struct node{

	struct node *left;
	struct node *right;
	struct node *parent;
	int key;

};

struct BST{

	struct node *root;
};


struct node* createBST();
void Insert(struct node **r,int item);
struct node* Search(struct node *r,int item);
struct node* FindMin(struct node *r);
struct node* FindMax(struct node *r);
void InOrder(struct node *r);
void PostOrder(struct node *r);
struct node* PrecedingKey(struct node *r);
void DeleteNode(struct node **r,struct node  **x);
void printTree(struct node *r, int s);


int main(){

	int i;
	int item_value;
	int search_value;
	int pred_value;
	int delete_value;

	struct node *root = createBST();

	struct node *min;
	struct node *ptr;
	struct node *ptr2;

	while( i != 9){

			printf("\nWhat would you like to do?\n1.Insert node\n2.Search\n3.Find Min\n4.InOrder Traversal\n5.PostOrder Traversal\n6.Find Precceding Key\n7.Delete Key\n8.Print Tree\n9.Exit\n\n");
			scanf("%d",&i);

			switch(i){

				case 1 :  printf("\nEnter key value\n");
					  scanf("%d",&item_value);
					  Insert(&root,item_value);	
					  break;


				case 2 : printf("Enter element to search\n");
					 scanf("%d",&search_value);
					 ptr = Search(root,search_value);
					 if(ptr == NULL)
					 printf("Element not present\n");
					 else
					 printf("Element found\n");
					 break;
			
			
				case 3 : min = FindMin(root);
					 printf("Minimum key value = %d\n",min->key);
					 break;
			

				case 4 : InOrder(root); 
					 break;

				case 5 : PostOrder(root);
					 break;

				case 6 : printf("Enter value to find predecessor of\n");
					 scanf("%d",&pred_value);

					 // Check if input is the minimum element
					 min = FindMin(root);

						 if(min->key == pred_value)
					   	 	printf("No predecessor\n");

						 else{
							 ptr = Search(root,pred_value);
							 if(ptr == NULL)
							 printf("Element not present\n");
							 else{
							 ptr2= PrecedingKey(ptr);
							 printf("Predecessor is %d\n",ptr2->key);
							 }
						 }
						 	 
					 break;

				case 7 : printf("Enter key value to delete\n");
					 scanf("%d",&delete_value);
					 ptr = Search(root,delete_value);
				   	 
						 if(ptr->key == root->key && delete_value != root->key){
					
							printf("Element dosen't exist\n");
						}

						 else{

							DeleteNode(&root,&ptr);
						 }
					 break;
					 
				case 8 : printTree(root,0);
					break;	 
				
				case 9 : i = 9;
					break;	

				default : printf("Wrong input\n");
			}


		}


}

struct node* createBST(){

	struct BST *bst = (struct BST*)malloc(sizeof(struct BST));
	bst->root = NULL;

	return bst->root;


}

void Insert(struct node **r,int item){

	struct node *curr   = *r;
	struct node *parent = NULL;
	
	while(curr != NULL){

		if(item <= curr->key){

			parent = curr;
			curr   = curr->left;
		}

		else if(item > curr->key){

			parent = curr;
			curr   = curr->right;

		}

	}

	struct node *NewNode = (struct node*)malloc(sizeof(struct node));
	NewNode->left  = NULL;
	NewNode->right = NULL;
	NewNode->parent= parent;
	NewNode->key   = item;

	if(*r == NULL){

		*r = NewNode; 
		return;
	}

	if(parent != NULL){

		if(item <= parent->key)
			parent->left = NewNode;

		else
			parent->right = NewNode;	

	}

return;	

}

struct node* Search(struct node *r,int item){

	if(r == NULL){
	
		return r;
	}


	else if(r->key == item){

		return r;
	}

	else if(item <= r->key)
		return Search(r->left,item);

	else
		return Search(r->right,item);

}

struct node* FindMin(struct node *r){

	while(r->left != NULL)
		r = r->left;

return r;

}

struct node* FindMax(struct node *r){

	while(r->right != NULL)
		r = r->right;


return r;

}

void InOrder(struct node *r){

	if(r == NULL)
		return;

	InOrder(r->left);
	printf("%d ,",r->key);
	InOrder(r->right);

}

void PostOrder(struct node *r){

	if(r == NULL)
		return;

	PostOrder(r->left);
	PostOrder(r->right);
	printf("%d ,",r->key);

}

struct node* PrecedingKey(struct node *r){


	if(r->left != NULL){

	    struct node *s = FindMax(r->left); // find max	
	    return s;
	}

	else{


	    struct node *p = r->parent;

		while(p != NULL && r==p->left){

			r = p;
			p = p->parent;

		}

		return p;

	}


}

void DeleteNode(struct node **r,struct node  **x){

	struct node *p = (*x)->parent;
	struct node *xNode = *x;
	struct node *rNode = *r;

	
	// If node has no children
	if((*x)->left == NULL && (*x)->right == NULL){
	
		
			if(p == NULL){
		
				*r = NULL;
				free(*x);				
			}
		
			else if(*x == p->left){
		
				p->left = NULL;
				free(*x);			
			}
		
			else if(*x == p->right){
		
				p->right = NULL;
				free(*x);			
			}
			
	}
	
	// if node has only a right child
	else if((*x)->right != NULL && (*x)->left == NULL){
	
		
		if(p == NULL){
		
			*r = (*x)->right;
			(*x)->right->parent = NULL;
			free(*x);
		
		}
		
		else if(*x == p->left){
		
			p->left = (*x)->right;
			(*x)->right->parent = p;
			free(*x);
		
		}
		
		else if(*x == p->right){
		
			p->right = (*x)->right;
			(*x)->right->parent = p;
			free(*x);
		
		}

	}
	
	// if node has only a right child
	else if((*x)->left != NULL && (*x)->right == NULL){
	
		
		if(p == NULL){
		
			*r = (*x)->left;
			(*x)->left->parent = NULL;
			free(*x);
		
		}
		
		else if(*x == p->right){
		
			p->right =(*x)->left;
			(*x)->left->parent = p;
			free(*x);
		
		}
		
		else if(*x == p->left){
		
			p->left = (*x)->left;
			(*x)->left->parent = p;
			free(*x);
		
		}

	}
	
	// if node has both left and right child
	else if((*x)->left != NULL && (*x)->right != NULL){
	
	
		struct node *y = PrecedingKey(xNode);
		int pred_key   = y->key;
		DeleteNode(r,&y);
		
		(*x)->key = pred_key;
	
	}						

}


void printTree(struct node *r, int s){

	if(r == NULL){
	
	return;
	
	}

	s = s + 10;

	printTree(r->right, s);

	printf("\n");

	for(int i=10;i<s;i++){

		printf(" ");
	}
	
	
	printf("%d\n",r->key);

	printTree(r->left,s);

}

