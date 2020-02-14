#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/sorts.h"



// Getting from the user sorting token: by which criteria sort data?
int32_t get_sort_token()
{
    int32_t token;
    char user_input[MAX_STR_LEN];

    fprintf(stdout, "Enter sorting key: "); 
    fscanf(stdin, "%s", user_input);

    if (strcmp(ARTICLE, user_input) == SAME_STR)
    {
        token = TOKEN_ARTICLE;
    }
    else if (strcmp(NAME, user_input) == SAME_STR)
    {
        token = TOKEN_NAME;
    }
    else if (strcmp(COUNT, user_input) == SAME_STR)
    {
        token = TOKEN_COUNT;
    }
    else
    {
        token = UNKNOWN_TOKEN;
    }

    return token;
}

// Swap elements
void swap_items(stock_t *const goods, const int32_t i, const int32_t j)
{
    item_t temp = goods->stock[i];
    goods->stock[i] = goods->stock[j];
    goods->stock[j] = temp;
}


// `Article` comparartor function
int32_t article_cmp(const item_t product_1, const item_t product_2)
{
    return -strcmp(product_2.article, product_1.article);  
}


// `Item name` comparator function
int32_t name_cmp(const item_t product_1, const item_t product_2)
{
    return -strcmp(product_2.name, product_1.name);  
}


// `Amount of the item on the stock` comparator function
int32_t count_cmp(const item_t product_1, const item_t product_2)
{
    if (product_1.amount > product_2.amount)
    {
        return FIRST_ARG;
    }
    else if (product_1.amount < product_2.amount)
    {
        return SECOND_ARG;
    }

    return EQUAL_ARG;
}


// Stable sorting (Cocktail sort)
void cocktail_sort(stock_t *const goods, int32_t (*compare)(const item_t product_1, const item_t product_2))
{
    // Limits of the unsorted array
    int32_t left_limit = 0, right_limit = goods->quantity - 1;
    
    // Is array sorted?
    int32_t swap_flag = NOT_SORTED;

    while ((left_limit < right_limit) && (swap_flag == NOT_SORTED))
    {
        swap_flag = SORTED;

        for (int32_t i = left_limit; i < right_limit; i++)
        {
            if (compare(goods->stock[i], goods->stock[i + 1]) > 0)
            {
                swap_items(goods, i, i + 1);
                swap_flag = NOT_SORTED;
            }
        }
        right_limit--;

        for (int32_t i = right_limit; i > left_limit; i--)
        {
            if (compare(goods->stock[i], goods->stock[i - 1]) < 0)
            {
                swap_items(goods, i, i - 1);
                swap_flag = NOT_SORTED;
            }
        }
        left_limit++;
    }
}
