#include<stdio.h>

//function to add x and y
int add(int x, int y)
{
    return x+y ;
}
//function to compute x-y
int subtract(int x, int y)
{
    return x-y ;
}
// function to calculate the product x*y 
long long int multiply(int  x, int y)
{
    long int i, prod = 0 ;
    for (i = 0; i < y ; ++i)   //loop is run 'y' times. We are adding the number 'x','y' many times to obtain x*y
        prod += x ;           //'prod' value is updated by adding x to it, i.e prod = prod + x
    
    return prod ;
}
//'divide' function to compute the Floor value of x/y.
int divide(int x, int y)
{
    int quotient = 0 ; //quotient of the division 'x/y' is nothing but the floor value of x/y.
    // while loop to calculate quotient of x/y.Terminates when x becomes less than y.
    while(x >= y)
    {
        x = x-y ;      //repeatedly subtract y from x at every iteration
        quotient++;    // counts the number of times y is subtracted from x.
    }
    return quotient ;
}
// modulo func to compute 'x%y', i.e the remainder of the division x/y.
int modulo(int x, int y)
{
    //from the reamainder theorem, remainder of 'x/y' is the dividend - divisor*(quotient of 'x/y')
    return x-multiply(y, divide(x,y)) ;  
}
//square function calculates x*x
long long int square(int x)
{
    return multiply(x, x); //square of 'x' is nothing but x*x 
}
//'sq_rt' func calculates the square root of 'x'
int sq_rt(int x)
{
    if ((x == 0)||(x == 1)) //trivial case of x = 0 or 1, where sqrt of 'x' is x itself 
        return x ;

    int i = 1 ;
    //this loop iterates for all i values btw 1 and sqrt(x).
    //once i exceeds sqrt(x), condition check fails, loop is terminated
    while(square(i) <= x) //while(i*i <= x)
        i++;              //increment i by 1, till i reaches sqrt(x)

    return i-1 ;  //on exiting from the while loop, value of 'i*i' is greater than 'x', thus the correct floor value of sqrt(x) is 'i-1'
}
//'log_2' function, which gives the CEIL value of logarithm of 'x', base 2.
int log_2(int x)
{
    int ans = 0 ;
    //while loop to calculate number of times 'x' is divided by 2, till it becomes less than or equal to 1.
    //In each iteration we reduce 'x' by half, till x <= 1. The numebr of iterations correctly gives the value of 'log2(x)'.
    while(x > 1)
    {
        //Below operations update x = ceil(x/2)
        if (modulo(x,2) != 0)
            x= divide(x,2)+1 ;  //since x is odd, ceil(x/2) = x/2 + 1 .
        else
            x = divide(x,2) ;   //since x is even, ceil(x/2) = x/2 . 
        ans ++;
    }
    return ans ; //'ans' contains the value of ceil(log2(x)).
}
//'display' function with no return type and no arguments
void display()
{
    //2 print statements to output the 'MENU' for the user.
    printf("\nMENU:\nEnter the number corresponding to the operation you want to perform.\n1: Add\n2: Multiply\n3: Divide\n");
    printf("4: Subtract\n5: Modulus\n6: Square\n7: Square Root\n8: Log (Base : 2)\n9: Exit\n");
}

int main()
{
    int op ; //
    int num1, num2 ;
    display() ;
    printf("Your choice: ");
    scanf("%d", &op);
    //while loop keeps runing untill user enters 9. On entering 9, the loop terminates and the program ends.
    while(op != 9) 
    {
        if ((op >= 1)&&(op<=5)) //For operations 1,2,3,4 and 5 two input values are required.
        {
            printf("Enter the first number: ");
            scanf("%d", &num1);
            printf("Enter the second number: ");
            scanf("%d", &num2);
        }
        else if((op > 5)&&(op<=8)) //For operations 6,7 and 8 only one input is required.
        {
            printf("Enter a number: ");
            scanf("%d", &num1);
        }
        switch(op)
        {
            case 1: //Addition of num1 and num2
                printf("The result is: %d\n", add(num1, num2));
                break ;

            case 2: //Multiplication of num1 and num2
                printf("The result is: %lld\n", multiply(num1, num2));
                break ;

            case 3: //Division of num1 by num2
                if (num2 == 0)
                    printf("2nd number must be positive\n");  //Division by zero is not valid.
                else
                    printf("The result is: %d\n", divide(num1, num2));
                break ;

            case 4: //Subtraction of num2 from num1, i.e num1-num2
                printf("The result is: %d\n", subtract(num1, num2));
                break ;

            case 5: //Remainder of the division 'num1/num2'
                if (num2 == 0)
                    printf("2nd number must be positive.\n"); //The divisor should be non-zero
                else
                    printf("The result is: %d\n", modulo(num1, num2));
                break ;

            case 6: //Square of num1
                printf("The result is: %lld\n", square(num1));
                break ;

            case 7: //Square root of num1 
                printf("The result is: %d\n", sq_rt(num1));
                break ;

            case 8: //Logarithm of num1 to the base 2
                if (num1 == 0)
                    printf("The number entered must be positive.\n"); //'log' function is valid for positive values only,
                else
                    printf("The result is: %d\n", log_2(num1));
                break ;

            default :
                printf("Please enter a VALID number from the MENU, corresponding to the operation you want to perform.\n");  
        }

        display() ;
        printf("Your choice: ");
        scanf("%d", &op);
    }
    return 0;
}
