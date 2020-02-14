#include <stdio.h>

#include "p_number.h"


#define SUCCESS 0
#define INDEX_INPUT_ERROR 100
#define INDEX_VALUE_ERROR 101

#define VAR_INPUT 1  // scanf() successfully read 1 variable



// Inputting index 'p'
int input_number(int *const p_index, const int size)
{
    printf("Enter index P position: ");
    int code = scanf("%d", p_index);
    if (code != VAR_INPUT)
        return INDEX_INPUT_ERROR;

    code = check_index(p_index, size);
    if (code)
        return code;

    return SUCCESS;
}


// Checking if index valid or nah
int check_index(const int *const index, const int size)
{
    if ((*index < size) && (*index >= 0))
        return SUCCESS;

    return INDEX_VALUE_ERROR;
}
