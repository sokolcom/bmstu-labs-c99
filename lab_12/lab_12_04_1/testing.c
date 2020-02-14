// TAP testing (test anything protocol)
#include <stdio.h>
#include <stdint.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/testing.h"



// Token testing
int32_t token_testing(int32_t *const test_idx)
{
    int32_t testing_code = PASSED;

    // Output token
    *test_idx = out_token(&testing_code, *test_idx);

    // Multiplication token
    *test_idx = mul_token(&testing_code, *test_idx);
    
    // Squaring token
    *test_idx = sqr_token(&testing_code, *test_idx);
    
    // Dividing token
    *test_idx = div_token(&testing_code, *test_idx);

    // Unknown token entered
    *test_idx = unknown_token(&testing_code, *test_idx);

    return testing_code;
}


// Outputing number testing
int32_t output_testing(int32_t *const test_idx)
{
    int32_t testing_code = PASSED;

    // Symbols (not a numbers) entered
    *test_idx = non_number(&testing_code, *test_idx);

    // Negative number entered
    *test_idx = negative_input(&testing_code, *test_idx);

    // `0` entered
    *test_idx = zero_input(&testing_code, *test_idx);
    
    // `1` entered
    *test_idx = one_input(&testing_code, *test_idx);

    // Trivial input 
    *test_idx = trivial_input(&testing_code, *test_idx);

    return testing_code;
}


// Multiplication testing
int32_t m12n_testing(int32_t *const test_idx)
{
    int32_t testing_code = PASSED;

    // Multiply by one 
    *test_idx = mult_one(&testing_code, *test_idx);

    // Trivial multiplication
    *test_idx = trivial_m12n(&testing_code, *test_idx);

    return testing_code;
}


// Squaring testing
int32_t sqr_testing(int32_t *const test_idx)
{
    int32_t testing_code = PASSED;

    // Squaring number 1
    *test_idx = sqr_one(&testing_code, *test_idx);
    
    // Trivial squaring
    *test_idx = trivial_sqr(&testing_code, *test_idx);

    return testing_code;
}


// Dividing testing
int32_t divide_testing(int32_t *const test_idx)
{
    int32_t testing_code = PASSED;

    // Dividend < divisor
    *test_idx = zero_quotient(&testing_code, *test_idx);

    // Divide by one (divisor = 1)
    *test_idx = divisor_one(&testing_code, *test_idx);
    
    // Trivial dividing
    *test_idx = trivial_div(&testing_code, *test_idx);

    return testing_code;
}


int main()
{
    int32_t code = 0;
    int32_t test_idx = 1, last_test_idx = TESTS_AMOUNT;

    fprintf(stdout, "%d..%d\n", test_idx, last_test_idx);

    // Tokens
    code += token_testing(&test_idx);

    // Outputing the number
    code += output_testing(&test_idx);
    
    // Multiplication  
    code += m12n_testing(&test_idx);

    // Squaring numbers
    code += sqr_testing(&test_idx);

    // Dividing numbers
    code += divide_testing(&test_idx);

    fprintf(stdout, "Testing finished\n");

    if (test_idx != TESTS_AMOUNT + 1)
    {
        return TESTING_FAILURE;
    }

    return TESTING_SUCCESS;
}
