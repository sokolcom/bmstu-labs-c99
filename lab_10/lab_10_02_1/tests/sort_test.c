#include <stdio.h>
#include <stdint.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/data_processing.h"
#include "../include/sorts.h"

#include "../include/auxiliary.h"
#include "../include/sorts_test.h"



// Array contains one item
void one_item_sort(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/sorts_01.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to sort
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    cocktail_sort(&input, article_cmp);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        printf("COCKTAIL_SORT() DESCRIPTION:\n");
        printf("\tOne item array - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Sort by item's articles
void sort_article(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/sorts_02.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to sort
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    cocktail_sort(&input, article_cmp);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("COCKTAIL_SORT() DESCRIPTION:\n");
        
        printf("\tSort by articles - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Sort by item's name
void sort_name(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/sorts_03.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to sort
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    cocktail_sort(&input, name_cmp);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("COCKTAIL_SORT() DESCRIPTION:\n");
        
        printf("\tSort by names - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}


// Sort by item's amount on the stock
void sort_amount(int32_t *const testing_code)
{
    stock_t input, ideal;

    freopen("./tests/module_testing/sorts_04.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    input_products(&input, NORMAL_TEST);  // what to sort
    input_products(&ideal, NORMAL_TEST);  // with what to compare
    
    cocktail_sort(&input, count_cmp);

    if (data_cmp(&input, &ideal) != SAME_DATA)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("COCKTAIL_SORT() DESCRIPTION:\n");
        
        printf("\tSort by amount - FAILED!\n");
        
        *testing_code = FAILED;
    }

    free_data(&input);
    free_data(&ideal);
}
