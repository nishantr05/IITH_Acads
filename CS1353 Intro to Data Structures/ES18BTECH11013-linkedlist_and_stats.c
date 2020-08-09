#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int value ;
	struct  node* next ;
	
} node;
node* head = NULL  ;                           // head to point to the start of the list.
node* tail = NULL  ;                           //here, tail pointer points to the end of the list and allows us to append an element in constant time.

void append(int x)
{
	node* new_node = (node*)malloc(sizeof(node)) ;  // create a new node dynamically 
	new_node -> value = x ;
	new_node -> next = NULL ;
	if (head == NULL)                          // appending the first element in the list
	{
		head = new_node ;
		tail = new_node ;
		return ;	
	}
	 
	tail -> next = new_node;                   //link the newly created node to the end of the list
	tail = new_node ;                          //reset the tail pointer to point to the end of the list
} 
void min()
{
	node* current ;
	current = head;
	
	int min = head -> value ;
	while(current != NULL)                     //current points to the first node intially, and is used to traverse the list
	{
		if ((current -> value) < min)
			min = current -> value ;

		current = current -> next;
	}
	printf("Min element in the list is = %d\n", min);
}
void mean()
{
	node* current = head ;
	int sum = 0, count = 0;                //sum to keep track of the sum of elements, and count to count the number of elements
	while(current != NULL)
	{
		count++;
		sum += current -> value ;
		current = current -> next;
	}
	double mean = sum / count ;        
	current = head;
	while(current != NULL)
	{
		if ((current -> value) > mean)        //checking for value in the list greater than mean
		{    
			printf("First element strictly greater than mean is : %d\n", current -> value);
			return ;
	    }
		current = current -> next ;	
	}

	printf("No element strictly greater than mean\n");
}

int main()
{
	int input ;
	printf("Enter the elements\n");
	while(1)
	{
		scanf("%d", &input);
		if (input < 0)
			break ;

		append(input);
	}
	min();
	mean();
	return 0;
}