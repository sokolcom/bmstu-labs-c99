#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "define.h"

typedef struct node
{
    char word[MAX_WORD_LEN];
    struct node *next;
} node_t;

#endif

