#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/my_snprintf_testing.h"



int32_t my_snprintf_testing()
{
    int32_t testing_code = PASSED;

    // N equals zero testing
    n_zero(&testing_code);

    // N is less than hole output (shrink output)
    n_less_length(&testing_code);

    // N is big enough to contain output (no shrink)
    n_more_length(&testing_code);

    // No specifiers
    specifier_absence(&testing_code);

    // %c
    c_specifier(&testing_code);

    // %x
    x_specifier(&testing_code);

    // %hx
    hx_specifier(&testing_code);

    // %o
    o_specifier(&testing_code);

    // %ho
    ho_specifier(&testing_code);

    // Trivial testing (different specifiers in one string)
    trivial_snprintf(&testing_code);

    return testing_code;
}


int main()
{
    printf("\nPAY ATTENTION PLEASE!\nLook for the module testing results in "
        "the ./module_testing/testing_results.txt\n");

    // Here will be the description of the failed testing
    freopen("./tests/module_testing/fail_desc.txt", "w", stdout);

    int32_t code = my_snprintf_testing();

    // Testing results:
    freopen("./tests/module_testing/testing_results.txt", "w", stdout);
    printf("TESTING my_snprintf():\t");
    if (code != PASSED)
    {
        printf("FAILED!\n");
        printf("\nFor the detailed information about failures look for the fail_desc.txt!\n");
        return TESTING_FAILURE;
    }
    else
        printf("PASSED!\n");

    return TESTING_SUCCESS;
}
