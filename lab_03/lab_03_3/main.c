/*
Задача 3

Выбранный тип: integer
Алгоритм сортровки: сортировка "пузырьком"
"Направление" сортировки: по возрастанию
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NO_KEY ' '
#define KEY_GENERATE 'g'
#define KEY_PRINT 'p'
#define KEY_SORT 's'
#define ONE_ELEM 1

#define ELEMS_AMOUNT 100
#define START -100
#define RANGE 201

#define ZERO 0
#define ONE 1
#define TWO 2
#define KEY_LENGTH 1

#define SUCCESS 0
#define FAILURE 1
#define NO_NAME_ERROR -1
#define KEY_ERROR -2
#define EXIST_ERROR -3
#define EMPTY_ERROR -4



char check_key(const char *const key)
{
    if (strlen(key) != KEY_LENGTH)
        return NO_KEY;

    if (key[ZERO] == KEY_GENERATE)
        return KEY_GENERATE;
    else if (key[ZERO] == KEY_PRINT)
        return KEY_PRINT;
    else if (key[ZERO] == KEY_SORT)
        return KEY_SORT;
    else
        return NO_KEY;
}


int file_length(FILE* source)
{
    int length = ZERO;
    int element;
    rewind(source);
    while (fread(&element, sizeof(int), ONE, source) == ONE_ELEM)
        length++;
    return length;
}


void generate_file(FILE* source)
{
    srand(time(NULL));
    int element;

    for (int i = ZERO; i < ELEMS_AMOUNT; i++)
    {
        element = START + rand() % RANGE;
        fwrite(&element, sizeof(int), ONE, source);
    }
}


int get_number_by_pos(FILE* source, const int index)
{
    int element;
    fseek(source, index * sizeof(int), SEEK_SET);
    fread(&element, sizeof(int), ONE, source);
    return element;
}


void put_number_by_pos(FILE* source, const int element, const int index)
{
    fseek(source, index * sizeof(int),  SEEK_SET);
    fwrite(&element, sizeof(int), ONE, source);
}


/*
void qsort_binary(FILE* source, const int first, const int last)
{
    if (first < last)
    {
        int f = first;
        int l = last;
        int x = get_number_by_pos(source, (first + last) / TWO);

        while (f <= l)
        {
            int elem_f = get_number_by_pos(source, f);
            while ((elem_f < x) && (f < last))
            {
                f++;
                elem_f = get_number_by_pos(source, f);
            }

            int elem_l = get_number_by_pos(source, l);
            while ((elem_l > x) && (l > first))
            {
                l--;
                elem_l = get_number_by_pos(source, l);
            }

            if (f <= l)
            {
                put_number_by_pos(source, elem_f, l);
                put_number_by_pos(source, elem_l, f);
                f++;
                l--;
            }
        }

        qsort_binary(source, first, l);
        qsort_binary(source, f, last);
    }
}
*/


void sort_file(FILE* source)
{
    int length = file_length(source);

    for (int i = ZERO; i < length - ONE; i++)
        for (int j = i + ONE; j < length; j++)
        {
            int element_i = get_number_by_pos(source, i);
            int element_j = get_number_by_pos(source, j);
            if (element_i > element_j)
            {
                put_number_by_pos(source, element_i, j);
                put_number_by_pos(source, element_j, i);
            }
        }
}


void print_file(FILE* source)
{
    rewind(source);
    int element;
    while (fread(&element, sizeof(int), ONE, source) == ONE_ELEM)
        printf("%d\n", element);
}


int main(int argc, char **argv)
{
    if (argc <= TWO)
    {
        printf("No file name entered!\n");
        return NO_NAME_ERROR;
    }

    if (check_key(argv[ONE]) == KEY_GENERATE)
    {
        FILE* binary_file = fopen(argv[TWO], "wb");
        generate_file(binary_file);
        fclose(binary_file);
        return SUCCESS;
    }
    else if (check_key(argv[ONE]) == KEY_PRINT)
    {
        FILE* binary_file = fopen(argv[TWO], "rb");
        if (binary_file)
        {
            if (file_length(binary_file))
            {
                print_file(binary_file);
                fclose(binary_file);
                return SUCCESS;
            }
            else
            {
                printf("File is empty!\n");
                return FAILURE;
            }
        }
        else
        {
            printf("File not found!\n");
            return EXIST_ERROR;
        }
    }
    else if (check_key(argv[ONE]) == KEY_SORT)
    {
        FILE* binary_file = fopen(argv[TWO], "rb+");
        if (binary_file)
        {
            if (file_length(binary_file))
            {
                sort_file(binary_file);
                fclose(binary_file);
                return SUCCESS;
            }
            else
            {  
                printf("File is empty!\n");
                return FAILURE;
            }
        }
        else
        {
            printf("File not found!\n");
            return EXIST_ERROR;
        }
    }
    else
    {
        printf("Unknown key!\n");
        return KEY_ERROR;
    }
}

