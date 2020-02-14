#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../include/define.h"
#include "../include/tokens.h"



// Read users input (operating mode)
int32_t get_token(FILE *const input_stream, FILE *const output_stream)
{
    char str_token[MAX_STR_LENGTH];

    // fprintf(output_stream, "Enter operating mode:\n<out, mul, sqr, div>\n");
    fscanf(input_stream, "%s", str_token);

    if (!strcmp(str_token, OUTPUT))
    {
        return TOKEN_OUT;
    }
    else if (!strcmp(str_token, MULTIPLICATION))
    {
        return TOKEN_MUL;
    }
    else if (!strcmp(str_token, SQUARE))
    {
        return TOKEN_SQR;   
    }
    else if (!strcmp(str_token, DIVIDE))
    {
        return TOKEN_DIV;
    }
    
    return UNKNOWN_TOKEN;
}
