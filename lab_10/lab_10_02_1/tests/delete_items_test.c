#include <stdio.h>
#include <stdint.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/data_processing.h"

#include "../include/auxiliary.h"
#include "../include/data_proc_test.h"



// After deletion no items left
void empty_delete(int32_t *const testing_code)
{
    stock_t input;

    freopen("./tests/module_testing/delete_01.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);

    int32_t code = delete_items(&input, "LIPSTICK");

    if (!(code) || (input.quantity != 0))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        printf("DELETE_ITEMS() DESCRIPTION:\n");
        printf("\tNo items left - FAILED!\n");
        free_data(&input);
        
        *testing_code = FAILED;
    }
}


// Nothing to delete
void no_delete(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/delete_02.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to delete
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    int32_t code = delete_items(&input, "LIPSTICK");

    if ((code) || (data_cmp(&input, &ideal) != SAME_DATA))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("DELETE_ITEMS() DESCRIPTION:\n");
        
        printf("\tNothing to delete - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Trivial deletion 
void trivial_delete(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/delete_03.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to delete
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    int32_t code = delete_items(&input, "LIPSTICK");

    if ((code) || (data_cmp(&input, &ideal) != SAME_DATA))
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("DELETE_ITEMS() DESCRIPTION:\n");
        
        printf("\tTrivial deletion - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}
