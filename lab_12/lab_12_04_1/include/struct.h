#ifndef _STRUCT_H_
#define _STRUCT_H_


// Linked list typedef
typedef struct node
{
    uint32_t base;
    uint32_t power;
    struct node *next;
} node_t;

#endif
