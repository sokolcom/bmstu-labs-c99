#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // int64_t
#include <inttypes.h>  // for scanf() & printf() int64_t
#include <stdarg.h>  // for the testing (va_list etc)

#include "matrix_struct.h"
#include "matrix_cdio.h"

#define SUCCESS 0
#define DIMENSION_INPUT_ERROR 10
#define DIMENSION_VALUE_ERROR 11
#define ELEMENTS_ERROR 20
#define MEMORY_ERROR 30
#define EXTEND_MEMORY_ERROR 31
#define CROP_ERROR 40
#define EXPAND_ERROR 50

#define VAR_INPUT 1  // scanf() successfully read 1 variable
#define MIN_DIMENSION 1  // Matrix should be at least 1x1

#define ROWS 1  // Flag which indicates to work with rows
#define COLS -1  // Flag which indicates to work with columns



// Auxiliary functions

// min(x, y)
int64_t croping_size(const int64_t x, const int64_t y)
{
    if (x < y)
        return x;
    
    return y;
}


// max(x, y)
int64_t extending_size(const int64_t x, const int64_t y)
{
    if (x > y)
        return x;
    
    return y;
}


int check_dimension(const int64_t *const dimension)
{
    if (*dimension < MIN_DIMENSION)
        return DIMENSION_VALUE_ERROR;
    return SUCCESS;
}


int check_memory(const int64_t *const array)
{
    if (!array)
        return MEMORY_ERROR;
    return SUCCESS;
}


// Allocating memory for another matrix row
// `const int key` says if we enter elements or not
int64_t *create_row(const int64_t size, const int key)
{
    int64_t *array = (int64_t *)calloc(size, sizeof(int64_t));
    if (check_memory(array))
        return NULL;

    if (key == ENTER_ELEMS)
    {
        int check_input;
        for (int64_t i = 0; i < size; i++)
        {
            check_input = scanf("%" SCNd64, &array[i]);
            if (check_input != VAR_INPUT)
            {
                free(array);
                return NULL;
            }
        }
    }

    return array;
}


// Minimal element in matrix row
int64_t get_minimal_in_row(const int64_t *const row, const int64_t length)
{
    int64_t min_element = row[0];
    for (int64_t element = 1; element < length; element++)
        if (row[element] <= min_element)
            min_element = row[element];
    
    return min_element;
}


// Returns column index in which element is contained
int64_t get_col_index(const int64_t *const row, const int64_t length, const int64_t element)
{
    int64_t index;
    for (int64_t i = 0; i < length; i++)
        if (row[i] == element)
            index = i;
    
    return index;
}


// Input the matrix (allocate & enter elements)
int input_matrix(dmatrix_t *const matrix, ...)
{
    int64_t rows_amount;
    printf("Enter amount of the rows:\n");
    int check_input = scanf("%" SCNd64, &rows_amount);
    if (check_input != VAR_INPUT)
        return DIMENSION_INPUT_ERROR;

    if (check_dimension(&rows_amount))
        return DIMENSION_VALUE_ERROR;

    printf("Enter amount of the cols:\n");
    check_input = scanf("%" SCNd64, &matrix->cols);
    if (check_input != VAR_INPUT)
        return DIMENSION_INPUT_ERROR;

    if (check_dimension(&matrix->cols))
        return DIMENSION_VALUE_ERROR;

    matrix->matrix_pointer = (int64_t **)calloc(rows_amount, sizeof(int64_t *));

// To cause memory allocation error in testing
#ifdef __TESTING__
// #define calloc(x, y) (NULL)
    va_list arg;
    va_start(arg, matrix);
    int memory_flag = va_arg(arg, int);
    va_end(arg);

    if (memory_flag)
    {
        free(matrix->matrix_pointer);
        matrix->matrix_pointer = NULL;  // simulate memory allocation error 
    }
#endif

    if (matrix->matrix_pointer)
    {
        printf("Enter elements of the matrix:\n");
        for (int64_t i = 0; i < rows_amount; i++)
        {
            matrix->matrix_pointer[i] = create_row(matrix->cols, ENTER_ELEMS);
            if (!matrix->matrix_pointer[i])
            {
                matrix->rows = i;
                free_matrix(matrix);
                return MEMORY_ERROR;
            }
        }

        matrix->rows = rows_amount;
    }
    else
        return MEMORY_ERROR;

    return SUCCESS;
}


