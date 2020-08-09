#include <stdio.h>

int main()
{ 
    int N, i = 2 ;            //integer variable 'i' is declared to keep track of all the even positive integers less than 'N'. It is initialized to 2, as 2 is the first even positive int.
    long long int prod = 1 ;  // 'prod' variable declared of type 'long long int' to calculate product of the even integers.
    scanf("%d", &N) ;
    if (N <= 1)               
    {
      if (N == 1)             //For 'N' = 1, 'N' is still a positive integer, so we output a BLANK line, instead of printing error.
        printf("\n");
      else                    // For 'N' strictly less than 1, there exist no positive even integers less than 'N'. So 'Error' is printed.
        printf("Error\n");       
    }
    else if (N > 30)          //This case exists to make sure no overflow occurs
      printf("Value of 'N' entered is too large to compute the product.\n"); 
    else
    {
        while (i <= N)        //while loop, which executes the below statements, till the condition 'i <= N' is true
        {
           prod = prod*i ;    // value of 'prod' is updated by multiplying with the next even integer.
           printf("%d ", i);
           i += 2 ;           // incrementing 'i' by two, so 'i' takes the value of the next even integer.
        }
        printf("\n%lld\n", prod);
    }

    return 0;
}