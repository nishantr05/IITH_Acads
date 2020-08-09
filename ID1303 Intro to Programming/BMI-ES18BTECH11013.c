#include <stdio.h>

int main(void)
{
    float weight, height, BMI;
    scanf("%f%f", &weight, &height) ; // To read the value of height and weight from user
    BMI = weight/(height*height) ;
    printf("%0.4f\n", BMI); //prints the BMI correct to 4 decimal places.
    if (BMI <= 18.5)
       printf("Underweight\n"); //This condition is executed if BMI is less than 18.5

    else if (BMI <= 25)   
       printf("Normal\n"); //This condition is executed if BMI is between 18.5 and 25

    else if (BMI <= 30)
       printf("Overweight\n"); //This condition is executed if BMI is between 25 and 30

    else
       printf("Obese\n"); //This condition is executed if BMI is greater than  30

    return 0;
}
