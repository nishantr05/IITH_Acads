#include <stdio.h>
#include <stdlib.h>
#include<time.h>

long unsigned int fibonacci(int n)  //recurssive function 'fibonacci' to calculate nth fibonacci number.
{
	/* base case */
    if (n == 1) //return 0 as the 1st fibonacci number
     return 0;
    if (n == 2) //return 1 as the 2nd fibonacci number
     return 1;
    
    return fibonacci(n-1) + fibonacci(n-2); //return value of (n-1)th term + (n-2)th term as the nth fibonacci number
   
}

int main () 
{  
  for (int n = 1; n <=40; n=n+5)  //for loop to iterate through different values of 'n'
   {
     	clock_t start, end;             
 	   start = clock();       //Timer starts
       long unsigned int nth_fibonacci =  fibonacci(n); //Varible 'nth_fibonacci', to store the nth fibonacci number
       end = clock();         //Timer ends

     printf("The fibonacci number at position %d is %ld,and time taken to compute it is %lf \n",n, nth_fibonacci,((double)(end-start))/CLOCKS_PER_SEC );

    } 

    
   return 0;
}