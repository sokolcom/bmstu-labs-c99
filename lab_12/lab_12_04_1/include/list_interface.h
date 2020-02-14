#ifndef _LIST_INTERFACE_H_
#define _LIST_INTERFACE_H_

int32_t push_node(node_t **const head, const int32_t base, const int32_t power);
int32_t delete_node(node_t **const head);
void print_list(FILE *const output_stream, const node_t *head);
void free_list(node_t *head);

int32_t get_number(const node_t *factorized);
int32_t reverse_copy(const node_t *src, node_t **const result);

#endif
