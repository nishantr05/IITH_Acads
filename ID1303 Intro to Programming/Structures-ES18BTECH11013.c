#include <stdio.h>
#include<assert.h>

struct engine
{
    char S_no[5], material[10] ;  //Strings declared for serial number ('S_no') and material used.
    int d, m, y ;  // three integers 'd'(day), 'm'(month) and 'y'(year) for storing the date. 
    int weight ;   // Weight of engine part.
};
typedef struct engine engine ; //word 'engine' defined as an alias to 'struct engine'.

//Weight function, to check the entries with weight greater than 5kgs
void weight_5(engine* ptr, int size)
{
    assert(ptr != NULL) ; // Assert statement ensures the pointer passed in not 'NULL'.If vioalted we get a runtime error.

    int flag = 0 ; //To check if there exists parts whose weight is more than 5 Kgs.
    printf("\nSerial numbers where weight is more than 5kg : ") ;
    for (int i = 0; i < size; ++i)
    {
        if ((ptr+i)-> weight > 5)
        {
          printf("%s  ", (ptr+i)-> S_no) ;
          flag = 1;      //setting flag to one, indicicating there are parts with weight more than 5Kgs.
        }
    }
    if(flag == 0)   //since flag is zero no such entries are present.
        printf(" No entries found!!");

    printf("\n");
}

//Function to check if serial number lies between AA2 and BB7.
void serial_num(engine* ptr, int size)
{
    assert(ptr != NULL) ; // Assert statement ensures the pointer passed in not 'NULL'.If vioalted we get a runtime error.

    int flag = 0 ;       //To check if there exists parts whose serial number lies between AA2 and BB7
    char* temp ;  //'temp' pointer to access the 'S-no' string.
    printf("\nYear of manufacture of engine parts having serial number between AA2 and BB7 : ") ;
    for (int i = 0; i < size; ++i)
    {
        temp = (ptr+i)-> S_no ;
        // 'temp[i]' is nothing but '*(temp+i)'
        // The below if condition checks if the serial numbers lie in between 'AA2' and 'BB7'
        if ((temp[0] == 'A' && temp[1] == 'A' && temp[2] >= '2' && temp[2] <= '9')||(temp[0] == 'B' && temp[1] == 'B' && temp[2] >= '0' && temp[2] <= '7'))
        {
          printf("%d  ", (ptr+i)-> y) ;
          flag = 1;      //setting flag to one, indicicating there are parts with the required serial number.
        }
    }
    if(flag == 0)  //since flag is zero no such entries are present.
        printf(" No entries found!!");

    printf("\n");
}

//Function to check and print details of the parts manufactured within 3 years from 15th Nov,2019 .
void years(engine* ptr, int size)
{
    assert(ptr != NULL) ; // Assert statement ensures the pointer passed in not 'NULL'.If vioalted we get a runtime error.

    int flag = 0 ;       //'flag' varriable,to check for parts within 3 years of manufacture from 15th Nov 2019.y
    int d , m, y   ;
    printf("\nDetails of engine parts where year of manufacture is within 3 years of 15th Nov 2019 : ") ;
    for (int i = 0; i < size; ++i)
    {
        // setting 'd', 'm' and 'y' to the respective manunfacture date of the engine part.
        d = (ptr+i)-> d ;
        m = (ptr+i)-> m ;
        y = (ptr+i)-> y ;

        // if condition to check if date of manufacture is after 15th November 2016.
        if ((y > 2016)||(y == 2016 && m > 11)||(y == 2016 && m == 11 && d > 15)) 
        {
          //printing the details of the engine part :
          printf("\nSerial number: %s\n", (ptr+i)-> S_no) ;
          printf("Date of manufacture: ");
          d < 10 ? printf("0%d-", d) : printf("%d-", d) ;         //if 'd'(day) is less than 10, then we print an additional zero.
          m < 10 ? printf("0%d-%d\n", m, y) : printf("%d-%d\n", m, y) ; //if 'm'(month) is less than 10, then we print an additional zero.
          printf("Material: %s\n", (ptr+i)-> material );
          printf("Weight: %d\n", (ptr+i)-> weight );
          flag = 1;      //setting flag to one, indicicating there are parts within 3 years of manufacture from 15th Nov 2019.
        }
    }
    if(flag == 0)  //since flag is zero no such entries are present.
        printf(" No entries found!!");

    printf("\n");
}

int main()
{
    int i, size ;      //'size' stores the number of parts.
    engine parts[5] ;  // Creating an array called 'parts' of type 'engine'. Maximum number of parts is 5.
    printf("Enter the number of parts: ");
    scanf("%d", &size) ;
    for (i = 0; i < size; ++i)
    {
        //reading the required values from the user.
        printf("Enter serial number of part %d : ", i+1) ;
        scanf("%s", parts[i].S_no) ;
        printf("Enter date of manufacture of part %d : ", i+1) ;
        scanf("%d-%d-%d", &parts[i].d, &parts[i].m, &parts[i].y) ;
        printf("Enter material of part %d : ", i+1);
        scanf("%s", parts[i].material) ;
        printf("Enter weight of part %d : ", i+1);
        //while loop, which keeps asking user for weight, till valid entry is made.
        while(1)
        {   
            scanf("%d", &parts[i].weight) ;
            if(parts[i].weight >= 1 && parts[i].weight <= 10)
                break ;
            printf("\nPlease enter weight between 1 and 10 kgs : ") ;
        }
        printf("\n");

    }
    //Calling the respective functions for the required computations.
    //'parts' is the array of structures, which is passed in each function call.
    weight_5(parts, size) ;
    serial_num(parts, size) ;
    years(parts, size) ;    
    return 0;
}