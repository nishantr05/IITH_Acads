#include <stdio.h>

int main()
{
    int N, curr_balance, X ;
    char op ;       //'op' is initialized as a char value,it stores the character which corresponds to the 'operation' the user performs. 
    scanf("%d", &N);
    // A while loop to make sure the user enters a valid input for 'N'.
    // As long as N < 1 (i.e 'N' is not a positive int), the user is asked to enter a valid value.
    while(N < 1)
    {
        printf("Please enter a valid value for N\n"); 
        scanf("%d", &N) ;
    }
    scanf("%d", &curr_balance) ; //Reading the initial balance from the user.
    // A for loop, which runs from i = 0 to i = N-1, allowing the user to enter N different values of 'op'.
    for (int i = 0; i < N; ++i)
    {
        scanf(" %c", &op) ;
        //A switch-case contruct, based on which operation to perform. 
        switch (op)
        {
            // Case for when user wants to withdraw money 
            case 'w':
                scanf("%d", &X) ;
                printf("WithdrawAmount\n");
                if (X > curr_balance)     //if X is greater than current balance, then the amount cannot be withdrawn
                    printf("Error\n");
                else
                {
                    curr_balance = curr_balance - X ; // 'X' amount is withdrawn
                    printf("Success\n");
                }
                break ;

            // Case for when user wants to add money
            case 'a' :
                scanf("%d", &X) ;
                curr_balance = curr_balance + X ; //'X' amount is credited to the current balance
                printf("AddAmount\nSuccess\n");
                break ;
            
            // This case is for displaying user's net balance
            case 'p' :
                printf("GetBalance\n%d\n", curr_balance);
                break ;
            
            // Default case to print error, when user enters invalid character.
            default :
                printf("Error\n");

        }
    }
    
    return 0;
}
