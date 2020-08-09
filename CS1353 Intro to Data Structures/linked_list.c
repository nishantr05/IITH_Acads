#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node* next ;	
	//struct node* prev ;
} node; 

// '->' is nothing but a kind of dereferencing operator
//append element at end of list : O(n)
node* tail  = NULL;
void append( node** head_ptr, int x) // takes value of head (pointer to node) by reference. thus, any change in address stored  
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node -> value = x;       
	new_node -> next = NULL ; // new node is inserted in the end so will have next link as null.
	if (*head_ptr == NULL)
	{
	  *head_ptr = new_node ; //  *head_ptr is pointer to 1st node, i.e has the address of first node.
	  tail = new_node ;
	  return ;
	}
    //apending in O(1) with tail pointer
	tail -> next = new_node;
	tail = new_node;
	/* appending in O(n)
	node* temp = *head_ptr ;
	while(temp -> next != NULL)
		temp = temp -> next ;
	temp -> next = new_node ;
    */
}
void insert_begining(node** head_ptr, int x) //inserts given element at start of list
{
	node* new_node = (node*)malloc(sizeof(node)) ;
	new_node -> value = x;
	new_node -> next = *head_ptr ; //head points to fisrt node. thus setting (*new_node).next = head, will mean new_node is pointing to fisrt node.
    *head_ptr = new_node ;
} 
void insert_at_n(node** head_ptr, int n, int x) // inserts element at position "n" (max value of n = currentsize +1)
{
	node* new_node = (node*)malloc(sizeof(node)) ;
	new_node -> value = x;
	if (n == 1) //start of list
	{
		new_node -> next = *head_ptr ;
		*head_ptr = new_node ;	
		return ;
	}
	node* temp = *head_ptr ;
	for (int i = 1; i < n-1; ++i) //go uptill n-1th node and insert new_node
		temp = temp -> next ;
	if (temp -> next == NULL)
	  tail = new_node ;
	new_node -> next = temp -> next ;
	temp -> next = new_node ;
	
}
void print(node* temp) // here temp is give the address at head
{
	//node* temp = head ;
	while(temp -> next != NULL)
	{
		printf("%d ", temp -> value );
		temp = temp -> next ;
	}
	printf("%d\n", temp -> value);
	/*
	while(temp != NULL)
	{
		printf("%d ", temp -> value );
		temp = temp -> next ;
	} 
	printf("\n");  */
    
}
void delete_n(node** head_ptr, int n)
{
	node* temp = *head_ptr ;
	if (n == 1)
	{
		*head_ptr = temp -> next ;
		free(temp) ;
		return ;
	}
	for (int i = 1; i < n-1; ++i)
	   temp = temp -> next;        // temp points to n-1th node.
	node* temp1 = temp -> next ;   // temp1 points to the nth node.
	temp -> next = temp1 -> next ;  // linking the n-1th node and the n+1 th node
	if (temp1 == tail)
	  tail = temp ;
	free(temp1) ;
}
void delete_key(node** head_ptr, int key)
{
	node *current = *head_ptr ;
	node* prev = NULL ;
	while(current != NULL)
	{
		if (current -> value == key)
		 break ;
		prev = current ;
		current = current -> next ;
	}
	if (current != NULL)
	{
		if (prev == NULL)
		   *head_ptr = current -> next ;
        else
		  prev -> next = current -> next ;
	 
	     if (current -> next == NULL)
        	tail = prev ;
		free(current);
	}
	else
	 printf("Key not present\n");

}


   
int main()
{
	node * head = NULL;// intially the list is empty
	append(&head, 6) ; //here 'head' is passed reference, so all changes are taken care of
	append(&head, 10) ;
	append(&head, -2) ;
	print(head) ;
	insert_begining(&head, 3) ;
	print(head) ;
	insert_begining(&head, 7) ;
	print(head) ;
	insert_begining(&head, 11) ;
	print(head) ;
	insert_at_n(&head, 4, 0) ;
	print(head) ;
	delete_n(&head, 4) ;
	print(head) ;
	delete_n(&head, 1) ;
	print(head) ;
	append(&head, 9) ;
	print(head) ;
	delete_key(&head, 9) ;
	print(head) ;
	delete_key(&head, 7) ;
	print(head);

	return 0;
}