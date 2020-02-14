// Задача 1.03

#include <stdio.h>

#define ZERO 0
#define ONE 1
#define NO_ERROR 0

int main()
{
    float r1, r2, r3;
    
    puts("Enter resistances (3 of them):");
    scanf("%f%f%f", &r1, &r2, &r3);
    if (r1 <= ZERO || r2 <= ZERO || r3 <= ZERO)
        printf("Invalid input (check values)!");
    else
        printf("%.5f", ONE / ((ONE / r1) + (ONE / r2) + (ONE / r3)));
    return NO_ERROR;
}
