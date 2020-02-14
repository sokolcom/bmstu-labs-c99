#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "struct.h"
#include "define.h"
#include "processing.h"



void make_list(node_t **const head, FILE *stream)
{
    node_t *temp;

    while (!feof(stream))
    {
        temp = (node_t *)calloc(1, sizeof(node_t));

        temp->next = *head;
        fscanf(stream, "%s", temp->word);
        *head = temp;
    }
}


void reverse_words(node_t *head)
{
    char temp_symbol;
    int32_t length;

    while (head)
    {
       length = strlen(head->word);

       for (int32_t idx = 0; idx < length / 2; idx++)
       {
           temp_symbol = head->word[idx];
           head->word[idx] = head->word[length - idx - 1];
           head->word[length - idx - 1] = temp_symbol;
       }

       // printf("%s ", (head)->word);
       head = head->next;
    }
}


void print_list(const node_t *head, FILE *const stream)
{
    while (head)
    {
        printf("%s ", head->word);
        fprintf(stream, "%s\n", head->word);
        head = head->next;
    }
}


void free_list(node_t *head)
{
    node_t *temp = NULL;

    while (head)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
}


void reverse(const char *const filename)
{
    FILE *input_stream = fopen(filename, "r");
    FILE *output_stream = fopen("out.txt", "w");

    node_t *list = NULL;

    make_list(&list, input_stream);
    reverse_words(list);

    print_list(list, output_stream);
    free_list(list);

    fclose(input_stream);
    fclose(output_stream);
}

