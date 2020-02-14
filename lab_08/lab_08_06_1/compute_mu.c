#include "compute_mu.h"


// mu1 = arithmetical mean
double compute_mu1(double *const array, const double *const trash_pointer)
{
    double sum = 0.0;
    int length = 0;
    
    for (double *i = array; i < trash_pointer; i++)
    {
        sum += *i;
        length++;
    }
    return sum / length;
}


// mu2 = max(x)
double compute_mu2(double *const array, const double *const trash_pointer)
{
    double max_element = *array;
    
    for (double *i = array + 1; i < trash_pointer; i++)
    {
        if (max_element < *i)
            max_element = *i;
    }
    return max_element;
}
