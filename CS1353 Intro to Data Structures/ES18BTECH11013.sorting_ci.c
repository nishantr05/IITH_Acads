#include<stdio.h>
#define RANGE 20

int main()

    {
        int size, input;
        int is_duplicate = 0;

        printf("Enter the size of an array\n");  // Inputing the size of array from user
        scanf("%d", &size);                 
        int A[size];
        int B[RANGE+1] = {0};                         // Array B is declared with size "RANGE+1".
        int C[size];

        printf("Enter the array elements\n");  
        int i = 0;                  
        for ( i = 0; i < size; i++) 
        {
        	scanf("%d", &input);
            if ((input > RANGE)||(input < 0))    // Exit input stream if element lies outside given range.
        	  break;

        	//Check if any value is inputed twice and exit if so.
        	for (int j = 0; j < i; ++j)
        	{
        		if (input == A[j])
        		{
        			is_duplicate = 1;
        			break;
        		}	
        	}
        	if (is_duplicate)
        	break;

            A[i] = input;
            B[input]++ ;
            
        }

        if (i < size) // If number of input elements is less than size, then rewrite size to appropriate value.
          size = i;

        //FILLING ARRAY 'B', each position 'j' contaiing number of elements of 'A' less than or equal to j.
        //EFFECIENT
         printf("%d, ", B[0]); 
        for (int i = 1; i <= RANGE ; ++i)
        {
        	B[i] = B[i] + B[i-1];
        	printf("%d, ", B[i]);                                
            
        }
        printf("\n");
        /*INEFFECIENT: for (int k = 0; k <= RANGE ; ++k)
        {
        	int count = 0;

        	for (int l = 0; l < size; ++l)
        	{
        		if (A[l] <= k)
        			count++;
        	}

        	B[k] = count;
        } */

        // FILLING ARRAY C
        int m = 0;
        if (B[0] == 1)
        		{  
        			C[m] = 0;
        			m++ ;
        		}

        	for (int n = 1; n <= RANGE; ++n)
        	{  

        		if (B[n] > B[n-1]) // If the condition satisfies then element 'n' is in Array 'A'
        	   {
        	   	 C[m] = n;         // Ensures 'C' is sorted as n is traversed in ascending order.
        	   	 m++;
        	   }   
        	}
        
        //Printing sorted array 'C'
        printf("Sorted array is:\n");
        for (int o = 0; o < size; o++)
        printf("%d, ", C[o]);                                
        printf("\n");

    return 0;    
}