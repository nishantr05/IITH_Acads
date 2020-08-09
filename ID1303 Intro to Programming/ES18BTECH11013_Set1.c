
/* Roll no : ES18BTECH11013
   Name : Nishant Reddy
   Set : 1
*/

#include <stdio.h>

struct point
{
    int x ;          //x-coordinate of the point
    int y ;          //y-coordinate of the point
    int is_maximal ; //'is_maximal' serves as a flag variable to check whether the point is maximal or not
} ;

int main()
{
    int n ,i, j ; //n - size of array; i,j - counter variables
    printf("Enter the number of points in the set : ");
    scanf("%d", &n);
    struct point Arr[n] ;   //Creating an array of type 'struct point'.

    //Reading the co-ordinates from the user:
    for (i = 0; i < n; ++i)
    {
        printf("Enter the coordinates of the point %d : ", i+1) ;
        scanf("%d%d", &Arr[i].x, &Arr[i].y) ;
        Arr[i].is_maximal = 1;                 //Setting the default flag value to '1'(true).
    }

    //Below nested for loop to check whether there exists a point (Arr[j].x, Arr[j].y) which dominates (Arr[i].x, Arr[i].y)
    //If such a point exists then 'Arr[i].is_maximal' is set to 0 (false).
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (Arr[j].x > Arr[i].x && Arr[j].y > Arr[i].y)
            {
                Arr[i].is_maximal = 0 ;   //flag value 'is_maximal' set to 0, indicating that (Arr[i].x, Arr[i].y) is not a maximal point.
                break ;
            }
        }
    }
    //Printing all the maximal points :
    printf("\nThe maximal points are : ");
    for (i = 0; i < n; ++i)
    {
        if (Arr[i].is_maximal) //Printing the point if 'is_maximal' is equal to 1 (true).
        {
            printf("(%d, %d)    ",Arr[i].x, Arr[i].y);
        }
    }
    printf("\n");

    return 0;
}