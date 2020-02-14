// Задача 1.04

#include <stdio.h>

#define SEC_HOUR 3600
#define SEC_MIN 60
#define NO_ERROR 0


int main()
{
    int hours, minutes, seconds;
    int input;

    printf("Calculate total amount of hours & minutes\n\n");
    printf("Enter total amount of seconds: \n");
    scanf("%d", &input);

    hours = input / SEC_HOUR;
    minutes = (input - SEC_HOUR * hours) / SEC_MIN;
    seconds = input - SEC_HOUR * hours - SEC_MIN * minutes;

    printf("\nResult: %d hours, %d minutes, %d seconds", hours, minutes, seconds);

    return NO_ERROR;
}
