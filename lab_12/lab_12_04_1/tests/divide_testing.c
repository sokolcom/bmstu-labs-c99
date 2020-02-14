#include <stdio.h>
#include <stdint.h>

#include "../include/define.h"
#include "../include/work_mode.h"
#include "../include/testing.h"



int32_t zero_quotient(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/zero_quot.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = divide(input_stream, output_stream);
    fclose(output_stream);

    if (code)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "dividend < divisor\n");

    fclose(input_stream);

    return test_idx;
}


int32_t divisor_one(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/divisor_one.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = divide(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "5 2  2 2  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "divide by 1\n");

    fclose(input_stream);

    return test_idx;
}


int32_t trivial_div(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/trivial_div.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = divide(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "1543 1  2 2  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "trivial divison\n");

    fclose(input_stream);

    return test_idx;
}