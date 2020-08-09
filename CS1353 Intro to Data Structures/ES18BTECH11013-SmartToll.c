/* The data structure I used to store the vehicle numbers  is 'array'. I used an array because it can be sorted easily making it easy for the data 
   to be accessed. I have used the insertion sort algorithm to sort the vehicle numbers. */


#include <stdio.h>
#define max_size 100

int Vehicle_Id[max_size];  //global array to store the vehicle numbers.
int count;                // count variable to keep a track of number of vehicles passed
 
void storeNextVehicleID(int value)  
{
  
     int j = count-2 ;

     if (count == 1)
      Vehicle_Id[0] = value ;
     else
     { 
        //Inserting the elements using Insertion sort, resulting in a sorted array at each stage.
        while((j >= 0) && (Vehicle_Id[j] > value))
       {
         Vehicle_Id[j+1] = Vehicle_Id[j];        // Move elements of arr[0...count-1], if they are greater than value, to one position ahead of their current place */
         j--;
       }
        Vehicle_Id[j+1]=value;                   // Finally insert the 'value' element into its correct position.
      }
        
      printf("Entries : ");
      for (int i = 0; i < count; ++i)
      {
        printf("%d ", Vehicle_Id[i]);
      }
        printf("\n \n");       

}


int main () 
{  
   int Id; // 'Id' variable to store the vehicle number
     
   for (count = 1; (count <= max_size) ; ++count)
   {
     printf("Enter your vehicle number (lying in between 1 and 10,000)\n");
     scanf("%d", &Id) ;
     if (Id < 0)
       break;

     storeNextVehicleID(Id) ;
   }
   
   return 0;
}