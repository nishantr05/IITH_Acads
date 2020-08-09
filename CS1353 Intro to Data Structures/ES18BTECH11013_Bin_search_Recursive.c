#include <stdio.h>

int recc_binarySearch(int arr[], int low, int high, int key) 
{ 
   if (high >= low) // base case, to exit the recursion
   { 
        int mid = (low + high)/2; //variable 'mid' to compute the middle postion.
  
        
        if (arr[mid] == key)  
          return mid; // If the element is present at the middle itself, return 'mid' index.
        
        else if (arr[mid] > key) 
          return recc_binarySearch(arr, low, mid-1, key); // If element is smaller than mid,then search in left subarray 
        
        else
        return recc_binarySearch(arr, mid+1, high, key); // Else the element can only be present in right subarray 
   } 
  
   // We reach here when element is not present in array 
   return -1; 
} 
int main () 
{  
    int size; int key_index;
    int found = 0;
    printf("Enter the size of array\n");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array in ascending order:\n");//here a sorted array is entered by the user.
    for (int i = 0; i < size; ++i)
    scanf("%d", &arr[i]);
    int key;
    printf("Enter the element you want to search\n");
    scanf("%d", &key);
    // first call to the recursive search function
    key_index = recc_binarySearch(arr, 0, size-1, key);
    if (key_index != -1) //if return value is not -1, key has been found
    printf("Element has been found at index %d\n", key_index );
    else
    printf("Element has not been found\n");

  return 0;
}