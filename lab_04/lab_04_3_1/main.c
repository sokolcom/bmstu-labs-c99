// Задача 4.01

#include <stdio.h>
#include <math.h>


#define N_MAX 10

#define FLOAT_ONE 1.0
#define ZERO 0
#define INT_ONE 1

#define SUCCESS 0
#define SIZE_ERROR 1
#define INPUT_ERROR 2
#define VALUE_ERROR 3



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


int count_positive(const int *const array, const int n, int *const prod)
{
    int count = ZERO;

    for (int i = ZERO; i < n; i++)
    {
        if (array[i] > ZERO)
        {
            count++;
            *prod *= array[i];
        }
    }

    return count;
}


int main()
{
    int n;
    int check;

    printf("Enter amount of elements (less than ten):\n");
    check = scanf("%d", &n);
    if ((check == INT_ONE) && (n > ZERO) && (n <= N_MAX))
    {
        int array[N_MAX];

        printf("Enter elements of array:\n");
        int code = input_array(array, n);

        if (code == SUCCESS)
        {
            int prod = INT_ONE;
            int positive_elems = count_positive(array, n, &prod);

            if (positive_elems > ZERO)
            {
                float geom_mean = pow(prod, FLOAT_ONE / positive_elems);
                printf("%f", geom_mean);

                return SUCCESS;
            }
            else
            {
                printf("No positive elements found!");
                return VALUE_ERROR;
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
