/*
Задача 5.02, вариант №3

Преобразовать исходную матрицу следующим образом:
удалить из нее все столбцы, содержащие по крайней мере одно число,
в записи которого встречается заданная цифра
*/

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 10
#define ZERO 0
#define ONE 1
#define MINUS_ONE -1
#define ONE_VAR 1
#define TWO_VARS 2
#define BASE 10

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define INPUT_OK 1
#define INPUT_ERROR 0
#define INPUT_FAILURE 1
#define DIGIT_ERROR 0
#define EMPTY_ERROR 2
#define DEL_COL 1
#define KEEP_COL 0


typedef int matr_t[N_MAX][N_MAX];
typedef const int c_int;


int input_data(int matrix[][N_MAX], int *const rows, int *const cols, int *const digit)
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
            printf("Enter the digit:\n");
            if ((scanf("%d", digit) == ONE_VAR) && (*digit >= ZERO) && (*digit < BASE))
                return INPUT_OK;
            else
            {
                printf("Invalid digit entered!");
                return DIGIT_ERROR;
            }
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


void delete_columns(int matrix[][N_MAX], c_int rows, int *const cols, c_int digit)
{
    int count = ZERO;

    while (count < (*cols))
    {
        for (int i = ZERO; i < rows; i++)
        {
            for (int j = ZERO; j < *cols; j++)
            {
                int curr_elem = abs(matrix[i][j]);
                int digit_count = ZERO;

                while (curr_elem > MINUS_ONE)
                {
                    int d = curr_elem % BASE;
                    if (d == digit)
                        digit_count++;
                    curr_elem /= BASE;
                    if (curr_elem == ZERO)
                        curr_elem--;
                }
                if (digit_count)
                {
                    for (int k = ZERO; k < rows; k++)
                        for (int p = j; p < *cols; p++)
                            matrix[k][p] = matrix[k][p + ONE];
                    (*cols)--;
                }
            }
        }
        count++;
    }
    if (!(*cols))
        printf("Matrix is empty!");
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
    int digit;

    if (input_data(matrix, &rows, &cols, &digit))
    {
        delete_columns(matrix, rows, &cols, digit);
        if (cols > ZERO)
        {
            print_matrix(matrix, rows, cols);
            return SUCCESS;
        }
        else
            return EMPTY_ERROR;
    }
    else
        return INPUT_FAILURE;
}
