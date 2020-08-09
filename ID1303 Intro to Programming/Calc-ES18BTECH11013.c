#include <stdio.h>

int main()
{
    int A, B ;         // declaring A, B as integers
    char C ;           // C is defined as a character
    scanf("%c", &C);             
    scanf("%d %d", &A, &B);  
    //if-else block to identify the operation corresponding to character 'C' :
    if (C == '+')
        printf("Addition\n%d \n", A+B);
    else if (C == '-')
        printf("Subtraction\n%d \n", A-B);
    else if (C == '*')
        printf("Multiplication\n%lld \n", (long long)A*B);  //type-casting 'A' to type 'long long int' to prevet overflow.Using '%lld' format specifier to print 'long long int' type varible.
    else if (C == '/')
    {
        if(B == 0)
            printf("Division\nError\n");             // division by zero is not allowed
        else
            printf("Division\n%f \n", (double)A/B);  // type-casting 'A' to 'double' type so as to get the correct decimal value.
    }
    else
        printf("Error\n");      //Final case, which prints 'Error', incase an invalid character is entered.                
    
    return 0;
}
