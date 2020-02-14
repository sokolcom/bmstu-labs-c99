#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdint.h>

// Item on the stock
typedef struct
{
    char *article;
    char *name;
    int32_t amount;
} item_t;


// Array of items
typedef struct
{
    item_t *stock;  // dynamic array of items
    int32_t quantity;  // length of the array
} stock_t;


// Testing indicator 
//   fail - any of test have failed
//   done - testing successfully passed
typedef enum
{
    fail = 0,
    done
} test_flag_t;

#endif
