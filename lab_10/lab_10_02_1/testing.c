#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/data_proc_test.h"
#include "include/sorts_test.h"
#include "include/tokens_test.h"



// Inputing products testing
int32_t input_products_testing()
{
    int32_t testing_code = PASSED;

    // Allocation failed
    alloc_fail(&testing_code);

    // No items entered (`nothing` entered)
    no_items(&testing_code);
    
    // Invalid article (in lowercase)
    article_lowercase(&testing_code);
    
    // Invalid article (contains numbers) 
    article_numbers(&testing_code);

    // Invalid name (contains numbers)
    name_numbers(&testing_code);

    // Invalid amount (negative number)
    amount_negative(&testing_code);

    // "nothing" entered in different (e.g. 'noTHiNG`)
    strange_stop(&testing_code);

    // Trivial input
    trivial_input(&testing_code);

    return testing_code;
}


// Configurating articles (adding name in UPPERCASE) testing
int32_t config_articles_testing()
{
    int32_t testing_code = PASSED;

    // All name's letters in lowercase
    lowercase_name(&testing_code);

    // All name's letters in UPPERCASE
    uppercase_name(&testing_code);

    // All name's letters in lowercase & UPPERCASE
    allcase_name(&testing_code);

    return testing_code;
}


// Deleting items from the array testing
int32_t delete_items_testing()
{
    int32_t testing_code = PASSED;

    // After delete no items left
    empty_delete(&testing_code);

    // Nothing to delete 
    no_delete(&testing_code);
    
    // Trivial deletion
    trivial_delete(&testing_code);

    return testing_code;
}


// Getting sorting token testing
int32_t tokens_testing()
{
    int32_t testing_code = PASSED;

    // Sort by article token
    article_token(&testing_code);

    // Sort by name token
    name_token(&testing_code);
    
    // Sort by amount token
    amount_token(&testing_code);
    
    // Unknown token entered
    unknown_token(&testing_code);

    return testing_code;
}


// Cocktail sort testing
int32_t sort_testing()
{
    int32_t testing_code = PASSED;

    // Array contains one item
    one_item_sort(&testing_code);

    // Sort by item's articles
    sort_article(&testing_code);
    
    // Sort by item's name
    sort_name(&testing_code);
    
    // Sort by item's amount on the stock
    sort_amount(&testing_code);

    return testing_code;
}


int main()
{
    printf("\nPAY ATTENTION PLEASE!\nLook for the module testing results in the ./module_testing/testing_results.txt\n");

    int32_t code;
    test_flag_t flag = done;  // if any of tests failed flag will be `fail`

    // Here will be the description of the failed testing
    freopen("./tests/module_testing/fail_desc.txt", "w", stdout);

    // Inputing data
    freopen("./tests/module_testing/program_output.txt", "w", stdout);  // program prints will be there
    code = input_products_testing();
    freopen("./tests/module_testing/testing_results.txt", "w", stdout);
    printf("TESTING input_products():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");
    
    // Configurating articles 
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    code = config_articles_testing();
    freopen("./tests/module_testing/testing_results.txt", "a", stdout);
    printf("TESTING config_articles():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");

    // Deleting items
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    code = delete_items_testing();
    freopen("./tests/module_testing/testing_results.txt", "a", stdout);
    printf("TESTING delete_items():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");

    // Sorting tokens
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    code = tokens_testing();
    freopen("./tests/module_testing/testing_results.txt", "a", stdout);
    printf("TESTING get_sort_token():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        flag = fail;
    }
    else
        printf("PASSED!\n");

    // Sorting
    freopen("./tests/module_testing/program_output.txt", "w", stdout);
    code = sort_testing();
    freopen("./tests/module_testing/testing_results.txt", "a", stdout);
    printf("TESTING cocktail_sort():\t");
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
