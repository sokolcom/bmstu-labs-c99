#include <stdio.h>

#define MAX_LENGTH_NAME 100
#define OUTPUT_NAME "out.txt"
#define ROWS_MAX 100
#define COLS_MAX 100
#define AMOUNT_MAX 10000
#define MIN_DIME 1
#define ZERO 0
#define ONE 1

#define SUCCESS 0
#define EXIST_ERROR 1
#define EMPTY_ERROR 2
#define DIME_ERROR 3
#define OK 1
#define OOPS 0

void print_amounts(int matrix[][COLS_MAX], const int i, const int j,
                 const int dime, const int amount)
{
    for (int k = ZERO; i < dime; k++)
        for (int l = ZERO; j < dime; l++)
           matrix[i + k][j + l] = amount;
}


int around_elems(int matrix[][COLS_MAX], const int i, const int j,
                 const int rows, const int cols)
{
    if (rows == cols)
    {
        for (int k = ZERO; i < rows; k++)
            for (int l = ZERO; j < rows; l++)
               if (matrix[i + k][j + l] != ZERO)
                   return OOPS;
        return OK;
    }
    else
        return OOPS;
}


void print_result(FILE* f, int matrix[][COLS_MAX], const int rows,
                  const int cols, const int amount)
{
    int max_dime = ONE;
    for (int i = ZERO; i < rows - ONE; i++)
        for (int j = ZERO; j < cols - ONE; j++)
            for (int k = ONE; k < cols - j; k++)
                for (int l = ONE; l < rows - i; k++)
                    if (around_elems(matrix, i, j, k, l))
                        if (k > max_dime)
                            max_dime = k;

    for (int i = ZERO; i < rows - ONE; i++)
        for (int j = ZERO; j < cols - ONE; j++)
            for (int k = ONE; k < cols - j; k++)
                for (int l = ONE; l < rows - i; k++)
                    if (around_elems(matrix, i, j, k, l))
                        print_amounts(matrix, i, j, k, amount);


    for (int i = ZERO; i < rows; i++)
    {
        for (int j = ZERO; j < cols; j++)
           fprintf(f, "%d ", matrix[i][j]);
        fprintf(f, "\n");
    }
}


int analyse_data(FILE* input_file)
{
    FILE* output_file = fopen(OUTPUT_NAME, "w");

    int rows;
    fscanf(input_file, "%d", &rows);
    int cols;
    fscanf(input_file, "%d", &cols);
    int amount;
    fscanf(input_file, "%d", &amount);

    if ((rows > ROWS_MAX) || (cols > COLS_MAX) || (amount > AMOUNT_MAX) ||
            (rows < MIN_DIME) || (cols < MIN_DIME) || (amount < MIN_DIME))
    {
        printf("Invlid matrix configurations!");
        return DIME_ERROR;
    }

    int matrix[ROWS_MAX][COLS_MAX] = { ZERO };
    int n;
    int m;
    int value;
    while (!feof(input_file))
    {
        fscanf(input_file, "%d %d %d", &n, &m, &value);
        matrix[n][m] = value;
    }

    print_result(output_file, matrix, rows, cols, amount);
    fclose(output_file);
    return SUCCESS;
}


int main()
{
    char file_name[MAX_LENGTH_NAME];
    printf("Enter file name to analyse:\n");
    scanf("%s", file_name);

    FILE* input_file = fopen(file_name, "r");

    if (input_file)
    {
        char check_empty = fgetc(input_file);
        if (check_empty == EOF)
        {
            printf("File is empty!\n");
            fclose(input_file);
            return EMPTY_ERROR;
        }
        else
            ungetc(check_empty, input_file);

        if (analyse_data(input_file) == SUCCESS)
        {
            fclose(input_file);
            return SUCCESS;
        }
        else
            return DIME_ERROR;
    }
    else
    {
        printf("File with the entered name doesn't exist!\n");
        return EXIST_ERROR;
    }
}
