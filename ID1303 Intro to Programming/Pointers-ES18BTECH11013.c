#include <stdio.h>
#define MAX 1000

//'str_reverse' function to print the reverse of a string.
void str_reverse(char* ptr, int len) 
{
	while(len > 0) //Iterate 'len' (length of string) many times.
	{
		printf("%c", *(ptr+len-1)); //printing the characters from the end.
		len-- ;
	}
	printf("\n");
} 
int main()
{
	int str_len = 0 ;
	char str[MAX] ;     // string 'str' of length 'MAX'(=1000) declared.
	char* temp ;        //char* pointer 'temp', used while calculating string length

	while(1)  //while loop whose condition check always evaluates to true, breaks out only when valid input is entered.
	{
		printf("Enter the string to reverse : ");
		fgets(str, MAX, stdin) ;  //'fgets' function to read string from user.
		temp = str ;              //'temp' is made to point to first element of 'str'
		str_len = 0 ;             
		//Below while loop to calculate string length
		while (*temp != '\n')   //iterate till newline character character is encountered, indicating end of string.
		{
		  str_len ++ ;
		  temp++ ;
		}
		if (str_len == 0 || str_len > 10)           //Invalid input, when string in NULL or string length is greater than 10.
			printf("Invalid Input. Enter again!!\n");  //Error message is printed
		else
			break ;	   //Incase of valid input we break out.
	}
	str_reverse(str, str_len) ; //calling 'str_reverse' function; passing string 'str' and string length 'str_len'.
	return 0;
}