/*
Задача 5.01, вариант №3

По матрице получить одномерный массив, присвоив его k-тому элементу значение 1,
если выполняется указанное условие: элементы k-ой строки образуют монотонную
последовательность, и значение 0 иначе
*/

#include <stdio.h>

#define N_MAX 10
#define ZERO 0
#define ONE 1
#define ONE_VAR 1
#define TWO_VARS 2

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define INPUT_OK 1
#define INPUT_ERROR 0
#define INPUT_FAILURE 1


typedef int matr_t[N_MAX][N_MAX];
typedef const int c_int;


int input_matrix(int matrix[N_MAX][N_MAX], int *const rows, int *const cols)
{
    int check, matrix_el;
    int arg_count = ZERO;

    check = scanf("%d%d", rows, cols);

    if (check == TWO_VARS)
    {
        if (*rows > N_MAX || *rows < ONE || *cols > N_MAX || *cols < ONE)
        {
            printf("Invalid matrix size!");
            return INPUT_ERROR;
        }
        else
        {
            for (int i = ZERO; i < *rows; ++i)
            {
                for (int j = ZERO; j < *cols; j++)
                {
                    check = scanf("%d", &matrix_el);
                    if (check == ONE_VAR)
                    {
                        matrix[i][j] = matrix_el;
                        arg_count++;
                    }
                    else
                    {
                        printf("Invalid element entered!");
                        return INPUT_ERROR;
                    }
                }
            }

            if (arg_count != (*rows) * (*cols))
            {
                printf("Invalid amount of arguments!");
                return INPUT_ERROR;
            }
            else
                return INPUT_OK;
        }
    }
    else
    {
        printf("Invalid dimension!");
        return INPUT_ERROR;
    }
}

/*
int input_matrix(int matrix[][N_MAX], int *const rows, int *const cols)
{
    int check;
    int element;
    int counter = ZERO;

    printf("Enter amount of the rows & cols (not more than ten):\n");
    check = scanf("%d %d", rows, cols);
    if (check == TWO_VARS)
    {
        if ((*rows <= N_MAX) && (*cols <= N_MAX) && (*rows > ZERO) && (*rows > ZERO))
        {
            printf("Enter the matrix:\n");
            for (int i = ZERO; i < *rows; i++)
                for (int j = ZERO; j < *cols; j++)
                {
                    check = scanf("%d", &element);
                    if (check == ONE_VAR)
                    {
                        matrix[i][j] = element;
                        counter++;
                    }
                    else
                    {
                        printf("Invalid element(s) entered!");
                        return INPUT_ERROR;
                    }
                }
            if (counter == ((*rows) * (*cols)))    
                return INPUT_OK;
            else
            {
                printf("Invalid amount of elements entered!");
                return INPUT_ERROR;
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
*/


void fill_array(matr_t matrix, c_int rows, c_int cols, int *const array)
{
    int order_up, order_down;

    if (cols == ONE)
    {
        for (int i = ZERO; i < rows; i++)
            array[i] = ZERO;
    }
    else
    {
        for (int i = ZERO; i < rows; i++)
        {
            order_up = ONE;
            for (int j = ZERO; j < cols - ONE; j++)
                if (matrix[i][j] <= matrix[i][j + ONE])
                    order_up++;

            order_down = ONE;
            for (int j = ZERO; j < cols - ONE; j++)
                if (matrix[i][j] >= matrix[i][j + ONE])
                    order_down++;

            if ((order_up == cols) || (order_down == cols))
                array[i] = ONE;
            else
                array[i] = ZERO;
        }
    }
}


void print_array(c_int *const array, c_int n)
{
    for (int i = ZERO; i < n; i++)
        printf("%d ", array[i]);
}


int main()
{
    int rows, cols;
    matr_t matrix;
    int output_array[N_MAX];

    if (input_matrix(matrix, &rows, &cols))
    {
        fill_array(matrix, rows, cols, output_array);
        print_array(output_array, rows);
        return SUCCESS;
    }
    else
        return INPUT_FAILURE;
}
