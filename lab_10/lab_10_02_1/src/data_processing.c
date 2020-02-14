#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>  // memory alloc testing
#include <string.h>  // strcmp()
#include <ctype.h>  // isupper() & isalpha()

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/data_processing.h"



// Allocate memory for the stock
int32_t stock_alloc(stock_t *const items_array)
{
    items_array->stock = (item_t *)realloc(items_array->stock, (items_array->quantity + 1) * sizeof(item_t));
    if (!(items_array->stock))
    {
        return ALLOC_ERROR;
    }

    items_array->stock[items_array->quantity].article = calloc(MAX_STR_LEN, sizeof(char));
    if (!(items_array->stock[items_array->quantity].article))
    {
        free_data(items_array);
        return ALLOC_ERROR;
    }

    items_array->stock[items_array->quantity].name = calloc(MAX_STR_LEN, sizeof(char));
    if (!(items_array->stock[items_array->quantity].name))
    {
        free(items_array->stock[items_array->quantity].article);

        free_data(items_array);
        return ALLOC_ERROR;            
    }

    return SUCCESS;
}


// Check if we stop input or not
int32_t check_stop_input(const char *string, const char *const str_cmp)
{
    char *temp_string = (char *)calloc(MAX_STR_LEN, sizeof(char));

    int32_t length = 0;
    while (*string)
    {
        if (isupper(*string))
        {
            *temp_string = *string + CHANGE_CASE;
        }
        else
        {
            *temp_string = *string;
        }
        
        temp_string++;
        string++; 
        length++;
    }

    // Return pointer back
    while (length)
    {
        temp_string--;
        length--;
    }

    if (strcmp(temp_string, str_cmp) == SAME_STR)
    {   
        free(temp_string);
        return ABORT_INPUT;
    }

    free(temp_string);
    return CONTINUE_INPUT;
}


// Article - latin letters in uppercase
int32_t check_article(const char *string)
{
    while (*string)
    {
        if (!(isalpha(*string)) || !(isupper(*string)))
        {
            return FAILED;
        }

        string++;
    }

    return PASSED;
}


// Name - latin letters in lower(upper)case
int32_t check_name(const char *string)
{
    while (*string)
    {
        if (!(isalpha(*string)))
        {
            return FAILED;
        }

        string++;
    }

    return PASSED;
}


// Amount is an integer >= 0
int32_t check_amount(const int32_t number)
{
    if (number < 0)
        return FAILED;
    
    return PASSED;
}


// Enter stock dataset
int32_t input_products(stock_t *const items_array, ...)
{
    items_array->stock = NULL;
    items_array->quantity = 0;

// To simulate memory allocation error in testing
#ifdef _MODULE_TESTING_
    va_list arg;
    va_start(arg, items_array);
    int32_t memory_flag = va_arg(arg, int32_t);
    va_end(arg);

    if (memory_flag)
    {
        return ALLOC_ERROR;  
    }
#endif

    int32_t code;

    char abort_input[] = "nothing";  // if entered "nothing" then stop input
    int32_t input_flag = INPUT_OK;

    fprintf(stdout, "Enter items (<article> <name> <quantity>):\n");

    while (input_flag)
    {
        code = stock_alloc(items_array);
        if (code)
        {
            return ALLOC_ERROR;
        }
        
        fscanf(stdin, "%s", items_array->stock[items_array->quantity].article);
        if (check_stop_input(items_array->stock[items_array->quantity].article, abort_input))
        {
            // Check if article valid
            if (!check_article(items_array->stock[items_array->quantity].article))
            {
                free(items_array->stock[items_array->quantity].article);
                free(items_array->stock[items_array->quantity].name);
                free_data(items_array);
                return INPUT_ERROR;
            }

            // Check if item's name valid
            fscanf(stdin, "%s", items_array->stock[items_array->quantity].name);
            if (!check_name(items_array->stock[items_array->quantity].name))
            {
                free(items_array->stock[items_array->quantity].article);
                free(items_array->stock[items_array->quantity].name);
                free_data(items_array);
                return INPUT_ERROR;
            }

            // Check if item's quantity valid
            code = fscanf(stdin, "%" SCNd32, &(items_array->stock[items_array->quantity].amount));
            if (!(code) || (!check_amount(items_array->stock[items_array->quantity].amount)))
            {
                free(items_array->stock[items_array->quantity].article);
                free(items_array->stock[items_array->quantity].name);
                free_data(items_array);
                return INPUT_ERROR;
            }

            (items_array->quantity)++;
        }
        else
        {
            input_flag = INPUT_STOP;
        }
    }

    free(items_array->stock[items_array->quantity].article);
    free(items_array->stock[items_array->quantity].name);

    // Check for the empty array
    if (items_array->quantity == 0)
    {
        free(items_array->stock);
        return INPUT_ERROR;
    }

    return SUCCESS;
}


