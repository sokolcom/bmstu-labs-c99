#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matrix_struct.h"
#include "matrix_algebra.h"
#include "matrix_cdio.h"
#include "powers.h"


// Return codes
#define TESTING_SUCCESS 0
#define TESTING_FAILURE 1

#define PASSED 1  // Module testing passed
#define FAILED 0  // Module testing failed

#define MEMORY_TEST 1
#define NORMAL_TEST 0


// Testing indicator 
//   fail - any of test have failed
//   done - testing successfully passed
typedef enum
{
    fail = 0,
    done
} test_flag_t;



// Create matrix to comapare with the testing result matrix
dmatrix_t ideal_matrix(const int64_t rows, const int64_t cols)
{
    dmatrix_t matrix;
    matrix.cols = cols;

    matrix.matrix_pointer = (int64_t **)calloc(rows, sizeof(int64_t *));
    if (matrix.matrix_pointer)
    {
        for (int64_t i = 0; i < rows; i++)
        {
            matrix.matrix_pointer[i] = (int64_t *)calloc(matrix.cols, sizeof(int64_t));

            if (!matrix.matrix_pointer[i])
            {
                free_matrix(&matrix);
                return matrix;
            }
            else
            {   
                matrix.rows = i + 1;
                for (int j = 0; j < matrix.cols; j++)
                {
                    // fill in ascending order (0, 1, 2, 3, ....)
                    matrix.matrix_pointer[i][j] = cols * i + j;
                }
            }
        }
    }

    return matrix;
}


// Generate identity matrix NxN
dmatrix_t id_matrix(const int64_t dime)
{
    dmatrix_t matrix;
    matrix.cols = dime;

    matrix.matrix_pointer = (int64_t **)calloc(dime, sizeof(int64_t *));
    if (matrix.matrix_pointer)
    {
        for (int64_t i = 0; i < dime; i++)
        {
            matrix.matrix_pointer[i] = (int64_t *)calloc(dime, sizeof(int64_t));

            if (!matrix.matrix_pointer[i])
            {
                free_matrix(&matrix);
                return matrix;
            }
            else
            {
                matrix.rows = i + 1;
                for (int j = 0; j < matrix.cols; j++)
                {
                    if (i == j)
                        matrix.matrix_pointer[i][j] = 1;
                    else
                        matrix.matrix_pointer[i][j] = 0;
                }
            }
        }
    }

    return matrix;   
}


// Compare matrices
int matrix_compare(const dmatrix_t a, const dmatrix_t b)
{
    // Check dimensions
    if ((a.rows != b.rows) || (a.cols != b.cols))
        return FAILED;

    // Check element-by-element
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            if (a.matrix_pointer[i][j] != b.matrix_pointer[i][j])
                return FAILED;
        }
    }
    return PASSED;
}


void dime_not_int(int *const testing_code)
{
    freopen("./module_testing/input_matrix_01.txt", "r", stdin);

    dmatrix_t matrix;
    int code = input_matrix(&matrix, NORMAL_TEST);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("INPUT_MATRIX() DESCRIPTION:\n");
        printf("\tInvalid dimensions (not an integer) - FAILED!\n");
        *testing_code = FAILED;
    }
}


void dime_error_value(int *const testing_code)
{
    freopen("./module_testing/input_matrix_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix;
    int code = input_matrix(&matrix, NORMAL_TEST);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_MATRIX() DESCRIPTION:\n");
        
        printf("\tInvalid dimensions (less than 1) - FAILED!\n");
        *testing_code = FAILED;
    }
}



void allocate_error(int *const testing_code)
{
    freopen("./module_testing/input_matrix_03.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix;
    int code = input_matrix(&matrix, MEMORY_TEST);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_MATRIX() DESCRIPTION:\n");
        
        printf("\tUnable to allocate memory - FAILED!\n");
        *testing_code = FAILED;
    }
}


void elems_not_int(int *const testing_code)
{
    freopen("./module_testing/input_matrix_04.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix;
    int code = input_matrix(&matrix, NORMAL_TEST);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_MATRIX() DESCRIPTION:\n");
        
        printf("\tInvalid elements input (not an integer) - FAILED!\n");
        *testing_code = FAILED;
    }
}


