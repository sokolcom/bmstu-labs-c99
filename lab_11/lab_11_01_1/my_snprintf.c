#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>


#include "include/define.h"
#include "include/struct.h"
#include "include/my_snprintf.h"
#include "include/auxiliary.h"



int32_t my_snprintf(char *str_out, size_t n, const char *str_format, ...)
{
    int32_t result_code;

    char *copy_out = (char *)calloc(n, sizeof(char));

    bstate_t buffer_state;
    buffer_state.buffer = copy_out;
    buffer_state.n_max = n;
    buffer_state.n_real = 0;

    va_list args;
    va_start(args, str_format);

    while (*str_format)
    {
        // Print symbols while we don't meet specifier or end of string
        print_symbols(&str_format, &buffer_state);

        // If "%" was found (not the end of string)
        if (*str_format)
        {
            get_specifier(&args, &str_format, &buffer_state);
        }
    }

    va_end(args);

    result_code = print_string(str_out, copy_out, &buffer_state);
    return result_code;
}
