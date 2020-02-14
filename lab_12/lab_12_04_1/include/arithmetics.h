#ifndef _ARITHMETICS_H_
#define _ARITHMETICS_H_

int32_t factorize_number(node_t **const head, int32_t number);
int32_t multiply_factorized(const node_t *head_1, const node_t *head_2, node_t **const head_result);
void square_factorized(node_t **const head);
int32_t divide_factorized(const node_t *dividend, const node_t *divisor, node_t **const head_result);

#endif
