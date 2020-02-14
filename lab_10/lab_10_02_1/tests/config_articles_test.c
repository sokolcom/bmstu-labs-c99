#include <stdio.h>
#include <stdint.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/data_processing.h"

#include "../include/auxiliary.h"
#include "../include/data_proc_test.h"



// Letters in lowercase testing
void lowercase_name(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/config_01.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to config
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    configure_articles(&input);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        printf("CONFIG_ARTICLES() DESCRIPTION:\n");
        printf("\tlowercase - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Letters in UPPERCASE testing
void uppercase_name(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/config_02.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to config
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    configure_articles(&input);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("CONFIG_ARTICLES() DESCRIPTION:\n");
        
        printf("\tUPPERCASE - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Letters in lowercase & UPPERCASE testing
void allcase_name(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/config_03.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to config
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    configure_articles(&input);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("CONFIG_ARTICLES() DESCRIPTION:\n");
        
        printf("\tUPPERCASE & lowercase - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}
