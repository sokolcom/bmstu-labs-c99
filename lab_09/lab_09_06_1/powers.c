#include <stdio.h>
#include <stdint.h>  // int64_t
#include <inttypes.h>  // for scanf() int64_t

#include "powers.h"

#define SUCCESS 0
#define POWER_INPUT_ERROR 100
#define POWER_VALUE_ERROR 101

#define VAR_INPUT 1  // scanf() successfully read 1 variable


 
// Inputting powers
int input_powers(int64_t *const rho, int64_t *const gamma)
{
    printf("Enter power RHO (matrix A): ");
    int code = scanf("%" SCNd64, rho);
    if (code != VAR_INPUT)
        return POWER_INPUT_ERROR;

    code = check_power(rho);
    if (code)
        return code;

    printf("Enter power GAMMA (matrix B): ");
    code = scanf("%" SCNd64, gamma);
    if (code != VAR_INPUT)
        return POWER_INPUT_ERROR;

    code = check_power(gamma);
    if (code)
        return code;

    return SUCCESS;
}


// Checking if power valid or nah
int check_power(const int64_t *const power)
{
    if (*power >= 0)
        return SUCCESS;

    return POWER_VALUE_ERROR;
}
