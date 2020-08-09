#include <stdio.h>
#define MAX 50

int arr[MAX];
int top = -1;

void push(int x)
{
   if (top >= MAX-1)
     {
     	printf("Error!, stack overflow\n");
     	return;
     }   

   arr[++top] = x;
}

int pop()
{
	return arr[top--];
}

void print()
{
  for (int i = 0; i <= top; ++i)
  	printf("%d ", arr[i]);
  printf("\n");
}

int main()
{
	push(0); print();
	push(10); print();
	push(20); print();
	push(72); print();
	pop();    print();
	pop();    print();
	push(22); print();
	push(200); print();

	return 0;
}