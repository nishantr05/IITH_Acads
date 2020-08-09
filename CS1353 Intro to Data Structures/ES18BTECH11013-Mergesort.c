#include <stdio.h>

/*Function 'Merge', with parameters as the left and right arrays to be merged into array 'A' */

 void Merge(int left[], int lengthL, int right[], int lengthR, int A[])
 {
 	 int i=0;    // Initial index of subarray 'left' 
 	 int j=0;    // Initial index of subarray 'right' 
   int k=0;    // Initial index of merged array 'A' 
 	
    while((i<lengthL)&&(j<lengthR))
    {
    	if (left[i]<=right[j])
    	{
    		A[k]=left[i];
    		i++;
    	}
    	else
    	{
    		A[k]=right[j];
    		j++;
    	}
    	k++;
    }

    while(i<lengthL)      /* Copy the remaining elements of subarray left[], if there are any */   
    {
	    A[k]=left[i];
	    i++; k++;
    }

    while(j<lengthR)      /* Copy the remaining elements of subarray right[], if there are any */
    {
	    A[k]=right[j];
	    j++; k++;
    }
}

void Merge_sort(int A[], int n)
{

   if (n<2)                          // base condition to exit out of the recursive function
   return ;

   int mid = n/2 ;
   int left[mid], right[n-mid] ;     // split the given array into two parts and sort seperately
   int i;

   for (i = 0; i < mid; ++i)
    left[i] = A[i];

   for (i = mid; i < n; ++i)
     right[i-mid] = A[i];

   Merge_sort(left, mid);               //sort the left part of the array
   Merge_sort(right, n-mid);            // sort the right part of array
   Merge(left, mid, right, n-mid, A);   // merge left and right sorted parts
}

int main()

    {  
        int size ;
        printf("Enter the size of an array\n");                  // Inputing the size of array from user
        scanf("%d", &size);

        int array[size];
        printf("Enter the array elements\n");                    // Entering the elements of the array
        for (int i = 0; i < size; i++) 
        scanf("%d", &array[i]);

        Merge_sort(array, size);

        printf("Sorted array is:\n");
        for (int k = 0; k < size; ++k)
        printf("%d, ", array[k]);                                // Printing the sorted array
        printf("\n");

        return 0;    
     }
