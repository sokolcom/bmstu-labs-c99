#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/data_processing.h"
#include "include/sorts.h"


int main()
{
    int32_t code;
    stock_t items_array;

    // Enter array of items
    code = input_products(&items_array);
    if (code)
    {
        fprintf(stdout, "Error!\nInput data failed!\n\n\n");
        return code;
    }

#ifdef _TESTING_
    printf("\n\n***AFTER INPUT:\n");
    for (int32_t item = 0; item < items_array.quantity; item++)
    {
        printf("%s  ", items_array.stock[item].article);
        printf("%s  ", items_array.stock[item].name);
        printf("%" PRId32 "\n", items_array.stock[item].amount);
    }

    printf("QUANTITY: %d\n\n", items_array.quantity);
#endif

    // Add to each item's article its name in uppercase
    configure_articles(&items_array);

#ifdef _TESTING_
    printf("\n\n***AFTER CONFIG ARTICLES:\n");
    for (int32_t item = 0; item < items_array.quantity; item++)
    {
        printf("%s  ", items_array.stock[item].article);
        printf("%s  ", items_array.stock[item].name);
        printf("%" PRId32 "\n", items_array.stock[item].amount);
    }

    printf("QUANTITY: %d\n\n", items_array.quantity);
#endif

    // Delete items with given article (lab task: "LIPSTICK")
    char spec_article[] = "LIPSTICK";
    code = delete_items(&items_array, spec_article);
    if (code)
    {
        fprintf(stdout, "Error!\nDelete data failed!\n\n\n");
        return code;
    }

#ifdef _TESTING_
    printf("\n\n***AFTER DELETE:\n");
    for (int32_t item = 0; item < items_array.quantity; item++)
    {
        printf("%s  ", items_array.stock[item].article);
        printf("%s  ", items_array.stock[item].name);
        printf("%" PRId32 "\n", items_array.stock[item].amount);
    }

    printf("QUANTITY: %d\n\n", items_array.quantity);
#endif

    // Sort data by entered type
    int32_t sort_token = get_sort_token();
    if (sort_token == TOKEN_ARTICLE)
    {
        cocktail_sort(&items_array, article_cmp);
    }
    else if (sort_token == TOKEN_NAME)
    {
        cocktail_sort(&items_array, name_cmp);
    }
    else if (sort_token == TOKEN_COUNT)
    {
        cocktail_sort(&items_array, count_cmp);
    }
    else
    {
        free_data(&items_array);

        fprintf(stdout, "Error!\nUnknown key entered!\n\n");
        return TOKEN_ERROR;
    }

    // Print processed data into given file (lab task: "stockpile.txt")
    char output_filename[] = "stockpile.txt";
    code = print_data(output_filename, &items_array);
    if (code)
    {
        free_data(&items_array);

        fprintf(stdout, "Error!\nUnable to open the file!\n\n");
        return code;
    }

    free_data(&items_array);
    
    return SUCCESS;
}
