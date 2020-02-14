// Задача 2.01

#include <stdio.h>

#define ZERO 0
#define TEN 10
#define VAR 1
#define NO_ERROR 0
#define ERROR 1


long long calc_rank(long long n)
{
    long long rank = 1;	
    
    while (n >= rank * TEN)
        rank *= TEN;
    return rank;
}


int main()
{
    long long n;
    int digit;
    int check;

    printf("Enter integer:\n");
    check = scanf("%lli", &n);

    if ((check != VAR) || (n <= ZERO))
    {
        printf("Invalid input!");
        return ERROR;
    }
    else
    {
        long long mult = calc_rank(n);

        while (mult > ZERO)
        {
            digit = n / mult;
            printf("%d", digit);
            n = n % mult;
            mult /= TEN;
        }

        return NO_ERROR;
    }
}
