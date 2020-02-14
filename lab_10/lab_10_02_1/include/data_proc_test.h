#ifndef _DATA_PROC_TEST_H_
#define _DATA_PROC_TEST_H_

void alloc_fail(int32_t *const testing_code);
void no_items(int32_t *const testing_code);
void article_lowercase(int32_t *const testing_code);
void article_numbers(int32_t *const testing_code);
void name_numbers(int32_t *const testing_code);
void amount_negative(int32_t *const testing_code);
void strange_stop(int32_t *const testing_code);
void trivial_input(int32_t *const testing_code);

void lowercase_name(int32_t *const testing_code);
void uppercase_name(int32_t *const testing_code);
void allcase_name(int32_t *const testing_code);

void empty_delete(int32_t *const testing_code);
void no_delete(int32_t *const testing_code);
void trivial_delete(int32_t *const testing_code);

#endif