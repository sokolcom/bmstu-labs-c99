// Задача 2, вариант 2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ONE_VAR 1
#define TEN 10
#define ZERO 0
#define TWO 2

#define SUCCESS 0
#define INPUT_ERROR 1
#define VALUE_ERROR 2
#define FIND_ERROR 3


bool check_prime(int num)
{
    if (num < TWO)
        return false;
    for (int i = TWO; i < num; i++)
        if (num % i == ZERO)
            return false;
    return true;
}

int print_prime_numbers(int n)
{
    int first, last;
    int number;
    int count = ZERO;

    while (n > TEN)
    {
        last = n % TEN;
        first = (n / TEN) % TEN;

        number = first * TEN + last;

        if (check_prime(number))
        {
            printf("%d ", number);
            count++;
        }

        n /= TEN;
    }
    return count;
}

int main()
{
    int n;

    int check = scanf("%d", &n);
    if (check == ONE_VAR)
    {
        n = abs(n);
        if (n > TEN)
        {
            int result = print_prime_numbers(n);
            if (result > ZERO)
                return SUCCESS;
            else
            {
                printf("No prime numbers found!");
                return FIND_ERROR;
            }
        }
        else
        {
            printf("Number is too short!");
            return VALUE_ERROR;
        }
    }
    else
    {
        printf("Invalid input!");
        return INPUT_ERROR;
    }
}
