#include <stdio.h>

#define STR_LEN 257
#define WORD_LEN 17
#define ZERO 0
#define ONE 1

#define SUCCESS 0
#define FAILURE 1
#define STRING_ERROR -1
#define INPUT_SUCCESS 1
#define INPUT_FAILURE 0
#define FOUND 1
#define NOT_FOUND 0
#define UNIQUE 1
#define NOT_UNIQUE 0
#define DIFFERENT 0
#define SAME 1
#define PRINTED 1
#define NOT_PRINTED 0



int is_separator(const char symbol)
{
    char separators[] = " .,:;-!?";
    int i = ZERO;

    while (separators[i] != symbol)
        if (!separators[i++])
            return NOT_FOUND;
    return FOUND;
}


int split_words(const char *const string, char matrix[][WORD_LEN])
{
    int row = ZERO, col = ZERO;
    int index = ZERO;

    while (string[index])
    {
        if (!is_separator(string[index]))
            matrix[row][col++] = string[index];
        else
        {
            matrix[row++][col] = '\0';
            col = ZERO;
        }
        index++;
    }
    matrix[row][col] = '\0';
    return ++row;
}


int word_length(const char *const word)
{
    int length = ZERO;
    while (word[length])
        length++;
    return length;
}


int words_compare(const char *const str_1, const char *const str_2)
{
    int length = word_length(str_1);

    if (length == word_length(str_2))
    {
        for (int i = ZERO; i < length; i++)
            if (str_1[i] != str_2[i])
                return DIFFERENT;
        return SAME;
    }
    else
        return DIFFERENT;
}


int is_unique(char *const template, char words_1[][WORD_LEN], const int amount_1,
    char words_2[][WORD_LEN], const int amount_2)
{
    int counter = ZERO;
    for (int i = ZERO; i < amount_1; i++)
        if (words_compare(template, words_1[i]))
            counter++;

    for (int i = ZERO; i < amount_2; i++)
        if (words_compare(template, words_2[i]))
            counter++;

    if (counter == UNIQUE)
        return UNIQUE;
    else
        return NOT_UNIQUE;
}


int print_unique(char words_1[][WORD_LEN], const int amount_1,
    char words_2[][WORD_LEN], const int amount_2, int *const flag)
{
    int counter = ZERO;

    for (int i = ZERO; i < amount_1; i++)
        if (words_1[i][ZERO] != '\0')
            if (is_unique(words_1[i], words_1, amount_1, words_2, amount_2))
            {
                if ((counter == ZERO) && (!(*flag)))
                {
                    printf("Result: ");
                    *flag = PRINTED;
                }
                printf("%s ", words_1[i]);
                counter++;
            }
    return counter;
}


int amount_unique(char words_1[][WORD_LEN], const int amount_1,
    char words_2[][WORD_LEN], const int amount_2)
{
    int flag = NOT_PRINTED;
    int n = print_unique(words_1, amount_1, words_2, amount_2, &flag);
    n += print_unique(words_2, amount_2, words_1, amount_1, &flag);
    return n;
}


int unique_words(const char *const line_1, const char *const line_2)
{
    char words_1[STR_LEN][WORD_LEN] = { '\0' };
    int amount_1 = split_words(line_1, words_1);

    char words_2[STR_LEN][WORD_LEN] = { '\0' };
    int amount_2 = split_words(line_2, words_2);
    
    return amount_unique(words_1, amount_1, words_2, amount_2);
}


int input_line(char *const line)
{
    char symbol = '\0';
    
    int word_length = ZERO;

    for (int index = ZERO; index < STR_LEN; index++)
    {
        scanf("%c", &symbol);
        if ((symbol == '\n' && index == ZERO) ||
            (index == STR_LEN - ONE && symbol != '\n'))
            return INPUT_FAILURE;
        else if (symbol == '\n')
        {
            line[index] = '\0';
            break;
        }
        else
        {
            line[index] = symbol;
            word_length++;
            if (is_separator(symbol))
                word_length = ZERO;
            if (word_length > WORD_LEN)
                return INPUT_FAILURE;
        }
    }
    return INPUT_SUCCESS;
}


int main()
{
    char line_1[STR_LEN] = { '\0' };
    char line_2[STR_LEN] = { '\0' };

    if (!input_line(line_1) || !input_line(line_2))
    {
        printf("Invalid input!\n");
        return STRING_ERROR;
    }

    if (unique_words(line_1, line_2)) 
        return SUCCESS;
    else
    {
        printf("No unique words found!\n");
        return FAILURE;
    }
}

