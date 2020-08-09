#include<stdio.h>

//Function 'fact', which computes the factorial of an integer n.
//The return type is 'long long int' so as to avoid overflow, if the computed factorial value is very large.
long long int fact(int n)       
{
    long long int prod = 1 ;  //'prod' variable stores the value of n! .
    for (int i = 1; i <= n; ++i)
        prod = prod*i ;      //At each iteration 'prod' is updated by multiplying with 'i'. 

    return prod ;
}
//Function 'nCr', which takes as arguments integers n and r, and returns the value of ' n!/(r!(n-r)!) '.
int nCr (int n, int r)
{
    return fact(n)/(fact(r)*fact(n-r)) ; //Call to function 'fact' to calculate n!, r! and (n-r)! values.
}

int main()
{
    int x, y ;
    scanf("%d %d", &x, &y) ;
    if ((x < y) || (x < 0 || y < 0) || (x > 15 || y > 15)) // if x is less than y OR if x,y < 0 OR if x,y > 15, then input is considered invald.
        printf("Incorrect Input!!\n");
    else
        printf("%d\n", nCr(x, y));  //We calucalte xCy, for valid x and y, by calling the function 'nCr(x, y)'.
    return 0;
}