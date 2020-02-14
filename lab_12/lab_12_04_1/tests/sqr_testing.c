#include <stdio.h>
#include <stdint.h>

#include "../include/define.h"
#include "../include/work_mode.h"
#include "../include/testing.h"



int32_t sqr_one(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/sqr_one.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = square_number(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "square 1\n");

    fclose(input_stream);

    return test_idx;
}


int32_t trivial_sqr(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/trivial_sqr.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = square_number(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "3 4  2 4  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "trivial squaring\n");

    fclose(input_stream);

    return test_idx;
}
