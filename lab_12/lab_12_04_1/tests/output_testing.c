#include <stdio.h>
#include <stdint.h>

#include "../include/define.h"
#include "../include/work_mode.h"
#include "../include/testing.h"



int32_t non_number(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/non_number.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = output_number(input_stream, output_stream);
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
    fprintf(stdout, "outputing not a number\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t negative_input(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/negative_input.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = output_number(input_stream, output_stream);
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
    fprintf(stdout, "outputing negative number\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t zero_input(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/zero_input.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = output_number(input_stream, output_stream);
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
    fprintf(stdout, "outputing zero\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t one_input(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/one_input.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = output_number(input_stream, output_stream);
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
    fprintf(stdout, "outputing one\n");

    fclose(input_stream);

    return test_idx;
}


int32_t trivial_input(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/trivial_input.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    int32_t code = output_number(input_stream, output_stream);
    fclose(output_stream);

    if (!code && check_result("tests/testing/program_output.txt", "103 1  2 3  1"))
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
        *testing_code = FAILED;
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "trivial output\n");

    fclose(input_stream);

    return test_idx;
}
