#ifndef _MATRIX_STRUCT_H_
#define _MATRIX_STRUCT_H_

#include <stdint.h>

typedef struct
{
    int64_t **matrix_pointer;
    int64_t rows;
    int64_t cols;
} dmatrix_t;

#endif
