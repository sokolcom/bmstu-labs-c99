// Задача 4.04
// Gnome sort

#include <stdio.h>
#include <math.h>


#define N_MAX 10

#define ZERO 0
#define ONE 1

#define SUCCESS 0
#define SIZE_ERROR 1
#define INPUT_ERROR 2



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



void swap(int *const array, const int i)
{
    int temp = array[i];
    array[i] = array[i - ONE];
    array[i - ONE] = temp;
}



void gnome_sort(int *const array, const int n)
{
    int i = ONE;

    while (i < n)
    {
        if (i == ZERO)
            i = ONE;
        if (array[i] < array[i - ONE])
        {
            swap(array, i);
            i--;
        }
        else
            i++;
    }
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
            gnome_sort(array, n);
            printf("\nSorted array:\n");
            print_array(array, n);
            return SUCCESS;
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
