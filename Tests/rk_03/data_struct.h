#ifndef _STRUCT_H_
#define _STRUCT_H_


typedef struct
{
    char **words;
    int length;
} unique_t;


typedef struct 
{
    char **sentence;
    int *pattern;
} sentence_t;


typedef struct
{
    unique_t u_words;
    sentence_t *text;
} text_t;


#endif