// Get index of the row/column to delete (finds minimal element)
int64_t min_element_location(const dmatrix_t *const matrix, const int flag)
{
    int64_t temp;
    int64_t min_element = get_minimal_in_row(matrix->matrix_pointer[0], matrix->cols);
    int64_t index;

    if (flag == ROWS)
    {
        index = 0;
        for (int64_t i = 1; i < matrix->rows; i++)
        {
            temp = get_minimal_in_row(matrix->matrix_pointer[i], matrix->cols);
            if (temp <= min_element)
            {
                min_element = temp;
                index = i;
            }
        }
    }
    else
    {
        index = get_col_index(matrix->matrix_pointer[0], matrix->cols, min_element);
        for (int64_t i = 1; i < matrix->rows; i++)
        {
            temp = get_minimal_in_row(matrix->matrix_pointer[i], matrix->cols);
            if (temp <= min_element)
            {
                min_element = temp;
                index = get_col_index(matrix->matrix_pointer[i], matrix->cols, min_element);
            }
        }
    }
    
    return index;
}


// Delete row from the matrix by given index
int delete_row(dmatrix_t *const matrix, const int64_t row_index)
{
    free(matrix->matrix_pointer[row_index]);
    for (int64_t row = row_index; row < matrix->rows - 1; row++)
    {
        matrix->matrix_pointer[row] = matrix->matrix_pointer[row + 1];
    }

    matrix->matrix_pointer = (int64_t **)realloc(matrix->matrix_pointer, sizeof(int64_t *) * (matrix->rows - 1));
    if (!matrix->matrix_pointer)
        return CROP_ERROR; 

    return SUCCESS;
}


// Delete column from the matrix by given index
int delete_col(dmatrix_t *const matrix, const int64_t col_index)
{
    for (int64_t row = 0; row < matrix->rows; row++)
    {
        for (int64_t elem = col_index; elem < matrix->cols - 1; elem++)
            matrix->matrix_pointer[row][elem] = matrix->matrix_pointer[row][elem + 1];
            
        matrix->matrix_pointer[row] = (int64_t *)realloc(matrix->matrix_pointer[row], sizeof(int64_t) * (matrix->cols - 1));
        if (!matrix->matrix_pointer[row])
            return CROP_ERROR; 
    }  

    return SUCCESS;
}


// Crop rows/columns
// `const int flag` indicates what to delete: rows or cols?
int crop_by_criteria(dmatrix_t *const matrix, const int crop_size, const int flag)
{
    // Crop rows
    if (flag == ROWS)
    {
        int64_t row_index;
        int code;
        while (matrix->rows > crop_size)
        {
            row_index = min_element_location(matrix, ROWS);
            code = delete_row(matrix, row_index);
            if (code)
                return CROP_ERROR;
            
            (matrix->rows)--;
        }
    }
    // Crop columns
    else
    {
        int64_t col_index;
        int code;
        while (matrix->cols > crop_size)
        {
            col_index = min_element_location(matrix, COLS);
            code = delete_col(matrix, col_index);
            if (code)
                return CROP_ERROR;
            
            (matrix->cols)--;
        }
    }

    return SUCCESS;
}


// Delete rows/columns from the matrix
// RUSSO COMMENTO ARRIVING SOON
int crop_matrix(dmatrix_t *const matrix)
{
    if (matrix->rows == matrix->cols)
        return SUCCESS;

    // min(row, cols)
    int64_t new_dime = croping_size(matrix->rows, matrix->cols);
    int code;
    if (new_dime == matrix->rows)
        code = crop_by_criteria(matrix, new_dime, COLS);  // del cols 
    else    
        code = crop_by_criteria(matrix, new_dime, ROWS);  // del rows
    
    return code;
}


