// Задача 4.02

#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#define N_MAX 10

#define ZERO 0
#define ONE 1
#define TEN 10

#define SUCCESS 0
#define SIZE_ERROR 1
#define INPUT_ERROR 2
#define NONE_ERROR 3
#define ALL_ERROR 4



int input_array(int *const array, const int n)
{
    int check;
    int count = ZERO;

    for (int i = ZERO; i < n; i++)
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
    for (int i = ZERO; i < n; i++)
        printf("%d\n", array[i]);
}



bool is_armstrong(int num)
{
    int copy = num;
    int length = ZERO;
    double sum = ZERO;
    int numbers[N_MAX];

    while (num > ZERO)
    {
        numbers[length] = num % TEN;
        length++;
        num = num / TEN;
    }

    for (int i = ZERO; i < length; i++)
        sum += pow(numbers[i], length);

    if (sum == copy)
        return true;
    else
        return false;
}



int find_armstrong(int *const arm_nums, const int *const array, const int n)
{
    int amount = ZERO;

    for (int i = ZERO; i < n; i++)
        if (is_armstrong(array[i]))
        {
            arm_nums[amount] = array[i];
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
        int array[N_MAX];

        printf("Enter elements of array:\n");
        int code = input_array(array, n);

        if (code == SUCCESS)
        {
            int arm_nums[N_MAX];
            int amount = find_armstrong(arm_nums, array, n);

            if (amount > ZERO)
            {
                if (amount == n)
                {
                    printf("All numbers are Armstrong's numbers!");
                    return ALL_ERROR;
                }
                else
                {
                    printf("Armstrong's numbers:\n");
                    print_array(arm_nums, amount);
                    return SUCCESS;
                }
            }
            else
            {
                printf("No Armstrong's numbers found!");
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
