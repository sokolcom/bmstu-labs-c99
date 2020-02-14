#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "matrix_struct.h"
#include "matrix_cdio.h"
#include "powers.h"
#include "matrix_algebra.h"


// Return codes
#define SUCCESS 0
#define RAISING_ERROR -10
#define MULT_ERROR -20



int main()
{
    int code;

    // Matrix A input
    dmatrix_t matrix_1;
    code = input_matrix(&matrix_1); 
    if (code)
    {
        printf("Error!\nTry again plz!");
        return code;
    }
    // Matrix B input
    dmatrix_t matrix_2;
    code = input_matrix(&matrix_2); 
    if (code)
    {
        free_matrix(&matrix_1);

        printf("Error!\nTry again plz!");
        return code;
    }

    // Crop matrix A
    code = crop_matrix(&matrix_1);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nUnable to crop matrix A!");
        return code;
    }
    // Crop matrix B
    code = crop_matrix(&matrix_2);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nDenied to crop matrix B!");
        return code;
    }

    // Expand matrix A
    code = expand_matrix(&matrix_1, matrix_2.rows);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nDenied to expand matrix A!");
        return code;
    }
    // Expand matrix B
    code = expand_matrix(&matrix_2, matrix_1.rows);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nUnable to crop matrix B!");
        return code;
    }
    
    // Powers (rho n' gamma)
    int64_t rho, gamma;
    code = input_powers(&rho, &gamma);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nInvalid input!");
        return code;
    }

    // A^rho
    dmatrix_t raised_matrix_1;
    code = raise_to_the_power(matrix_1, &raised_matrix_1, rho);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nError during raising to the power!");
        return RAISING_ERROR;
    }

    // B^gamma
    dmatrix_t raised_matrix_2;
    code = raise_to_the_power(matrix_2, &raised_matrix_2, gamma);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&raised_matrix_1);
        free_matrix(&matrix_2);

        printf("Error!\nError during raising to the power!");
        return RAISING_ERROR;
    }


    // A^rho x B^gamma = ???
    dmatrix_t matrix_result;
    matrix_result.matrix_pointer = NULL;
    code = matrix_m12n(raised_matrix_1, raised_matrix_2, &matrix_result);
    if (code)
    {
        free_matrix(&matrix_1);
        free_matrix(&matrix_2);
        free_matrix(&raised_matrix_1);
        free_matrix(&raised_matrix_2);

        printf("Error!\nError during multiplication!");
        return MULT_ERROR;
    }

    // Print result
    print_matrix(&matrix_result);

    // Free memory
    free_matrix(&matrix_1);
    free_matrix(&matrix_2);
    free_matrix(&raised_matrix_1);
    free_matrix(&raised_matrix_2);
    free_matrix(&matrix_result);

    return SUCCESS;
}