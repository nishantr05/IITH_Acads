    #include <stdio.h>

       void insertion_sort(int arr[], int size)
     {
        int i,j, value;
        for (i = 1; i < size; ++i)
        {
            value=arr[i];
            j=i-1;
            while((j>=0)&&(arr[j]>value))
            {
               arr[j+1]=arr[j];                /* Move elements of arr[0..i-1], if they are greater than value, to one position ahead of their current place */
               j--;
            }
            arr[j+1]=value;                    // Finally insert the ith element (arr[i]) into its correct position.
        }
     }

    void main()

    {
        int size;

        printf("Enter the size of an array\n");            // Reading the size of the array
        scanf("%d", &size);
        int array[size];

        printf("Enter the array elements\n");              // Entering the elements of the array
        for (int i = 0; i < size; i++) 
        scanf("%d", &array[i]);

        insertion_sort(array, size);

       printf("Sorted array is:\n");                       // Printing the sorted array
       for (int k = 0; k < size; ++k)
       printf("%d, ", array[k]);
       printf("\n");
}
      
      

        

 