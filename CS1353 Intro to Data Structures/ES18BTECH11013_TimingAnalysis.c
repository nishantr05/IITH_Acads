#include <stdio.h>
#include <stdlib.h>
#include<time.h>
void linear_search(int arr[], int size, int key)
 {
 	int key_index;                 //'key_index' to store where the key is stored

 	int found = 0;                 // initializing a flag variable 'found' to see if key is present or not
 	clock_t start, end;             
 	start = clock();               // The clock timer starts here
   for (int j = 0; j < size; ++j)
    {
      if (arr[j]==key)
      {
        key_index = j; 
        found = 1;  
      }
    }
    end = clock();                // Clock timer ends here
    printf("The array size is %d and the Time taken is %lf \n", size, ((double)(end-start))/CLOCKS_PER_SEC );
 }

int main () 
{  
    int MAX = 100000;
    int arr[MAX];
    
    for (int i = 10; i < MAX; i = i+10000)
    {
    	int n = i;                         // initializing the size of the array to different values
    	for (int i = 0; i < n; ++i)
         {
         	arr[i] = (rand()%100000);       // storing random elements in the array which are less than 10^6
         }

        int key = (rand()%100000);          // setting the value to be searched in the array as a random value 
        linear_search(arr, n, key);         // calling linear search with a given n
    }

   return 0;
}