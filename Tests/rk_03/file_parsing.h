#ifndef _FILE_PARSING_H_
#define _FILE_PARSING_H_

text_t parse_file(const char *const _Filename, int *const _Amount);
void print_data(const char *const _Filename, const text_t _Text, const int _Amount);
void look_alike(const text_t _Text, const int _Amount); 

#endif

