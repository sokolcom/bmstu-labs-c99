// Auxiliary functions to my_snprintf()
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/auxiliary.h"



// Print ordinary symbol (not specified by "%")
void print_symbols(const char **const str_format, bstate_t *const buffer_state)
{
    while ((**str_format != '%') && (**str_format != '\0'))
    {
        if (buffer_state->n_max > buffer_state->n_real)
        {
            *(buffer_state->buffer)++ = **str_format;
        }

        buffer_state->n_real++; 
        (*str_format)++;
    }

    // Check if we face specifier (not end of line)
    if (**str_format == '%')
    {
        (*str_format)++;
    }
}


// Swap two symbols
void swap_symbols(char *const element_1, char *const element_2)
{
    char temp = *element_1;
    *element_1 = *element_2;
    *element_2 = temp;
}


// Reverse string (when changing base: decimal --> octal/hexadecimal)
void reverse_string(char *const start, char *const end)
{
    for (char *symbol = start; symbol < start + (end - start) / 2 ; symbol++)
    {
        swap_symbols(symbol, end - (symbol - start) - 1);
    }
}


// Process yet another specifier 
void get_specifier(va_list *const args, const char **const str_format, bstate_t *const buffer_state)
{
    char cvalue;  // %c
    uint32_t uvalue = 0;  // %o, %x

    // %c specifier
    if (**str_format == 'c')
    {
        cvalue = va_arg(*args, int32_t);

        if (buffer_state->n_max > buffer_state->n_real)
        {
            *(buffer_state->buffer)++ = cvalue;
        }

        buffer_state->n_real++;
        (*str_format)++;
    }
    // %o specifier
    else if (**str_format == 'o')
    {
        uvalue = va_arg(*args, uint32_t);
        octal_number(uvalue, buffer_state);
        (*str_format)++; 
    }
    // %x specifier
    else if (**str_format == 'x')
    {
        uvalue = va_arg(*args, uint32_t);
        hex_number(uvalue, buffer_state);
        (*str_format)++;
    }
    // %h* modifier
    else if (**str_format == 'h')
    {
        (*str_format)++;
        h_modifier(args, str_format, buffer_state);
    }
}


// %h* modifier was found
void h_modifier(va_list *const args, const char **const str_format, bstate_t *const buffer_state)
{
    uint16_t number = 0;

    if (**str_format == 'o')
    {
        number = va_arg(*args, uint32_t);

        octal_number(number, buffer_state);
        (*str_format)++;
    }

    if (**str_format == 'x')
    {
        number = va_arg(*args, uint32_t);
        
        hex_number(number, buffer_state);
        (*str_format)++;
    }
}


// Decimal into octal (%o & %ho)
void octal_number(uint32_t value, bstate_t *const buffer_state)
{
    char *oct_buffer = (char *)calloc(OCT_MAX_LENGTH, sizeof(char));
    int32_t index = 0;

    char *start = oct_buffer;

    // If 0 entered (cause cycle will be skipped)
    if (!value)
    {
        oct_buffer[index++] = ENCODE_OFFSET;  
    }

    while (value)   
    {
        oct_buffer[index++] = (value % BASE_8) + ENCODE_OFFSET;
        value /= BASE_8; 
    }
    char *end = oct_buffer + index;

    reverse_string(start, end);

    for (int32_t i = 0; i < index; i++)
    {
        // Is there place to print symbol
        if (buffer_state->n_max > buffer_state->n_real)
        {
            *(buffer_state->buffer)++ = oct_buffer[i];
        }
        buffer_state->n_real++;
    }

    free(oct_buffer);
}


// Decimal into hexadecimal (%x & %hx)
void hex_number(uint32_t value, bstate_t *const buffer_state)
{
    char hexadecimal_digits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

    char *hex_buffer = (char *)calloc(HEX_MAX_LENGTH, sizeof(char));
    int32_t index = 0;

    char *start = hex_buffer;

    // If 0 entered (cause cycle will be skipped)
    if (!value)
    {
        hex_buffer[index++] = hexadecimal_digits[0];  
    }

    while (value)   
    {
        hex_buffer[index++] = hexadecimal_digits[value % BASE_16];
        value /= BASE_16; 
    }
    char *end = hex_buffer + index;

    reverse_string(start, end);

    for (int32_t i = 0; i < index; i++)
    {
        // Is there place to print symbol
        if (buffer_state->n_max > buffer_state->n_real)
        {
            *(buffer_state->buffer)++ = hex_buffer[i];
        }
        buffer_state->n_real++;
    }

    free(hex_buffer);
}


// Print into the string
int32_t print_string(char *str_out, char *copy_out, bstate_t *const buffer_state)
{
    if (buffer_state->n_max == 0)
    {
        free(copy_out);
        return buffer_state->n_real;
    }

    if (buffer_state->n_real < buffer_state->n_max)
    {
        *(buffer_state->buffer) = '\0';
    }
    else
    {
        copy_out[buffer_state->n_max - 1] = '\0';
    }

    strcpy(str_out, copy_out);
    free(copy_out);
    return buffer_state->n_real;
}
