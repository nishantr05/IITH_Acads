#include <iostream>
using namespace std ;

struct node
{
	int val ;
	node* left, right, p ;//p - parent
};
node* main_root = NULL ;

void insertnode(node* root, int data)
{
	node* newnode = new node() ;
	if (main_root == NULL)
	{ 
	    main_root = newnode;
	    newnode -> left = newnode -> right = newnode-> p = NULL ;
	}
	

 

}
