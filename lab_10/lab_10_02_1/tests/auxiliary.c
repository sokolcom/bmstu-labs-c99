// File contains auxiliary functions for the testing 
// (e.g. data_cmp)
#include <stdint.h>
#include <string.h>

#include "../include/struct.h"
#include "../include/define.h"
#include "../include/auxiliary.h"



// Compare two stocks item by item
int32_t data_cmp(const stock_t *const input, const stock_t *const ideal)
{
    if (input->quantity != ideal->quantity)
    {
        return DIFFERENT_DATA;
    }

    for (int32_t item = 0; item < input->quantity; item++)
    {
        if (strcmp(input->stock[item].article, ideal->stock[item].article))
        {
            return DIFFERENT_DATA;
        }

        if (strcmp(input->stock[item].name, ideal->stock[item].name))
        {
            return DIFFERENT_DATA;
        }

        if (input->stock[item].amount != ideal->stock[item].amount)
        {
            return DIFFERENT_DATA;
        }
    }

    return SAME_DATA;
}
