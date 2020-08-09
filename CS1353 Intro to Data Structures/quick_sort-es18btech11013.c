#include<stdio.h>

void swap(int *ptra, int *ptrb)
{
 int t;
  t = *ptra;
  *ptra = *ptrb;
  *ptrb = t;
} 

int partition(int arr[], int start, int end)
{
   int pivot = arr[end];                   /* Here we take the last element of the array as the 'pivot' */
   int pivotindex = start;                 /*Initialize pivot index to that starting index of the array to be partioned*/
   
   for (int i = start; i < end; ++i)    
   	 {
   	    if (arr[i] <= pivot)
   	   {
   	  	swap(&arr[i], &arr[pivotindex]);   /* Ensures at any stage, all elements to the left of arr[pindex] will be lesser than pivot */
   	  	pivotindex++;
   	   }
   }
    swap(&arr[pivotindex], &arr[end]);     /* Finally place the pivot element at the pivotindex of the array */
    return pivotindex;
}

void quick_sort(int arr[], int start, int end)
{
   if (start < end)                        /* Base condition to exit out of the recursive function */ 
   {
   	 int pindex = partition(arr, start, end);      /* Keeping track of the pivot index using 'pindex' */
   	 quick_sort(arr, start, pindex-1);             /* Seperately sort the array elements to the left of pivot */
   	 quick_sort(arr, pindex+1, end);               /* Seperately sort the array elements to the right of pivot */
   } 

}  


int main()

    {
        int size;

        printf("Enter the size of an array\n");     // Reading the size of the array
        scanf("%d", &size);
        int array[size];

        printf("Enter the array elements\n");       // Entering the elements of the array
        for (int i = 0; i < size; i++) 
        scanf("%d", &array[i]);

        quick_sort(array, 0, size-1);
 
        printf("Sorted array is:\n");               // Printing the sorted array
        for (int k = 0; k < size; ++k)
        printf("%d, ", array[k]);
        printf("\n");

     return 0;  
}
      
      
