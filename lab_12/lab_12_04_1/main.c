#include <stdio.h>
#include <stdint.h>

#include "include/define.h"
#include "include/tokens.h"
#include "include/work_mode.h"


int main()
{
    int32_t code;
    int32_t mode_token = get_token(stdin, stdout);

    if (mode_token == TOKEN_OUT)
    {
        code = output_number(stdin, stdout);
        if (code)
        {
            // fprintf(stdout, "Error occurred while outputing the number!\n");
            return code;
        }
    }
    else if (mode_token == TOKEN_MUL)
    {
        code = multiply(stdin, stdout);
        if (code)
        {
            // fprintf(stdout, "Error occurred while multiplicating numbers!\n");
            return code;
        }
    }
    else if (mode_token == TOKEN_SQR)
    {
        code = square_number(stdin, stdout);
        if (code)
        {
            // fprintf(stdout, "Error occurred while squaring the number!!\n");
            return code;
        }
    }
    else if (mode_token == TOKEN_DIV)
    {
        code = divide(stdin, stdout);
        if (code)
        {
            // fprintf(stdout, "Error occurred while dividing the number!\n");
            return code;
        }
    }
    else
    {
        // fprintf(stdout, "Error!\nUnknown token entered!\n");
        return TOKEN_ERROR;
    }

    return SUCCESS;
}
