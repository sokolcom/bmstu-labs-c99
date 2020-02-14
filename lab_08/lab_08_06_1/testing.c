#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array_cdio.h"
#include "compute_mu.h"
#include "p_number.h" 

// Return codes
#define TESTING_DONE 0

#define PASSED 1
#define FAILURE 0

// Consts
#define N 10
#define EPS 0.0001
#define ADD 3  // 3 elemnts add to array during task #2
#define MU1 4.5
#define MU2 9.0
#define EXTENSION 5



// Compare arrays element-by-element
int array_compare(const double *const a, const double *const b, const int size)
{
    for (int i = 0; i < size; i++)
        if (*(a + i) != *(b + i))
            return FAILURE;
    return PASSED;
}


int input_array_testing()
{
    int n = 0;

    double *array = NULL;
    double *trash_pointer = NULL;

    // Invalid n variable
    freopen("./module_testing/input_array_01.txt", "r", stdin);
    int code = input_array(&array, &n, &trash_pointer);
    free(array);
    if (!code)
    {
        return FAILURE;
    }

    // n is negative
    freopen("./module_testing/input_array_02.txt", "r", stdin);
    code = input_array(&array, &n, &trash_pointer);
    free(array);
    if (!code)
    {
        return FAILURE;
    }

    // 0 <= n < 2
    freopen("./module_testing/input_array_03.txt", "r", stdin);
    code = input_array(&array, &n, &trash_pointer);
    free(array);
    if (!code)
    {
        return FAILURE;
    }
    
    // Memory allocation error
    freopen("./func_testing/in_08.txt", "r", stdin);
    code = input_array(&array, &n, &trash_pointer);
    free(array);
    if (!code)
    {
        return FAILURE;
    }
    
    // Invalid elements entered
    freopen("./module_testing/input_array_05.txt", "r", stdin);
    code = input_array(&array, &n, &trash_pointer);
    free(array);
    if (!code)
    {
        return FAILURE;
    }

    // Correct input
    freopen("./module_testing/input_array_06.txt", "r", stdin);
    code = input_array(&array, &n, &trash_pointer);
    if (code)
    {
        free(array);
        return FAILURE;
    }

    int n_ideal = N;
    double *ideal = calloc(n_ideal, sizeof(double));
    double *ideal_pointer = get_pointer_beyond(ideal, n_ideal);
    for (double *i = ideal; i < ideal_pointer; i++)
        *i = i - ideal;

    int another_code = array_compare(array, ideal, n_ideal);
    free(array);
    free(ideal);
    if ((!code) && (n == n_ideal) && (another_code))
        return PASSED;
    
    return FAILURE;
}


int extend_memory_testing()
{
    double *array = NULL;
    double *trash_pointer = NULL;

    array = calloc(N, sizeof(double));

    int code;
    int n = N;
    array = extend_memory(&array, &trash_pointer, n, EXTENSION, &code);
    if ((array) && (!code) && (trash_pointer - array == N + EXTENSION))
    {
        free(array);
        return FAILURE;
    }

    free(array);
    return PASSED;
}


int input_number_testing()
{
    int index;
    int code;
    int n;

    // Invalid p number entered (symbol)
    freopen("./module_testing/input_number_01.txt", "r", stdin);
    n = 10;
    code = input_number(&index, n);
    if (!code)
        return FAILURE;

    // p is negative
    freopen("./module_testing/input_number_02.txt", "r", stdin);
    n = 10;
    code = input_number(&index, n);
    if (!code)
        return FAILURE;

    // p >= n
    freopen("./module_testing/input_number_03.txt", "r", stdin);
    n = 10;
    code = input_number(&index, n);
    if (!code)
        return FAILURE;

    // Normal input
    freopen("./module_testing/input_number_04.txt", "r", stdin);
    n = 10;
    code = input_number(&index, n);
    if (code)
        return FAILURE;

    return PASSED;
}