// Add to each item's article its name in uppercase
void configure_articles(stock_t *const items_array)
{
    int32_t length_article, length_name; // to return pointers back

    for (int32_t item = 0; item < items_array->quantity; item++)
    {
        length_article = 0;
        length_name = 0;

        // skip article letters
        while (*(items_array->stock[item].article)++)
        {
            length_article++;
        }
        items_array->stock[item].article--; 

        while (*(items_array->stock[item].name))
        {
            if (islower(*(items_array->stock[item].name)))
            {
                *(items_array->stock[item].article) = *(items_array->stock[item].name) - CHANGE_CASE;
            }
            else
            {
                *(items_array->stock[item].article) = *(items_array->stock[item].name);
            }


            (items_array->stock[item].article)++;
            (items_array->stock[item].name)++;
            length_article++;
            length_name++;
        }

        // Return pointers of strings back to the beginning
        while (length_article)
        {
            items_array->stock[item].article--;
            length_article--;
        }

        while (length_name)
        {
            items_array->stock[item].name--;
            length_name--;
        }
#ifdef _TESTING_
        printf("CONFIGURE_ARTICLES(), new article, name:\n");
        printf("%s, %s\n", items_array->stock[item].article, items_array->stock[item].name);
#endif
    }
}


// Delete items with specified article which are not in stock (amount = 0)
int32_t delete_items(stock_t *const items_array, const char *const spec_article)
{
    int32_t item = items_array->quantity;

    while (item--)
    {
        if ((strcmp(items_array->stock[item].article, spec_article) == SAME_STR) &&
            (!(items_array->stock[item].amount)))
        {
            free(items_array->stock[item].article);
            free(items_array->stock[item].name);

            for (int32_t i = item; i < items_array->quantity - 1; i++)
            {
                items_array->stock[i] = items_array->stock[i + 1];
            }

            (items_array->quantity)--;

#ifdef _TESTING_
            printf("DELETE_ITEMS(), after another delete:\n");
            for (int32_t item = 0; item < items_array->quantity; item++)
            {
                printf("%s  ", items_array->stock[item].article);
                printf("%s  ", items_array->stock[item].name);
                printf("%" PRId32 "\n", items_array->stock[item].amount);
            }

            printf("QUANTITY: %d\n", items_array->quantity);
#endif
        }
    }

    items_array->stock = (item_t *)realloc(items_array->stock, items_array->quantity * sizeof(item_t));
    if (!(items_array->stock))
    {
        return DELETE_ERROR;
    }

    return SUCCESS;
}


// Free all data in dynamic array of items
void free_data(const stock_t *const items_array)
{
    for (int32_t item = 0; item < items_array->quantity; item++)
    {
        free(items_array->stock[item].article);
        free(items_array->stock[item].name);
    }

    free(items_array->stock);
}


// Print data into given file
// return `OUT_STREAM_ERROR` if error occured, otherwise SUCCESS
int32_t print_data(const char *const filename, const stock_t *const items_array)
{
    FILE* output_stream = fopen(filename, "w");
    if (!output_stream)
    {
        return OUT_STREAM_ERROR;
    }

    for (int32_t item = 0; item < items_array->quantity; item++)
    {
        fprintf(output_stream, "%s\n", items_array->stock[item].article);
        fprintf(output_stream, "%s\n", items_array->stock[item].name);
        fprintf(output_stream, "%" PRId32 "\n", items_array->stock[item].amount);
    }

    fclose(output_stream);

    return SUCCESS;
}
