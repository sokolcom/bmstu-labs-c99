#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "include/define.h"
#include "include/struct.h"
#include "include/my_snprintf.h"
#include "include/my_snprintf_testing.h"



// N is zero (nothing written)
void n_zero(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = 0;
    char format[] = "To be or no to be, that is the question";

    if (snprintf(output_1, size, format) != 
        my_snprintf(output_2, size, format))
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\tN = 0 - FAILED!\n");
    }
}


// N is less than hole output (shrink output)
void n_less_length(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "'The Gambler' by F.M. Dostoevsky is stunning";

    if (snprintf(output_1, size, format) == 
        my_snprintf(output_2, size, format))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\tN IS LESS THAN OUTPUT LENGTH - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\tN IS LESS THAN OUTPUT LENGTH - FAILED!\n");
    }
}


// N is big enough to contain output (no shrink)
void n_more_length(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "I wish you read 'Heart of a Dog'";

    if (snprintf(output_1, size, format) == 
        my_snprintf(output_2, size, format))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\tN IS BIGGER THAN OUTPUT LENGTH - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\tN IS BIGGER THAN OUTPUT LENGTH - FAILED!\n");
    }
}


// No specifiers testing
void specifier_absence(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "Why dont you read sci-fi?";

    if (snprintf(output_1, size, format) == 
        my_snprintf(output_2, size, format))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\tNO SPECIFIER testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\tNO SPECIFIER testing - FAILED!\n");
    }
}


// %c testing
void c_specifier(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "%c for the Vendetta";
    char symbol = 'V';

    if (snprintf(output_1, size, format, symbol) == 
        my_snprintf(output_2, size, format, symbol))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\t'%%c' testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\t'%%c' testing - FAILED!\n");
    }
}


// %x testing
void x_specifier(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "Fahrenheit %x is R. Bradbury's novel";
    uint32_t hex = 451;

    if (snprintf(output_1, size, format, hex) == 
        my_snprintf(output_2, size, format, hex))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\t'%%x' testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\t'%%x' testing - FAILED!\n");
    }
}


// %hx testing
void hx_specifier(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "%hx is G. Orwell's novel";
    uint16_t hex = 1984;

    if (snprintf(output_1, size, format, hex) == 
        my_snprintf(output_2, size, format, hex))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\t'%%hx' testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\t'%%hx' testing - FAILED!\n");
    }
}


// %o testing
void o_specifier(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "Fahrenheit %o is R. Bradbury's novel";
    uint32_t octal = 451;

    if (snprintf(output_1, size, format, octal) == 
        my_snprintf(output_2, size, format, octal))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\t'%%o' testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\t'%%o' testing - FAILED!\n");
    }
}


// %ho testing
void ho_specifier(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "%ho is G. Orwell's novel";
    uint16_t octal = 1984;

    if (snprintf(output_1, size, format, octal) == 
        my_snprintf(output_2, size, format, octal))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\t'%%ho' testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\t'%%ho' testing - FAILED!\n");
    }
}


// Trivial testing (different specifiers in one string)
void trivial_snprintf(int32_t *const testing_code)
{
    char output_1[OUTPUT_SIZE];
    char output_2[OUTPUT_SIZE];

    int32_t size = OUTPUT_SIZE - 10;
    char format[] = "Module %o testing %hx is  f%cn: %x!";
    uint32_t octal = 12, hex = 3735928559;  // DEADBEEF
    uint16_t short_hex = 127;
    char symbol = 'U';

    if (snprintf(output_1, size, format, octal, short_hex, symbol, hex) == 
        my_snprintf(output_2, size, format, octal, short_hex, symbol, hex))
    {
        if (strcmp(output_1, output_2))
        {
            *testing_code = FAILED;

            freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
            printf("\tTrivial testing - FAILED!\n");
        }
    }
    else
    {
        *testing_code = FAILED;

        freopen("./tests/module_testing/fail_desc.txt", "a", stdout);        
        printf("\tTrivial testing - FAILED!\n");
    }
}
