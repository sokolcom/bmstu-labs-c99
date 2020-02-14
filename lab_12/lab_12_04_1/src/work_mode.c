#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/list_interface.h"
#include "../include/arithmetics.h"
#include "../include/work_mode.h"



// Output entered number
int32_t output_number(FILE *const input_stream, FILE *const output_stream)
{
    int32_t number;

    // fprintf(output_stream, "Enter number to print:\n");

    int32_t code = fscanf(input_stream, "%" PRId32, &number);
    if ((code != ONE_VAR) || (number < MIN_VALUE))
    {
        return INPUT_ERROR;
    }

    // List of the prime multipliers
    node_t *prime_m9s = NULL;

    // Factorize entered number 
    code = factorize_number(&prime_m9s, number);
    if (code)
    {
        free_list(prime_m9s);
        return code;
    }

    // Print result
    print_list(output_stream, prime_m9s);

    // Free list
    free_list(prime_m9s);

    return SUCCESS;
}


// Multiply two entered numbers
int32_t multiply(FILE *const input_stream, FILE *const output_stream)
{
    int32_t number_1, number_2;

    // fprintf(output_stream, "Enter numbers to multiply:\n");

    int32_t code = fscanf(input_stream, "%" PRId32 " %" PRId32, &number_1, &number_2);
    if ((code != TWO_VARS) || (number_1 < MIN_VALUE) || (number_2 < MIN_VALUE))
    {
        return INPUT_ERROR;
    }

    // Lists of the prime multipliers
    node_t *prime_m9s_1 = NULL;
    node_t *prime_m9s_2 = NULL;
    node_t *prime_m9s_result = NULL;

    // Factorize entered numbers
    code = factorize_number(&prime_m9s_1, number_1);
    if (code)
    {
        free_list(prime_m9s_1);
        return code;
    }

    code = factorize_number(&prime_m9s_2, number_2);
    if (code)
    {
        free_list(prime_m9s_1);
        free_list(prime_m9s_2);
        return code;
    }

    // Multiply two factorized numbers
    code = multiply_factorized(prime_m9s_1, prime_m9s_2, &prime_m9s_result);
    if (code)
    {
        free_list(prime_m9s_1);
        free_list(prime_m9s_2);
        free_list(prime_m9s_result);
        return code;
    }

    // Print result
    print_list(output_stream, prime_m9s_result);

    // Free lists
    free_list(prime_m9s_1);
    free_list(prime_m9s_2);
    free_list(prime_m9s_result);

    return SUCCESS;
}


// Square entered number
int32_t square_number(FILE *const input_stream, FILE *const output_stream)
{
    int32_t number;

    // fprintf(output_stream, "Enter number to square:\n");

    int32_t code = fscanf(input_stream, "%" PRId32, &number);
    if ((code != ONE_VAR) || (number < MIN_VALUE))
    {
        return INPUT_ERROR;
    }

    // List of the prime multipliers
    node_t *prime_m9s = NULL;

    // Factorize entered number 
    code = factorize_number(&prime_m9s, number);
    if (code)
    {
        free_list(prime_m9s);
        return code;
    }

    // Square factorized number
    square_factorized(&prime_m9s);

    // Print result
    print_list(output_stream, prime_m9s);

    // Free list
    free_list(prime_m9s);

    return SUCCESS;
}


// Divide two entered numbers
int32_t divide(FILE *const input_stream, FILE *const output_stream)
{
    int32_t number_1, number_2, code;

    // fprintf(output_stream, "Enter numbers to divide:\n");

    code = fscanf(input_stream, "%" PRId32 " %" PRId32, &number_1, &number_2);
    if ((code != TWO_VARS) || (number_1 < MIN_VALUE) || (number_2 < MIN_VALUE))
    {
        return INPUT_ERROR;
    }

    // Lists of the prime multipliers
    node_t *prime_m9s_1 = NULL;
    node_t *prime_m9s_2 = NULL;
    node_t *prime_m9s_result = NULL;

    // Factorize entered numbers
    // Dividend
    code = factorize_number(&prime_m9s_1, number_1);
    if (code)
    {   
        free_list(prime_m9s_1);
        return code;
    }

    // Divisor
    code = factorize_number(&prime_m9s_2, number_2);
    if (code)
    {
        free_list(prime_m9s_1);
        free_list(prime_m9s_2);
        return code;
    }

    // Divide two factorized numbers
    code = divide_factorized(prime_m9s_1, prime_m9s_2, &prime_m9s_result);
    if (code)
    {   
        free_list(prime_m9s_1);
        free_list(prime_m9s_2);
        free_list(prime_m9s_result);
        return code;
    }

    // Print result
    print_list(output_stream, prime_m9s_result);

    // Free lists
    free_list(prime_m9s_1);
    free_list(prime_m9s_2);
    free_list(prime_m9s_result);

    return SUCCESS;
}
