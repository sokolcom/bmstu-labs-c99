#include <stdio.h>
#include <stdint.h>

#include "../include/define.h"
#include "../include/work_mode.h"
#include "../include/testing.h"



int32_t mult_one(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/mult_one.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = multiply(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "41 1  3 1  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "multiply by 1\n");

    fclose(input_stream);

    return test_idx;
}


int32_t trivial_m12n(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/trivial_m12n.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = multiply(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "23 1  5 1  3 2  2 2  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "trivial multiplication\n");

    fclose(input_stream);

    return test_idx;
}