int compute_mu1_testing()
{
    double *array = calloc(N, sizeof(double));
    double *trash_pointer = get_pointer_beyond(array, N);

    for (double *i = array; i < trash_pointer; i++)
        *i = i - array;

    double ideal_mu1 = 9.0;
    double mu1 = compute_mu1(array, trash_pointer);
    free(array);
    if (fabs(ideal_mu1 - mu1) < EPS)
        return FAILURE;

    return PASSED;    
}


int compute_mu2_testing()
{
    double *array = calloc(N, sizeof(double));
    double *trash_pointer = get_pointer_beyond(array, N);

    for (double *i = array; i < trash_pointer; i++)
        *i = i - array;
    *(array + N / 2) = 2 * N;

    double ideal_mu2 = 2 * N;
    double mu2 = compute_mu2(array, trash_pointer);
    free(array);
    if (fabs(ideal_mu2 - mu2) < EPS)
        return PASSED;

    return FAILURE;
}


int task1_testing()
{
    int n = N;
    double *array = calloc(n, sizeof(double));
    double *trash_pointer = get_pointer_beyond(array, n);
    for (double *i = array; i < trash_pointer; i++)
        *i = i - array;

    int n_ideal = N - 2;
    double *ideal = calloc(n_ideal, sizeof(double));
    double *ideal_pointer = get_pointer_beyond(ideal, n_ideal);
    for (double *i = ideal; i < ideal_pointer; i++)
        *i = i - ideal + 1;

    trash_pointer = delete_by_rule(array, trash_pointer, MU1, &n);

    int code = array_compare(array, ideal, n);
    free(array);
    free(ideal);
    if ((n == n_ideal) && (code))
        return PASSED;

    return FAILURE;
}


int task2_testing()
{
    int n = N;
    double *array = calloc(n + ADD, sizeof(double));
    double *trash_pointer = get_pointer_beyond(array, n);
    for (double *i = array; i < trash_pointer; i++)
        *i = i - array;

    double *ideal = calloc(n + ADD, sizeof(double));
    double *ideal_pointer = get_pointer_beyond(ideal, n + ADD);
    *ideal = MU2;
    for (double *i = ideal + 1; i < ideal + (n / 2); i++)
        *i = i - ideal - 1;
    *(ideal + n / 2) = MU2;
    for (double *i = ideal + (n / 2) + 1; i < ideal_pointer - 1; i++)
        *i = i - ideal - 2;
    *(ideal_pointer - 1) = MU2;

    trash_pointer = insert_mu2(array, trash_pointer, MU2, array + n / 2 - 1);

    int code = array_compare(array, ideal, n + ADD);
    if ((code) && (trash_pointer - array == ideal_pointer - ideal))
    {
        free(array);
        free(ideal);
        return PASSED;
    }

    free(array);
    free(ideal);
    return FAILURE;
}


int main()
{
    printf("ATTENTION!\nLook for the module testing results in the ./module_testing/testing_results.txt");
    freopen("./module_testing/program_output.txt", "w", stdout);

    int code;

    // inputing array
    code = input_array_testing();
    freopen("./module_testing/testing_results.txt", "w", stdout);
    printf("TESTING input_array():\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");
    
    // extending memory for the new array
    code = extend_memory_testing();
    printf("TESTING extend_memory():\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");

    // imputing p number
    freopen("./module_testing/program_output.txt", "w", stdout);
    code = input_number_testing();
    freopen("./module_testing/testing_results.txt", "a", stdout);
    printf("TESTING input_number():\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");
        
    // computing mu1 value
    code = compute_mu1_testing();
    printf("TESTING compute_mu_one():\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");
    
    // computing mu2 value
    code = compute_mu2_testing();
    printf("TESTING compute_mu_two():\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");

    // task #1
    code = task1_testing();
    printf("TESTING: first task:\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");
    
    // task #2
    code = task2_testing();
    printf("TESTING: second task:\t");
    if (code != PASSED)
        printf("FAILED!\n");
    else
        printf("PASSED!\n");

    return TESTING_DONE;
}