void trivial_input(int *const testing_code)
{
    freopen("./module_testing/input_matrix_05.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix;
    int code = input_matrix(&matrix, NORMAL_TEST);
    if (code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_MATRIX() DESCRIPTION:\n");
        
        printf("\tTrivial testing (while input) - FAILED!\n");
        *testing_code = FAILED;
    }

    // Matrix to compare with the input
    dmatrix_t original_matrix = ideal_matrix(3, 3); 
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_MATRIX() DESCRIPTION:\n");
        
        printf("\tTrivial testing (comparing input with pre-entered matrix) - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");
    
    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


// Inputing matrices
int input_matrix_testing()
{
    int testing_code = PASSED;

    // Invalid dimensions (not an integer)
    dime_not_int(&testing_code);
    
    // Invalid dimensions (less than 1)
    dime_error_value(&testing_code);
    
    // Unable to allocate 
    allocate_error(&testing_code);

    // Invalid elements input (not an integer)
    elems_not_int(&testing_code);

    // Trivial testing
    trivial_input(&testing_code);

    return testing_code;
}


void no_crop(int *const testing_code)
{
    freopen("./module_testing/crop_matrix_01.txt", "r", stdin);

    dmatrix_t matrix, original_matrix;
    input_matrix(&matrix, NORMAL_TEST);
    crop_matrix(&matrix);
    original_matrix = ideal_matrix(3, 3);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("CROP_MATRIX() DESCRIPTION:\n");
        printf("\tNo need to crop - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


void crop_rows(int *const testing_code)
{
    freopen("./module_testing/crop_matrix_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix, original_matrix;
    input_matrix(&matrix, NORMAL_TEST);
    crop_matrix(&matrix);
    original_matrix = ideal_matrix(2, 2);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("EXPAND_MATRIX() DESCRIPTION:\n");
        
        printf("\tCrop rows - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


void crop_cols(int *const testing_code)
{
    freopen("./module_testing/crop_matrix_03.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    dmatrix_t matrix, original_matrix;
    input_matrix(&matrix, NORMAL_TEST);
    crop_matrix(&matrix);
    original_matrix = ideal_matrix(2, 2);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("EXPAND_MATRIX() DESCRIPTION:\n");
        
        printf("\tCrop columns - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


// Croping matrix testing
int crop_matrix_testing()
{
    int testing_code = PASSED;

    // No need to crop
    no_crop(&testing_code);

    // Crop only rows
    crop_rows(&testing_code);

    // Crop only columns
    crop_cols(&testing_code);

    return testing_code;
}


void equal_dime(int *const testing_code)
{
    int64_t another_size = 3;
    dmatrix_t matrix, original_matrix;

    freopen("./module_testing/expand_matrix_01.txt", "r", stdin);

    input_matrix(&matrix, NORMAL_TEST);
    expand_matrix(&matrix, another_size);
    original_matrix = ideal_matrix(3, 3);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("EXPAND_MATRIX() DESCRIPTION:\n");
        printf("\tNo need to expand (equal size) - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


void less_dime(int *const testing_code)
{
    int64_t another_size = 2;
    dmatrix_t matrix, original_matrix;

    freopen("./module_testing/expand_matrix_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    input_matrix(&matrix, NORMAL_TEST);
    expand_matrix(&matrix, another_size);
    original_matrix = ideal_matrix(3, 3);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("EXPAND_MATRIX() DESCRIPTION:\n");
        
        printf("\tNo need to expand (another size is less) - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


void negative_elems_expand(int *const testing_code)
{
    int64_t another_size = 4;
    dmatrix_t matrix, original_matrix;

    freopen("./module_testing/expand_matrix_03.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);

    input_matrix(&matrix, NORMAL_TEST);
    expand_matrix(&matrix, another_size);

    freopen("./module_testing/expand_matrix_03_control.txt", "r", stdin);
    input_matrix(&original_matrix, NORMAL_TEST);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("EXPAND_MATRIX() DESCRIPTION:\n");
        
        printf("\tMatrix contains negative elements  - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


void trivial_expand(int *const testing_code)
{
    int64_t another_size = 5;
    dmatrix_t matrix, original_matrix;

    freopen("./module_testing/expand_matrix_04.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    input_matrix(&matrix, NORMAL_TEST);
    expand_matrix(&matrix, another_size);

    freopen("./module_testing/expand_matrix_04_control.txt", "r", stdin);
    input_matrix(&original_matrix, NORMAL_TEST);
    if (matrix_compare(original_matrix, matrix) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("EXPAND_MATRIX() DESCRIPTION:\n");
        
        printf("\tTrivial testing - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");

    free_matrix(&matrix);
    free_matrix(&original_matrix);
}


// Expanding matrix testing
int expand_matrix_testing()
{
    int testing_code = PASSED;

    // No need to expand (equal size)
    equal_dime(&testing_code);

    // No need to expand (another size is less)
    less_dime(&testing_code);
    
    // There are negative elements in matrix
    negative_elems_expand(&testing_code);

    // Trivial testing
    trivial_expand(&testing_code);

    return testing_code;
}


void pow_not_int(int *const testing_code)
{
    int64_t rho, gamma;  // powers
    int code;

    freopen("./module_testing/input_powers_01.txt", "r", stdin);
    code = input_powers(&rho, &gamma);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("INPUT_POWERS() DESCRIPTION:\n");
        printf("\tEntered not an integer - FAILED!\n");
        *testing_code = FAILED;
    }
}


void negative_power(int *const testing_code)
{
    int64_t rho, gamma;  // powers
    int code;

    freopen("./module_testing/input_powers_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = input_powers(&rho, &gamma);
    if (!code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_POWERS() DESCRIPTION:\n");
        
        printf("\tEntered negative power - FAILED!\n");
        *testing_code = FAILED;
    }
}


void pow_zero(int *const testing_code)
{
    int64_t rho, gamma;  // powers
    int code;

    freopen("./module_testing/input_powers_03.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = input_powers(&rho, &gamma);
    if (code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_POWERS() DESCRIPTION:\n");
        
        printf("\tEntered power equal zero - FAILED!\n");
        *testing_code = FAILED;
    }
}


void trivial_powers(int *const testing_code)
{
    int64_t rho, gamma;  // powers
    int code;

    freopen("./module_testing/input_powers_04.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = input_powers(&rho, &gamma);
    if (code)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_POWERS() DESCRIPTION:\n");
        
        printf("\tTrivial testing - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");
}


// Inputing powers and check if entered numbers valid or not
int input_powers_testing()
{
    int testing_code = PASSED;

    // Invalid variables (not an integer)
    pow_not_int(&testing_code);

    // Invalid variables (negative power)
    negative_power(&testing_code);
    
    // Valid variables (one of them equal 0)
    pow_zero(&testing_code);
    
    // Trivial testing
    trivial_powers(&testing_code);

    return testing_code;
}


void identity_m12n(int *const testing_code)
{
    dmatrix_t matrix_1, matrix_2, matrix_result, original_result;

    freopen("./module_testing/matrix_m12n_01.txt", "r", stdin);
    input_matrix(&matrix_1, NORMAL_TEST);
    input_matrix(&matrix_2, NORMAL_TEST);

    matrix_result.matrix_pointer = NULL;
    matrix_m12n(matrix_1, matrix_2, &matrix_result);
    original_result = ideal_matrix(4, 4);
    if (matrix_compare(original_result, matrix_result) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("MATRIX_M12N() DESCRIPTION:\n");
        printf("\tMultiply by identity matrix - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix_1);
    free_matrix(&matrix_2);
    free_matrix(&matrix_result);
    free_matrix(&original_result);
}


void trivial_m12n(int *const testing_code)
{
    dmatrix_t matrix_1, matrix_2, matrix_result, original_result;

    freopen("./module_testing/matrix_m12n_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    input_matrix(&matrix_1, NORMAL_TEST);
    input_matrix(&matrix_2, NORMAL_TEST);

    matrix_result.matrix_pointer = NULL;
    matrix_m12n(matrix_1, matrix_2, &matrix_result);
    original_result = ideal_matrix(3, 3);
    if (matrix_compare(original_result, matrix_result) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("MATRIX_M12N() DESCRIPTION:\n");
        
        printf("\tTrivial testing - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");

    free_matrix(&matrix_1);
    free_matrix(&matrix_2);
    free_matrix(&matrix_result);
    free_matrix(&original_result);
}


// Matrix multiplication testing
int matrix_m12n_testing()
{
    int testing_code = PASSED;

    // Multiply by identity matrix
    identity_m12n(&testing_code);

    // Trivial testing
    trivial_m12n(&testing_code);

    return testing_code;
}


void raise_identity(int *const testing_code)
{
    dmatrix_t matrix, raised, original_result;
    int power = 0;

    freopen("./module_testing/raise_to_the_power_01.txt", "r", stdin);
    input_matrix(&matrix, NORMAL_TEST);

    raise_to_the_power(matrix, &raised, power);
    original_result = id_matrix(2);

    if (matrix_compare(original_result, raised) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        printf("RAISE_TO_THE_POWER() DESCRIPTION:\n");
        printf("\tPower equals zero - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&raised);
    free_matrix(&original_result);
}


void no_raise(int *const testing_code)
{
    dmatrix_t matrix, raised, original_result;
    int power = 1;

    freopen("./module_testing/raise_to_the_power_02.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    input_matrix(&matrix, NORMAL_TEST);

    raise_to_the_power(matrix, &raised, power);
    original_result = ideal_matrix(3, 3);

    if (matrix_compare(original_result, raised) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("RAISE_TO_THE_POWER() DESCRIPTION:\n");

        printf("\tPower equals 1 - FAILED!\n");
        *testing_code = FAILED;
    }

    free_matrix(&matrix);
    free_matrix(&raised);
    free_matrix(&original_result);
}


void trivial_raise(int *const testing_code)
{
    dmatrix_t matrix, raised, original_result;
    int power = 2;

    freopen("./module_testing/raise_to_the_power_03.txt", "r", stdin);
    freopen("./module_testing/program_output.txt", "w", stdout);
    input_matrix(&matrix, NORMAL_TEST);

    raise_to_the_power(matrix, &raised, power);

    freopen("./module_testing/raise_to_the_power_03_control.txt", "r", stdin);
    input_matrix(&original_result, NORMAL_TEST);

    if (matrix_compare(original_result, raised) == FAILED)
    {
        freopen("./module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("RAISE_TO_THE_POWER() DESCRIPTION:\n");
        
        printf("\tTrivial testing - FAILED!\n");
        *testing_code = FAILED;
    }

    if (*testing_code == FAILED)
        printf("\n");

    free_matrix(&matrix);
    free_matrix(&raised);
    free_matrix(&original_result);
}


// Raising to the power testing
int raise_to_the_power_testing()
{
    int testing_code = PASSED;

    // Power equals zero
    raise_identity(&testing_code);

    // Power equals 1
    no_raise(&testing_code);

    // Trivial testing
    trivial_raise(&testing_code);

    return testing_code;
}


int main()
{
    printf("PAY ATTENTION PLEASE!\nLook for the module testing results in the ./module_testing/testing_results.txt");

    int code;
    test_flag_t flag = done;  // if any of tests failed flag will be `fail`

    // Here will be the description of the failed testing
    freopen("./module_testing/fail_desc.txt", "w", stdout);

    // Inputing array
    freopen("./module_testing/program_output.txt", "w", stdout);  // program prints will be there
    code = input_matrix_testing();
    freopen("./module_testing/testing_results.txt", "w", stdout);
    printf("TESTING input_matrix():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");
    
    // Croping matrix
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = crop_matrix_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING crop_matrix():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");

    // Expanding matrix
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = expand_matrix_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING expand_matrix():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");

    // Inputing power
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = input_powers_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING input_powers():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");
        
    // Computing matrix multiplication
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = matrix_m12n_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING matrix_m12n():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");
    
    // Raising matrix to the power
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = raise_to_the_power_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING raise_to_the_power():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");
   
    if (flag == fail)
    {
        printf("\nFor the detailed information about failures look for the fail_desc.txt!\n");
        return TESTING_FAILURE;
    }

    return TESTING_SUCCESS;
}
