#include <stdio.h>

//Function to calculate hamming distance.
int hamming (int x, int y)
{
	int count = 0 ;
	int c = x^y ;  //Setting 'c' equal to bitwise xor of x and y
	//while loop which iterates as long as c is greater than 0.
	while(c) 	
	{
		// Counting number of ones in binary representation of 'c' :

		if (c&1)	//If units bit is one, increment count.
			count++;
		c >>= 1;   //right shift by 1
	}
	return count ;
}

int main()
{
	int a, b ;
	printf("Enter two numbers: ") ;	
	while(1)
	{
		scanf("%d %d", &a, &b) ;
		if ((a > 0 && a < 1024)&&(b > 0 && b < 1024))	//if input is valid, then break out.
			break ;
		printf("Please enter numbers between 0 and 1024 : "); //Error message for invalid input.
	}
	printf("Hamming distance is %d\n", hamming(a, b)) ;

	return 0;
}
