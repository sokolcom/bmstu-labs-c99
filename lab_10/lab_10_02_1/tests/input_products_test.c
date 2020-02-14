#include <stdio.h>
#include <stdint.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/data_processing.h"

#include "../include/auxiliary.h"
#include "../include/data_proc_test.h"



// Allocate array failure
void alloc_fail(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_01.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, MEMORY_TEST);
    if (!(code))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        printf("\tAllocation failed - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// No items were entered
void no_items(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_02.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (!(code) || (input.quantity != 0))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tNo items entered - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// Article contains letters in lowercase
void article_lowercase(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_03.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (!(code))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tArticle in lowercase - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// Article contains numbers
void article_numbers(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_04.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (!(code))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tArticle contains numbers - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// Name contains numbers
void name_numbers(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_05.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (!(code))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tName contains numbers - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// Amount is neagtive
void amount_negative(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_06.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (!(code))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tAmount is negative - FAILED!\n");

        free_data(&input);

        *testing_code = FAILED;
    }
}


// "nothing" in peculiar format (e.g. `nOTHIng`)
void strange_stop(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_07.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (code)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tPeculiar stopcode - FAILED!\n");

        *testing_code = FAILED;
    }
    else
    {
        free_data(&input);
    }
}


// Trivial input testing
void trivial_input(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/input_08.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    int32_t code = input_products(&input, NORMAL_TEST);
    if (code)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("INPUT_PRODUCTS() DESCRIPTION:\n");
        
        printf("\tTrivial input - FAILED!\n");

        *testing_code = FAILED;
    }
    else
    {
        free_data(&input);
    }
}