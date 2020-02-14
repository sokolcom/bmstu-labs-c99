#include <stdio.h>

#define ONE 1
#define CORRECT_VALUE 1

#define SUCCESS 0
#define FAILURE 1
#define VALUE_ERROR -1

int max_sub_sequence(FILE* input_file, int *max_counter)
{
    int value_prev;

    if (fscanf(input_file, "%d", &value_prev) == CORRECT_VALUE)
    {
        int value;
        int counter = ONE;

        while (fscanf(input_file, "%d", &value) == CORRECT_VALUE)
        {
            if (value == value_prev)
                counter++;
            if (*max_counter < counter)
                *max_counter = counter;
            if (value != value_prev)
                counter = ONE;
            value_prev = value;
        }
        return SUCCESS;
    }
    else
    {
        printf("Invalid input!");
        return VALUE_ERROR;
    }
}


int main()
{
    int result = ONE;
    if (max_sub_sequence(stdin, &result) == SUCCESS)
    {
        printf("Max in a row: %d", result);
        return SUCCESS;
    }
    else
        return FAILURE;
}

