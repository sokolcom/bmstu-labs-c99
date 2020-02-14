#include <stdio.h>
#include <stdint.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/sorts.h"

#include "../include/auxiliary.h"
#include "../include/tokens_test.h"



// Reading article token
void article_token(int32_t *const testing_code)
{
    freopen("./tests/module_testing/token_01.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);

    int32_t token = get_sort_token();
    if (token != TOKEN_ARTICLE)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        printf("GET_SORT_TOKEN() DESCRIPTION:\n");
        printf("\tArticle token - FAILED!\n");
        
        *testing_code = FAILED;
    }
}


// Reading article token
void name_token(int32_t *const testing_code)
{
    freopen("./tests/module_testing/token_02.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);

    int32_t token = get_sort_token();
    if (token != TOKEN_NAME)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("GET_SORT_TOKEN() DESCRIPTION:\n");
        
        printf("\tName token - FAILED!\n");
        
        *testing_code = FAILED;
    }
}


// Reading name token
void amount_token(int32_t *const testing_code)
{
    freopen("./tests/module_testing/token_03.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);

    int32_t token = get_sort_token();
    if (token != TOKEN_COUNT)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("GET_SORT_TOKEN() DESCRIPTION:\n");
        
        printf("\tAmount token - FAILED!\n");
        
        *testing_code = FAILED;
    }
}


// Reading amount token
void unknown_token(int32_t *const testing_code)
{
    freopen("./tests/module_testing/token_04.txt", "r", stdin);
    freopen("./tests/module_testing/program_output.txt", "w", stdout);

    int32_t token = get_sort_token();
    if (token != UNKNOWN_TOKEN)
    {
        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);
        if (*testing_code != FAILED)
            printf("GET_SORT_TOKEN() DESCRIPTION:\n");
        
        printf("\tUnknown token - FAILED!\n");
        
        *testing_code = FAILED;
    }
}
