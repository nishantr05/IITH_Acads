//program to implement linear search using recursion.

#include <stdio.h>

int recc_linear_Search(int arr[], int left, int right, int key) 
               
{ 
    if (right < left) //the entire array has been serached, but key is not found (base case).
        return -1; 
    if (arr[left] == key) //check if the left most element in the 'unsearched' array is the key.
        return left; 
    if (arr[right] == key) //check if the right most element in the 'unsearched' array is the key.
        return right; 

    return recc_linear_Search(arr, left+1, right-1, key); //make a recursive call to search for 'key' between indices (left+1) and (right-1). 
                         
} 

int main () 
{  
    int size; int key_index;  //key_index initialized to display position of key element
    
    printf("Enter the size of array\n");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; ++i)
    scanf("%d", &arr[i]);
    int key;
    printf("Enter the element you want to search\n");
    scanf("%d", &key);
    // first call to the recursive search function
    key_index = recc_linear_Search(arr, 0, size-1, key);
    if (key_index != -1) //if return value is not -1, key has been found
    printf("Element has been found at index %d\n", key_index );
    else
    printf("Element has not been found\n");

  return 0;

}

