#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array_cdio.h"


#define SUCCESS 0
#define SIZE_ERROR 10
#define SIZE_VALUE_ERROR 11
#define ELEMENTS_ERROR 20
#define MEMORY_ERROR 30
#define EXTEND_MEMORY_ERROR 31

#define VAR_INPUT 1  // scanf() successfully read 1 variable
#define MIN_SIZE 2  // Array should contain at least 2 elements



// Auxiliary functions:
double *create_array(const int size)
{
    double *array = calloc(size, sizeof(double));
    return array;
}


int check_size(const int size)
{
    if (size < MIN_SIZE)
        return SIZE_VALUE_ERROR;
    return SUCCESS;
}


int check_memory(const double *const array)
{
    if (!array)
        return MEMORY_ERROR;
    return SUCCESS;
}


void *get_pointer_beyond(double *const array, const int size)
{
    return array + size;
}


// Creating the array
int input_array(double **const array, int *const size, double **const trash_pointer)
{    
    printf("Enter the size of the array:\n");
    int check_input = scanf("%d", size);
    
    if (check_input != VAR_INPUT)
        return SIZE_ERROR;

    if (check_size(*size))
        return SIZE_VALUE_ERROR;

    *array = create_array(*size);
    if (check_memory(*array))
        return MEMORY_ERROR;
    
    *trash_pointer = get_pointer_beyond(*array, *size);  // Getting 'trash_pointer' 

    printf("Enter elements of the array:\n");
    for (double *i = *array; i < *trash_pointer; i++)
    {
        check_input = scanf("%lf", i);
        if (check_input != VAR_INPUT)
            return ELEMENTS_ERROR;
    }

    return SUCCESS;
}


// Deleting element from the array
void delete_by_position(double *const index, const double *const trash_pointer)
{
    for (double *i = index; i < trash_pointer - 1; i++)
        *i = *(i + 1);
}


// Inserting element into the array
void *insert_by_position(const double new_element, double *trash_pointer, double *const index)
{
    for (double *i = trash_pointer - 1; i >= index; i--)
        *(i + 1) = *i;
    
    *index = new_element;
    return ++trash_pointer;
}


// Outputing the array
void print_array(double *const array, const double *const trash_pointer)
{
    for (double *i = array; i < trash_pointer; i++)
        printf("%lf ", *i);
}


// Задание №1: удалить 2 элемента из массива, имеющих максимальную разницу с числом mu1
void *delete_by_rule(double *const array, double *trash_pointer, const double mu1, int *const size)
{
    // Delete twice (2 elements)
    for (int i = 0; i < 2; i++)
        trash_pointer = delete_element(array, trash_pointer, mu1, size);
    
    return trash_pointer;
}


void *delete_element(double *const array, double *trash_pointer, const double mu1, int *const size)
{
    double max_diff = fabs(mu1 - *array);
    double *index = array;
        
    for (double *i = array + 1; i < trash_pointer; i++)
    {
        if (max_diff < fabs(mu1 - *i))
        {
            max_diff = fabs(mu1 - *i);
            index = i;
        }
    }

    delete_by_position(index, trash_pointer);
    (*size)--;
    return --trash_pointer;
}


// Задание №2: вставить число mu2 в массив сначала на позицию index а затем в начало и в конец
void *insert_mu2(double *array, double *trash_pointer, const double mu2, double *const index)
{
    trash_pointer = insert_by_position(mu2, trash_pointer, index);
    trash_pointer = insert_by_position(mu2, trash_pointer, array);
    *trash_pointer = mu2;
    
    return ++trash_pointer;
}


// Extend memory for the task #2
void *extend_memory(double *const *const array, double **const trash_pointer, const int size, const int extension, int *const code)
{
    double *extended_array = NULL;
    extended_array = (double *)realloc(*array, (size + extension) * sizeof(double));
    
    if (!extended_array)
    {
        *code = EXTEND_MEMORY_ERROR;
        return *array;
    }
    
    *trash_pointer = get_pointer_beyond(extended_array, size);  // Getting 'trash_pointer';
    *code = SUCCESS;
    return extended_array;
}
