#ifndef _TESTING_H_
#define _TESTING_H_

int32_t check_result(const char *const filename, const char *const str);

int32_t out_token(int32_t *const testing_code, int32_t test_idx);
int32_t mul_token(int32_t *const testing_code, int32_t test_idx);
int32_t sqr_token(int32_t *const testing_code, int32_t test_idx);
int32_t div_token(int32_t *const testing_code, int32_t test_idx);
int32_t unknown_token(int32_t *const testing_code, int32_t test_idx);

int32_t non_number(int32_t *const testing_code, int32_t test_idx);
int32_t negative_input(int32_t *const testing_code, int32_t test_idx);
int32_t zero_input(int32_t *const testing_code, int32_t test_idx);
int32_t one_input(int32_t *const testing_code, int32_t test_idx);
int32_t trivial_input(int32_t *const testing_code, int32_t test_idx);

int32_t mult_one(int32_t *const testing_code, int32_t test_idx);
int32_t trivial_m12n(int32_t *const testing_code, int32_t test_idx);

int32_t sqr_one(int32_t *const testing_code, int32_t test_idx);
int32_t trivial_sqr(int32_t *const testing_code, int32_t test_idx);

int32_t zero_quotient(int32_t *const testing_code, int32_t test_idx);
int32_t divisor_one(int32_t *const testing_code, int32_t test_idx);
int32_t trivial_div(int32_t *const testing_code, int32_t test_idx);

#endif
