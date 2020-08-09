#include <stdio.h>

int main () 
{  
    int size; int key_index;
    int found = 0;
    printf("Enter the size of array\n");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array in ascending order:\n");
    for (int i = 0; i < size; ++i)
    scanf("%d", &arr[i]);
    int key;
    printf("Enter the element you want to search\n");
    scanf("%d", &key);
   int mid;
   int low = 0; 
   int high = size-1;
   while(low <= high)
   {
   	 mid = (low + high)/2;
   	 if (arr[mid]==key)
     {
       found = 1;
       key_index = mid;
       break;
     }
     else if(arr[mid] > key)
      high = mid-1;
    else
      low = mid +1;
   }
 
  if (found==1)
  printf("The key element has been found at index %d\n", key_index);
  else
  printf("The key element has not been found\n");
   return(0);
}