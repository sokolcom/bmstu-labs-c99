#ifndef _AUXILIARY_H_
#define _AUXILIARY_H_

void print_symbols(const char **const str_format, bstate_t *const buffer_state);
void get_specifier(va_list *const args, const char **const str_format, bstate_t *const buffer_state);
int32_t print_string(char *str_out, char *copy_out, bstate_t *const buffer_state);

void h_modifier(va_list *const args, const char **const str_format, bstate_t *const buffer_state);
void octal_number(uint32_t value, bstate_t *const buffer_state);
void hex_number(uint32_t value, bstate_t *const buffer_state);

#endif
