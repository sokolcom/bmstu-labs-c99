#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/list_interface.h"



// Push another prime multiplier & its power
int32_t push_node(node_t **const head, const int32_t base, const int32_t power)
{
    node_t *temp = calloc(1, sizeof(node_t));

    if (!temp)
    {
        return ALLOC_NODE_ERROR;
    }

    temp->next = *head;
    temp->base = base;  // prime multiplier
    temp->power = power;  // power of the number
    *head = temp;

    return SUCCESS;
}


// Output entered (or computed) number in specified format <base power>
void print_list(FILE *const output_stream, const node_t *head)
{
    while (head)
    {
        fprintf(output_stream, "%" PRId32 " ", head->base);
        fprintf(output_stream, "%" PRId32 "  ", head->power);
        head = head->next;
    }    

    // End of output (lab task) && print empty list
    fprintf(output_stream, "1\n");
}


// Free linked list 
void free_list(node_t *head)
{
    node_t *temp_node = NULL;

    while (head)
    {
        temp_node = head->next;
        free(head);
        head = temp_node;
    }
}


// Get number which is factorized into the given list
int32_t get_number(const node_t *factorized)
{
    int32_t number = 1;
    int32_t prime_m8r = 1; // prime multiplier

    while (factorized)
    {   
        for (int power = 0; power < factorized->power; power++)
        {
            prime_m8r *= factorized->base;
        }

        number *= (prime_m8r);
        prime_m8r = 1;

        factorized = factorized->next;
    }

    return number;
}


// Copy-paste one factorized number to another with reversed multipliers
int32_t reverse_copy(const node_t *src, node_t **const result)
{
    while (src)
    {
        if (!push_node(result, src->base, src->power))
        {
            src = src->next;
        }
        else
        {
            return ALLOC_NODE_ERROR;
        }
    }

    return SUCCESS;
}
