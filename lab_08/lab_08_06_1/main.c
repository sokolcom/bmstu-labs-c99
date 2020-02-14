#include <stdio.h>
#include <stdlib.h>

#include "array_cdio.h"
#include "compute_mu.h"
#include "p_number.h"


// Return codes
#define SUCCESS 0
#define EMPTY_ERROR -10

// Consts
#define ADDITIONAL_ELEMS 3



int main()
{
    // User's input variables 
    int n = 0;
    int p = 0;

    double *array = NULL;  // Dynamic array
    double *trash_pointer = NULL;  // Just after the last element of the array
    
    // Array allocation
    int code = input_array(&array, &n, &trash_pointer);
    if (code)
    {
        printf("Error!\nInvalid input!\n");
        free(array);
        return code;
    }

    // Computing mu1 & delete 2 elems with the maximal difference with the mu1
    double mu1 = compute_mu1(array, trash_pointer);

    trash_pointer = delete_by_rule(array, trash_pointer, mu1, &n);
    if (n <= 0)
    {
        printf("Error!\nThe array turned out to be empty!\n");
        free(array);
        return EMPTY_ERROR;
    }

    // Computing mu2 & insert array
    double mu2 = compute_mu2(array, trash_pointer);

    array = extend_memory(&array, &trash_pointer, n, ADDITIONAL_ELEMS, &code);
    if (code)
    {
        printf("Error!\nMemory extension was rejected!\n");
        free(array);
        return code;
    }
    
    code = input_number(&p, n);
    if (code)
    {
        printf("Error!\nInvalid number P entered!\n");
        free(array);
        return code;
    }
    
    trash_pointer = insert_mu2(array, trash_pointer, mu2, (array + p));
    
    print_array(array, trash_pointer);
    
    free(array);
    
    return SUCCESS;
}
