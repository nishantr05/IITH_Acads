#include <stdio.h>

int prime_sum(long long int N) //'prime_sum' function with long long int argument 'N' and int return type.
{
    static int sum ;    //static variable 'sum', which stores the value of the sum of prime digits present in 'N'.
    if (N > 0)         //Base condition.When it becomes false we exit out of the recursion.
    {   
       int d = N%10 ;                               //To store the value of the unit's digit of 'N'
       if ((d == 2)||(d == 3)||(d == 5)||(d == 7))  //checking if 'd' equals 2,3,5 or 7; the only prime numbers between 0 and 9.
         sum += d  ;
       prime_sum(N/10) ;                            //Recursively call 'prime_sum', by reducing the length of the number by one.
    }
    return sum ;       //We return the 'sum' value.
}

int main()
{
    int len ;       //len variable to calculate and store number of digits in 'N'
    long long int N, temp ;
    while (1)       //while loop which keeps iterating till break statement is encountered
    {
        scanf("%lld", &N) ;
        temp = N ;  // We store value of N in temp.
        len = 0 ;
        //Below while loop to calculate number of digits in 'N', i.e 'len'.
        while(temp > 0)
        {
           len++;
           temp /= 10 ;
        }
        if ((len == 10)&&(N >= 0))  //If the entered value is valid, we break out of the loop.
            break ;

        printf("INCORRECT INPUT!! Please Enter again...\n"); //Error message for invalid input.
    }
    printf("The sum of prime digits = %d\n", prime_sum(N));  //Printing 'prime_sum(N)', which calculates sum of prime digits in 'N'.

    return 0;
}