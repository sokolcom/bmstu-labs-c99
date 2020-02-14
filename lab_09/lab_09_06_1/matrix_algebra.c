#include <stdint.h>  // int64_t
#include <stdlib.h>

#include "matrix_struct.h"
#include "matrix_algebra.h"
#include "matrix_cdio.h"


#define SUCCESS 0
#define INIT_ERROR 500
#define MULT_ERROR 600
#define RAISE_ERROR 700



// Init matrix
int init_matrix(dmatrix_t *const matrix, const int64_t rows, const int64_t cols)
{
    matrix->cols = cols;
    matrix->matrix_pointer = (int64_t **)calloc(rows, sizeof(int64_t *));
    if (matrix->matrix_pointer)
    {
        for (int64_t i = 0; i < rows; i++)
        {
            matrix->matrix_pointer[i] = create_row(cols, SKIP_ELEMS);
            if (!matrix->matrix_pointer[i])
            {
                matrix->rows = i;
                free_matrix(matrix);
                return INIT_ERROR;
            }
        }

        matrix->rows = rows;
    }

    return SUCCESS;
}


// Computing element of the resulting matrix
int64_t dot_product(const dmatrix_t matr_a, const dmatrix_t matr_b, const int64_t index_row, const int64_t index_col)
{
    int64_t sum = 0;
    for (int64_t i = 0; i < matr_a.rows; i++)
    {
        sum += matr_a.matrix_pointer[index_row][i] * matr_b.matrix_pointer[i][index_col];
    }

    return sum;
}


// Matrix multiplication
// Keep it in mind!!!!!
// matrix_m12n() FREES matr_a (first parameter)
int matrix_m12n(const dmatrix_t matr_a, const dmatrix_t matr_b, dmatrix_t *const product_matrix)
{
    // To distinct raising to the power and basic multiplication
    if (product_matrix->matrix_pointer == NULL)
    {
        if (init_matrix(product_matrix, matr_a.rows, matr_a.cols) == INIT_ERROR)
        {
            return MULT_ERROR;;
        }
    }

    for (int64_t i_row = 0; i_row < matr_a.rows; i_row++)
    {
        for (int64_t i_col = 0; i_col < matr_b.cols; i_col++)
        {
            product_matrix->matrix_pointer[i_row][i_col] = dot_product(matr_a, matr_b, i_row, i_col);
        }
    }

    // free_matrix(&matr_a);

    return SUCCESS;
}


// Raise to the power zero (make an identity matrix)
int identity_matrix(dmatrix_t *const id_matrix, const dmatrix_t matrix)
{
    if (init_matrix(id_matrix, matrix.rows, matrix.cols) == INIT_ERROR)
        return INIT_ERROR;

    for (int64_t i_row = 0; i_row < matrix.rows; i_row++)
    {
        for (int64_t i_col = 0; i_col < matrix.cols; i_col++)
        {
            if (i_row == i_col)
                id_matrix->matrix_pointer[i_row][i_col] = 1;
            else
                id_matrix->matrix_pointer[i_row][i_col] = 0;
        }
    }

    return SUCCESS;
}


// Copy matrix into a new one
void copy_matrix(const dmatrix_t matrix, dmatrix_t *const copied_matrix)
{   
    for (int64_t i_row = 0; i_row < matrix.rows; i_row++)
    {
        for (int64_t i_col = 0; i_col < matrix.cols; i_col++)
        {
            copied_matrix->matrix_pointer[i_row][i_col] = matrix.matrix_pointer[i_row][i_col];
        }
    }
}


// Raise matrix to the entered power
int raise_to_the_power(const dmatrix_t matrix, dmatrix_t *const raised_matrix, const int64_t power)
{
    // Identity matrix
    if (power == 0)
    { 
        if (identity_matrix(raised_matrix, matrix) == INIT_ERROR)
        {
            return RAISE_ERROR;
        }
    }
    // Trivial case
    else
    {
        dmatrix_t temp_matrix;
        if ((init_matrix(raised_matrix, matrix.rows, matrix.cols) == INIT_ERROR) ||
            (init_matrix(&temp_matrix, matrix.rows, matrix.cols) == INIT_ERROR))
        {
            return RAISE_ERROR;
        }

        copy_matrix(matrix, raised_matrix);
        copy_matrix(matrix, &temp_matrix);

        for (int64_t matrix_power = 1; matrix_power < power; matrix_power++)
        {
            matrix_m12n(temp_matrix, matrix, raised_matrix);
            copy_matrix(*raised_matrix, &temp_matrix);
        }

        free_matrix(&temp_matrix);
    }

    return SUCCESS;
}
