#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define.h"
#include "data_struct.h"
#include "file_parsing.h"



char *get_word(FILE* source, int *const code)
{
    char symbol;
    fscanf(source, "%c", &symbol);

    // Skip first spaces
    while ((symbol == ' ') || (symbol == '\n'))
    {
        fscanf(source, "%c", &symbol);
    }

    int length = 0;
    char *word = NULL;
    while ((symbol != ' ') && (symbol != '\n') && (!feof(source)))
    {
        word = (char *)realloc(word, (++length) * sizeof(char));
        word[length - 1] = symbol;
        fscanf(source, "%c", &symbol);
    }

    word = (char *)realloc(word, (++length) * sizeof(char));
    word[length - 1] = '\0';

    if ((symbol == '\n') || (feof(source)))
    {
        *code = EOLN;
    }
    else
    {
        *code = TRIVIAL;
    }

    return word;
}


int is_unique(const char *const word, unique_t array)
{
    if (array.words == NULL)
        return IS_UNIQUE;

    int i = 0;
    while (i < array.length)
    {
        if (!strcmp(array.words[i++], word))
        {
            return NOT_UNIQUE;
        }
    }

    return IS_UNIQUE;
}


void add_word(char *const word, unique_t *const array)
{
    array->words = (char **)realloc(array->words, (++array->length) * sizeof(char *));
    array->words[array->length - 1] = word;
}


unique_t find_unique_words(FILE* src)
{
    int code;
    unique_t array;
    array.length = 0;
    array.words = NULL;
    char *word;
   
    while (!feof(src))
    {
        // printf("C'MON\n");
        word = get_word(src, &code);
        // printf("KEEEEK %s\n", word);
        if (is_unique(word, array))
        {
            // printf("KEEEEK LOOOOOL\n");
            add_word(word, &array);
        }
        // else
        // {
        //     printf("OOPS\n");
        // }
    }

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%s   ", array.words[i]);
    // }

    return array;
}


int word_cmp(const char *const word_1, const char *const word_2)
{
    return -strcmp(word_2, word_1);  
}


void swap_words(char **const word_1, char **const word_2)
{
    char *temp = *word_1;
    *word_1 = *word_2;
    *word_2 = temp;
}


void sort_unique_words(text_t *const data)
{
    for (int i = 0; i < data->u_words.length - 1; i++)
    {
        for (int j = i + 1; j < data->u_words.length; j++)
        {
            if (word_cmp(data->u_words.words[i], data->u_words.words[j]) > 0)
            {
                // printf("BRUH %s & %s\n", data->u_words.words[i], data->u_words.words[j]);
                swap_words(&data->u_words.words[i], &data->u_words.words[j]);
                // printf("BRUH %s & %s\n\n", data->u_words.words[i], data->u_words.words[j]);
            }
        }
    }
}


int get_pattern_idx(const char *const word, text_t *const text)
{
    int i = 0, idx;

    while (i < text->u_words.length)
    {
        if (!strcmp(text->u_words.words[i], word))
        {
            idx = i;
        }

        i++;
    }

    return idx;
}


void get_sentence(FILE *src_file, text_t *const text, const int i)
{
    char *word;
    int idx = 0, pattern_idx = 0;
    int code_eoln = TRIVIAL;

    text->text[i].sentence = NULL;
    text->text[i].pattern = (int *)calloc(text->u_words.length, sizeof(int));

    while (code_eoln != EOLN)
    {
        text->text[i].sentence = (char **)realloc(text->text[i].sentence, ++idx * sizeof(char *));
        word = get_word(src_file, &code_eoln);
        text->text[i].sentence[idx - 1] = word;

        if (!is_unique(word, text->u_words))
        {
            // printf("OK BOOMER\n");
            pattern_idx = get_pattern_idx(word, text);
            // printf("%d  ", pattern_idx);
            text->text[i].pattern[pattern_idx] = IS_UNIQUE;
        }
    }
}


text_t parse_file(const char *const filename, int *const amount)
{
    FILE* src_file = fopen(filename, "r");
    text_t src_text;

    src_text.u_words = find_unique_words(src_file);
    sort_unique_words(&src_text);
    rewind(src_file);

    // for (int i = 0; i < 20; i++)
    // {
    //     printf("%s   ", src_text.u_words.words[i]);
    // }
    
    int i = 0;
    src_text.text = NULL;
    // src_text.text->pattern = NULL;
    // src_text.text->sentence = NULL;
    while (!feof(src_file))
    {   
        (*amount)++;
        src_text.text = (sentence_t *)realloc(src_text.text, ++i * sizeof(sentence_t));
        get_sentence(src_file, &src_text, i - 1);
    }

    fclose(src_file);
    // printf("YEAH\n");

    return src_text;
}


void print_data(const char *const filename, const text_t text, const int amount)
{
    FILE *stream = fopen(filename, "w");

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < text.u_words.length; j++)
        {
            fprintf(stream, "%d   ", text.text[i].pattern[j]);
        }
        fprintf(stream, "\n");
    }

    fclose(stream);
}


int dot_product(const int* const vector_1, const int* const vector_2, const int length)
{
    int product = 0;

    for (int i = 0; i < length; i++)
    {
        product += (vector_1[i] * vector_2[i]);
    }

    return product;
}


void look_alike(const text_t text, const int amount)
{
    int alike_sum = 0, temp;
    int u, v;   // The most equivalent sentences

    for (int i = 0; i < amount - 1; i++)
    {
        for (int j = i + 1; j < amount; j++)
        {
            temp = dot_product(text.text[i].pattern, text.text[j].pattern, text.u_words.length);
            if (temp > alike_sum)
            {
                alike_sum = temp;
                u = i;
                v = j;
            }
        }
    }

    printf("The most similar sentences: %d and %d\n\n", u, v);
}