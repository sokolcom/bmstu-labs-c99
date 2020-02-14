#include <stdio.h>
#include <string.h>

#define ZERO 0

#define SUCCESS 0
#define FAILURE 1
#define PASSED 1
#define FAILED 0



char *my_strchr(const char *line, const char symbol)
{
	while (*line != symbol)
		if (!*line++)
			return NULL;
	return (char *)line;
}


char *my_strpbrk(const char *to_scan, const char *const sym_list)
{
    while (*to_scan)
        if (my_strchr(sym_list, *to_scan++))
            return (char *)--to_scan;  
    return NULL;
}


int my_strspn(const char *line, const char *symbols)
{
    int length = ZERO;
    while (*line && my_strchr(symbols, *line++))
        length++;
    return length;
}


int my_strcspn(const char *line, const char *symbols)
{
    int length = ZERO;

    while (*line && !my_strchr(symbols, *line++))
        length++;

    return length;
}


char *my_strrchr(const char *line, const char symbol)
{
    char *last = NULL;

    do
    {
        if (*line == symbol)
            last = (char *)line;
    } 
    while (*line++);

    return last;
}


int strpbrk_testing()
{
    char test_string[] = "London is the capital of Great Britain";
    char symbols_list[] = "Brexit";

    char *ideal = strpbrk(test_string, symbols_list);
    char *result = my_strpbrk(test_string, symbols_list);

    if (*ideal == *result)
    {
        printf("strpbrk() testing PASSED!\n\n");
        return PASSED;
    }
    else
    {
        printf("strpbrk() testing FAILED!\n\n");
        return FAILED;
    }
}


int strspn_testing()
{
    char test_string[] = "100 percents it works!";
    char symbols_list[] = "1234567890";

    int ideal = strspn(test_string, symbols_list);
    int result = my_strspn(test_string, symbols_list);

    if (ideal == result)
    {
        printf("strspn() testing PASSED!\n\n");
        return PASSED;
    }
    else
    {
        printf("strspn() testing FAILED!\n\n");
        return FAILED;
    }
}


int strcspn_testing()
{
    char test_string[] = "Symbols before this: ! is 22";
    char symbol = '!';

    int ideal = strcspn(test_string, &symbol);
    int result = my_strcspn(test_string, &symbol);

    if (ideal == result)
    {
        printf("strcspn() testing PASSED!\n\n");
        return PASSED;
    }
    else
    {
        printf("strcspn() testing FAILED!\n\n");
        return FAILED;
    }
}


int strchr_testing()
{
    char test_string[] = "2 girls have made 2 cakes in 2 hours";
    char symbol = '2';

    char *ideal = strchr(test_string, symbol);
    char *result = my_strchr(test_string, symbol);

    if (*ideal == *result)
    {
        printf("strchr() testing PASSED!\n\n");
        return PASSED;
    }
    else
    {
        printf("strchr() testing FAILED!\n\n");
        return FAILED;
    }
}


int strrchr_testing()
{
    char test_string[] = "3 guys have eaten 3 apples in 3 minutes";
    char symbol = '3';

    char *ideal = strrchr(test_string, symbol);
    char *result = my_strrchr(test_string, symbol);

    if (*ideal == *result)
    {
        printf("strrchr() testing PASSED!\n\n");
        return PASSED;
    }
    else
    {
        printf("strrchr() testing FAILED!\n\n");
        return FAILED;
    }
}


int main()
{
    int code = SUCCESS;

    if (!strpbrk_testing())
        code = FAILURE;

    if (!strspn_testing())
        code = FAILURE;

    if (!strcspn_testing())
        code = FAILURE;

    if (!strchr_testing())
        code = FAILURE;

    if (!strrchr_testing())
        code = FAILURE;

    return code;
}

