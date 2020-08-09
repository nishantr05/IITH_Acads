#include<stdio.h>

void swap(int *ptra, int *ptrb)
{
 int t;
  t = *ptra;
  *ptra = *ptrb;
  *ptrb = t;
} 

void selection_sort(int A[], int n)
{
	  if (n > 1)
  {
    int min = A[0];
    for (int i = 0; i < n; ++i)
    {
   	   if (A[i] < min)
   	 {
   	 	min = A[i];
   	 	swap(&A[0], &A[i]);
   	 }
   }
   selection_sort(A+1, n-1);
 }

}

    int main()

    {
        int array[30], size;

        printf("Enter the size of an array\n");
        scanf("%d", &size);

        printf("Enter the array elements\n");
        for (int i = 0; i < size; i++) 
         scanf("%d", &array[i]);

        selection_sort(array, size);

        printf("Sorted array is:\n");
        for (int k = 0; k < size; ++k)
        printf("%d, ", array[k]);
       printf("\n");

     return 0;  
}
      