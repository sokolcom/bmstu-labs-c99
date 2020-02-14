#ifndef _STRUCT_H_
#define _STRUCT_H_


// Current state of the buffer 
typedef struct
{
    char *buffer;
    size_t n_max;
    size_t n_real;
} bstate_t;  // b(uffer)state_t


#endif