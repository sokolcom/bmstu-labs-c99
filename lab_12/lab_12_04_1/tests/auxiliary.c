#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../include/define.h"
#include "../include/testing.h"


int32_t check_result(const char *const filename, const char *const str)
{
    char src_str[MAX_STR_LENGTH];
    int32_t index = 0;
    char temp_symbol = ' ';

    FILE* stream = fopen(filename, "r");

    // Skip info print
    while (temp_symbol != '\n')
    {
        fread(&temp_symbol, sizeof(char), 1, stream);
    }

    while (!feof(stream))
    {
        fread(&temp_symbol, sizeof(char), 1, stream);
        src_str[index++] = temp_symbol;
    }
    src_str[--index] = '\0';
    src_str[--index] = '\0';

    fclose(stream);

    if (!strcmp(str, src_str))
    {
        return CORRECT_RESULT;
    }

    return INCORRECT_RESULT;
}
