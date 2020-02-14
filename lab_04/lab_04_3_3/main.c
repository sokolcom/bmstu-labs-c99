// Задача 4.03

#include <stdio.h>
#include <math.h>


#define N_MAX 10
#define TOTAL 20

#define ZERO 0
#define ONE 1
#define TWO 2
#define TEN 10

#define SUCCESS 0
#define SIZE_ERROR 1
#define INPUT_ERROR 2
#define NONE_ERROR 3



int input_array(int *const array, const int n)
{
    int check;
    int count = ZERO;

    for (int i = ZERO; i < (n * TWO); i += TWO)
    {
        check = scanf("%d", &array[i]);
        count += check;
    }

    if (count == n)
        return SUCCESS;
    else
        return INPUT_ERROR;
}



void print_array(const int *const array, const int n)
{
    int i = ZERO;

    while (i < (n * TWO))
    {
        printf("%d\n", array[i]);
        if (array[i] > ZERO)
            printf("%d\n", array[i + ONE]);
        i += TWO;
    }
}



int inverse_number(int num)
{
    int mult = ONE;
    int length = ZERO;
    int numbers[N_MAX];
    int inverse = ZERO;

    while (num > ZERO)
    {
        numbers[length] = num % TEN;
        length++;
        num = num / TEN;
    }

    for (int i = (length - ONE); i >= ZERO; i--)
    {
        inverse += (numbers[i] * mult);
        mult *= TEN;
    }

    return inverse;
}



int add_positive(int *const array, const int n)
{
    int amount = ZERO;

    for (int i = ZERO; i < (n * TWO); i += TWO)
        if (array[i] > ZERO)
        {
            array[i + ONE] = inverse_number(array[i]);
            amount++;
        }

    return amount;
}



int main()
{
    int n;
    int check;

    printf("Enter amount of elements (less than ten):\n");
    check = scanf("%d", &n);
    if ((check == ONE) && (n > ZERO) && (n <= N_MAX))
    {
        int array[TOTAL];

        printf("Enter elements of array:\n");
        int code = input_array(array, n);

        if (code == SUCCESS)
        {
            int amount = add_positive(array, n);

            if (amount > ZERO)
            {
                printf("Added inverse positive numbers:\n");
                print_array(array, n);
                return SUCCESS;
            }
            else
            {
                printf("No positive numbers found!");
                return NONE_ERROR;
            }
        }
        else
        {
            printf("Invalid input!");
            return INPUT_ERROR;
        }
    }
    else
    {
        printf("Invalid amount!");
        return SIZE_ERROR;
    }
}
