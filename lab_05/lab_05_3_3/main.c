/*
Задача 5.03, вариант №3

Упорядочить строки матрицы по убыванию их наименьших элементов
*/

#include <stdio.h>

#define N_MAX 10
#define ZERO 0
#define ONE 1
#define ONE_VAR 1
#define TWO_VARS 2

#define SUCCESS 0
#define INPUT_OK 1
#define INPUT_ERROR 0
#define INPUT_FAILURE 1
#define SORT_OK 1
#define SORT_ERROR 0
#define SORT_FAILURE 2


typedef int matr_t[N_MAX][N_MAX];
typedef const int c_int;


int input_matrix(int matrix[][N_MAX], int *const rows, int *const cols)
{
    printf("Enter amount of the rows & cols (not more than ten):\n");
    if (scanf("%d %d", rows, cols) == TWO_VARS)
    {
        if ((*rows <= N_MAX) && (*cols <= N_MAX) && (*rows > ZERO) && (*rows > ZERO))
        {
            printf("Enter the matrix:\n");

            int element;
            for (int i = ZERO; i < *rows; i++)
                for (int j = ZERO; j < *cols; j++)
                {
                    if (scanf("%d", &element) == ONE_VAR)
                        matrix[i][j] = element;
                    else
                    {
                        printf("Invalid element(s) entered!");
                        return INPUT_ERROR;
                    }
                }
            return INPUT_OK;
        }
        else
        {
            printf("Invalid amount of rows/cols!");
            return INPUT_ERROR;
        }
    }
    else
    {
        printf("Invalid type of rows/cols!");
        return INPUT_ERROR;
    }
}


int min_element(c_int *const row, c_int cols)
{
    int min_elem = row[ZERO];
    for (int i = ONE; i < cols; i++)
        if (row[i] < min_elem)
            min_elem = row[i];
    return min_elem;
}


void swap_rows(int matrix[][N_MAX], c_int cols, c_int i, c_int j)
{
    int temp[N_MAX];
    for (int k = ZERO; k < cols; k++)
        temp[k] = matrix[i][k];

    for (int k = ZERO; k < cols; k++)
        matrix[i][k] = matrix[j][k];

    for (int k = ZERO; k < cols; k++)
        matrix[j][k] = temp[k];
}


int sort_rows(int matrix[][N_MAX], c_int rows, c_int cols)
{
    for (int i = ZERO; i < rows - ONE; i++)
        for (int j = i + ONE; j < rows; j++)
        {
            if (min_element(matrix[i], cols) < min_element(matrix[j], cols))
                swap_rows(matrix, cols, i, j);
            else if (min_element(matrix[i], cols) == min_element(matrix[j], cols))
            {
                printf("Some rows have same minimal elements!");
                return SORT_ERROR;
            }
        }
    return SORT_OK;
}


void print_matrix(matr_t matrix, c_int rows, c_int cols)
{
    printf("\n");
    for (int i = ZERO; i < rows; i++)
    {
        for (int j = ZERO; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}


int main()
{
    int rows, cols;
    matr_t matrix = { ZERO };

    if (input_matrix(matrix, &rows, &cols))
    {
        if (sort_rows(matrix, rows, cols))
        {
            print_matrix(matrix, rows, cols);
            return SUCCESS;
        }
        else
            return SORT_FAILURE;
    }
    else
        return INPUT_FAILURE;
}