// Compute integer raising to the power
int64_t pow_int(const int64_t number, const int64_t power)
{
    int64_t copy_number = number;

    for (int64_t i = 1; i < power; i++) 
    {
        copy_number *= number;
    }

    return copy_number;
}


// Compute geometric mean (integer)
int64_t geom_mean(const dmatrix_t *const matrix, const int64_t col)
{
    int64_t product = matrix->matrix_pointer[0][col];
    for (int64_t i = 1; i < matrix->rows; i++)
        product *= matrix->matrix_pointer[i][col];

    if (product < 0)
        product *= -1;
    
    int64_t mean = 0;
    while (pow_int(mean, matrix->rows) <= product)
    {
        mean++;
    }
    
    return --mean;
}


// Fill expanded row
void fill_row(int64_t *const row, const dmatrix_t *const matrix)
{
    for (int64_t i = 0; i < matrix->cols; i++)
    {
        row[i] = geom_mean(matrix, i);
    }
}


// Expand rows/columns
// `const int flag` indicates what to expand: rows or cols?
int expand_by_criteria(dmatrix_t *const matrix, const int64_t expand_size, const int flag)
{
    // Expand rows
    if (flag == ROWS)
    {
        matrix->matrix_pointer = (int64_t **)realloc(matrix->matrix_pointer, sizeof(int64_t *) * expand_size);
        if (matrix->matrix_pointer)
        {
            while (matrix->rows < expand_size)
            {
                matrix->matrix_pointer[matrix->rows] = create_row(matrix->cols, SKIP_ELEMS);  // avoid scanf()
                if (!matrix->matrix_pointer[matrix->rows])
                    return EXPAND_ERROR; 

                fill_row(matrix->matrix_pointer[matrix->rows], matrix);  // fill new row by given rule
                (matrix->rows)++;
            }
        }    
        else
            return EXPAND_ERROR;
    }
    // Expand columns
    else
    {
        for (int64_t row = 0; row < matrix->rows; row++)
        {
            matrix->matrix_pointer[row] = (int64_t *)realloc(matrix->matrix_pointer[row], sizeof(int64_t) * expand_size);
            if (matrix->matrix_pointer[row])
            {
                for (int64_t col = matrix->cols; col < expand_size; col++)
                {
                    matrix->matrix_pointer[row][col] = get_minimal_in_row(matrix->matrix_pointer[row], matrix->cols);
                }
            }
            else
            {
                return EXPAND_ERROR;
            }
        }

        matrix->cols = expand_size;
    }

    return SUCCESS;
}


// Expand matrix
// RUSSO COMMENTO ARRIVING SOON
int expand_matrix(dmatrix_t *const matrix, const int64_t matrix_2_dime)
{
    int64_t new_dime = extending_size(matrix->rows, matrix_2_dime);
    if (new_dime == matrix->rows)
        return SUCCESS;
    else
    {
        int code;
        code = expand_by_criteria(matrix, new_dime, ROWS);  // add rows
        if (code)
            return EXPAND_ERROR; 

        code = expand_by_criteria(matrix, new_dime, COLS);  // add cols
        if (code)
            return EXPAND_ERROR; 

        return SUCCESS;
    }
}


// Free allocated memory
void free_matrix(const dmatrix_t *const matrix)
{
    for (int64_t row = 0; row < matrix->rows; row++)
        free(matrix->matrix_pointer[row]);

    free(matrix->matrix_pointer);
}


// Output the matrix
void print_matrix(const dmatrix_t *const matrix)
{
    for (int64_t i_row = 0; i_row < matrix->rows; i_row++)
    {
        for (int64_t i_col = 0; i_col < matrix->cols; i_col++)
        {
            printf("%5" PRId64 " ", matrix->matrix_pointer[i_row][i_col]);
        }
        printf("\n");
    }
}
