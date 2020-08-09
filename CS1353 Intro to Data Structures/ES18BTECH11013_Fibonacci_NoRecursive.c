#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int main () 
{  

     for (int n = 1; n < 70; n=n+10) //for loop to iterate through different values of 'n' 
    {
      long int fib[3];    // Array 'fib' to store the (n-2)th, (n-1)th and nth terms of a fibonacci sequence
      fib[0] = 0;         //'0' stored as First number of fibonacci series
      fib[1] = 1;         //'1' stored as Second number of fibonacci series

     if (n == 1)
      fib[2] = 0;      //initialize 'fib[2]' to the first term of the series, if n equals to 1
     if (n == 2)
      fib[2] == 1;     //initialize 'fib[2]' to the second term of the series, if n equals to 2
    
     clock_t start, end;             
 	 start = clock();   //Timer starts
      for (int i = 3; i <= n; ++i) //for loop to calculate the nth fibonacci term, if n is greater than 3
     {
    	fib[2] = fib[1] + fib[0];  //'fib[2]' holds the value of the nth fibonacci term
    	fib[0] = fib[1];           //'fib[0]' holds the value of the (n-2)th fibonacci term
    	fib[1] = fib[2];           //'fib[1]' holds the value of the (n-1)th fibonacci term
     }
     end = clock();  //Timer ends
            
     printf("The fibonacci number at position %d is %ld, and time taken to compute it is %lf \n",n, fib[2],((double)(end-start))/CLOCKS_PER_SEC );
    
     
    }
     


   return 0;
}