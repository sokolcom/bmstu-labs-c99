#ifndef _DATA_PROCESSING_H_
#define _DATA_PROCESSING_H_

int32_t input_products(stock_t *const items_array, ...);
void configure_articles(stock_t *const items_array);
int32_t delete_items(stock_t *const items_array, const char *const spec_article);

void free_data(const stock_t *const items_array);
int32_t print_data(const char *const stream_name, const stock_t *const items_array);

#endif