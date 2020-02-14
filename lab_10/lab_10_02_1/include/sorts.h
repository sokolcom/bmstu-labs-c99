#ifndef _SORTS_H_
#define _SORTS_H_

int32_t get_sort_token();

void cocktail_sort(stock_t *const goods, int32_t (*compare)(const item_t product_1, const item_t product_2));

int32_t article_cmp(const item_t product_1, const item_t product_2);
int32_t name_cmp(const item_t product_1, const item_t product_2);
int32_t count_cmp(const item_t product_1, const item_t product_2);

#endif
