#include <stdio.h>

int main () 
{  
    int size; int key_index;
    int found = 0;
    printf("Enter the size of array\n");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; ++i)
    scanf("%d", &arr[i]);
    int key;
    printf("Enter the element you want to search\n");
    scanf("%d", &key);

    // search starts here.
    for (int j = 0; j < size; ++j)
    {
      if (arr[j]==key)
      {
        key_index = j;
        found = 1;
        break;
      }
    }
    if (found==1)
      printf("The key element has been found at index %d\n", key_index);
    else
      printf("The key element was not found\n");

   return(0);
}