#include <stdio.h>
#include <stdint.h>

#include "../include/define.h"
#include "../include/tokens.h"
#include "../include/testing.h"



int32_t out_token(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/out_token.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    if (get_token(input_stream, output_stream) == TOKEN_OUT)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "reading 'out' token\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t mul_token(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/mul_token.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    if (get_token(input_stream, output_stream) == TOKEN_MUL)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "reading 'mul' token\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t sqr_token(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/sqr_token.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    if (get_token(input_stream, output_stream) == TOKEN_SQR)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "reading 'sqr' token\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t div_token(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/div_token.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    if (get_token(input_stream, output_stream) == TOKEN_DIV)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
    }

    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "reading 'div' token\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}


int32_t unknown_token(int32_t *const testing_code, int32_t test_idx)
{
    FILE* input_stream = fopen("tests/testing/unknown_token.txt", "r");
    FILE* output_stream = fopen("tests/testing/program_output.txt", "w");

    if (get_token(input_stream, output_stream) == UNKNOWN_TOKEN)
    {
        fprintf(stdout, "ok");
    }
    else
    {
        fprintf(stdout, "not ok");
    }
    
    fprintf(stdout, " %d\t", test_idx++);
    fprintf(stdout, "reading unknown token\n");

    fclose(input_stream);
    fclose(output_stream);

    return test_idx;
}
