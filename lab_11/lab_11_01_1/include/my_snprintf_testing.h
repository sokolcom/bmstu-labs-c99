#ifndef _MY_SNPRINTF_TESTING_H_
#define _MY_SNPRINTF_TESTING_H_

void n_zero(int32_t *const testing_code);
void n_less_length(int32_t *const testing_code);
void n_more_length(int32_t *const testing_code);
void specifier_absence(int32_t *const testing_code);
void c_specifier(int32_t *const testing_code);
void x_specifier(int32_t *const testing_code);
void hx_specifier(int32_t *const testing_code);
void o_specifier(int32_t *const testing_code);
void ho_specifier(int32_t *const testing_code);
void trivial_snprintf(int32_t *const testing_code);

#endif
