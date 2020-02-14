#ifndef _ARRAY_CDIO_H_
#define _ARRAY_CDIO_H_

int input_array(double **const array, int *const size, double **const trash_pointer);
void delete_by_position(double *const index, const double *const trash_pointer);
void *insert_by_position(const double new_element, double *trash_pointer, double *const index);
void print_array(double *const array, const double *const trash_pointer);

void *delete_by_rule(double *const array, double *trash_pointer, const double mu1, int *const size);
void *delete_element(double *const array, double *trash_pointer, const double mu1, int *const size);
void *insert_mu2(double *array, double *trash_pointer, const double mu2, double *const index);
void *extend_memory(double *const *const array, double **const trash_pointer, const int size, const int extension, int *const code);
void *get_pointer_beyond(double *const array, const int size);

#endif
