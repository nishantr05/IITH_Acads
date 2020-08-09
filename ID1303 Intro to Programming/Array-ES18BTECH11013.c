#include<stdio.h>

//Arrays 'U' and 'I' are declared in global scope.
int U[20] ; // array 'U' is the union of the input arrays. It can have atmost 20 elements.
int I[10] ; // array 'I' is the Intersection of the input arrays. It can have atmost 10 elements.

void input(int A[])
{
    int val, is_present ;       //'val' stores the user input. 'is_present' serves as a boolean variable.
    for (int i = 0; i < 10; ++i)
    {
      scanf("%d", &val);
      is_present = 0 ;         //We set 'is_present' to equal 0.
      for (int j = 0; j < i; ++j)
      {
        if (A[j] == val)      //If the value entered is already present
        {
            printf("The value %d has already been entered, please enter a different value\n", val); 
            is_present = 1;   //Set 'is_present' = 1, since the element is already present.
            i-- ;             //decrement counter valriable 'i', since the input 'val' is not stored.
            break ;
        }
      }
      if (!is_present)  // if 'val' is NOT present, add it to array 'A'.
        A[i] = val ;
    }
}
int Union(int A1[], int A2[])
{
    
    int i, is_present ; //'is_present' takes values 0,1 and serves as a flag variable.
    int len = 10 ;      // 'len' stores number of elemets in array 'U'. 
    for (i = 0; i < 10; ++i)
       U[i] = A1[i] ;        //since 'U' is the union array, it will contain atleast all elements in A1.
  
    //The below nested for loops add elements of A2 not already present in 'U', to U 
    for (i = 0; i < 10; ++i)
    {
        is_present = 0 ;     //'is_present' is set to 0
        for (int j = 0; j < 10; ++j)
        {
            if (A2[i] == A1[j]) //We check if element in 'A2' is already present in 'A1'
            {
                is_present = 1 ; //'is_present' is made 1
                break;
            }
        }
        if (!is_present) //if element of A2 is not already present in 'U', then add it to 'U'
        {   
            U[len] = A2[i] ;
            len++ ;          //increment 'len', since an element is being added to 'U'
        }
    }
    //Printing the required output
    printf("\nUnion: ");
    for (i = 0; i < len; ++i)
        printf("%d ", U[i]);

    return len ;
}
int Intersection(int A1[], int A2[])
{
    
    int i, len = 0 ;  // 'len' stores number of elemets in array 'I'. 
    //The below nested for loops check for common elements in A1 and A2, to add to I
    for (i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (A1[i] == A2[j]) //We check if element in 'A1' is present in 'A2'
            {
                I[len] = A1[i]  ; 
                len++ ;
                break;
            }
        }
    }
    if (len == 0)
        printf("\n\nIntersection: NULL"); //if 'len' is 0. then we print intersection as 'NULL'
    else
    {
        printf("\n\nIntersection: ");
        for (i = 0; i < len; ++i)
            printf("%d ", I[i]);
    }
    return len ;
}
void computation (int A[], int len) //Here array 'A' is either the union array 'U' or intersection array 'I'.
{
    int i, max1, max2 ;
    if (len == 0)//This case occurs when the intersection array has no elements
    {
        printf("First Largest element = NULL\nSecond Largest element = NULL\n") ;
        return  ; //Exit control from the function  
    }
    else if (len == 1)//This case occurs when the intersection array has 1 element
    {
        printf("First Largest element = %d\nSecond Largest element = NULL\n", I[0]) ;
        return  ; //Exit control from the function 
    }
    //Below statements are executed when 2 or more elements are present in 'A'
    max1 = A[0] ;  //Initialize max1 to the first element 
    for (i = 0; i < len; ++i)
    {
        if (max1 < A[i])  //if max1 is less than A[i], then max1 is made equal to A[i]
            max1 = A[i] ;
    }
    max2 = A[0] == max1 ? A[1] : A[0] ;  //This statement sets max2 to an element in 'A', OTHER than max1.
    for (i = 0; i < len; ++i)
    {
        if (A[i] == max1)  //if we encounter max2 while traversing 'A', we simply ignore it and continue
            continue ;
        if (max2 < A[i])  //If max2 is less than A[i] (other than max1), then max2 = A[i].
            max2 = A[i] ;
    }
    printf("First Largest element = %d\nSecond Largest element = %d\n", max1, max2) ; //Printing the required result.
}

int main()
{
    int Arr1[10], Arr2[10] ;  // arrays Arr1, Arr2 are the input arrays
    int i, len_U, len_I ;   //lengths of Union and Intersection arrays are len_U nad len_I
    printf("Enter values in Array1:\n");
    input(Arr1) ;           //calling 'input' function to read values of array1
    printf("Enter values in Array2:\n");
    input(Arr2) ;           //calling 'input' function to read values of array2
    len_U = Union(Arr1, Arr2) ;        //Calling 'Union' function which finds and prints union of 'Arr1' and 'Arr2'
    len_I = Intersection(Arr1, Arr2) ; //Calling 'Intersection' function which finds and prints intersection of 'Arr1' and 'Arr2'
    printf("\n\nUnion computation:\n");
    computation(U, len_U) ;           //Calculating and printing Union computation.
    printf("\nIntersection computation:\n");
    computation(I, len_I) ;           //Calculating and printing Intersection computation.
    return 0;
}
