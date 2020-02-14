// Задача 1, вариант №3

#include <stdio.h>

#define N 100
#define HALF_N 50
#define ONE 1
#define TWO 2

#define ONE_VAR 1

#define SUCCESS 0
#define AMOUNT_ERROR 1
#define ELEM_ERROR 2


int create_array(int *array, int n, int *new_arr)
{
    int new_n = 0;

    for (int i = 0; i < n / TWO; i++)
    {
        new_arr[i] = array[i] * array[n - ONE - i];
        new_n++;
    }

    if (n % TWO == ONE)
    {
        new_arr[new_n] = array[n / TWO];
        new_n++;
    }

    return new_n;
}


int main()
{
    int arr[N];
    int n;
    int counter = 0;

    int check = scanf("%d", &n);
    if ((check == ONE_VAR) && (n > 0) && (n <= N))
    {
        for (int i = 0; i < n; i++)
        {
            int elem = scanf("%d", &arr[i]);
            counter += elem;
        }

        if (counter == n)
        {

            int result_arr[HALF_N];
            int result_n = create_array(arr, n, result_arr);

            for (int i = 0; i < result_n; i++)
                printf("%d ", result_arr[i]);

            return SUCCESS;
        }
        else
        {
            printf("Invalid elements");
            return ELEM_ERROR;
        }
    }
    else
    {
        printf("Invalid amount of elements");
        return AMOUNT_ERROR;
    }
}
