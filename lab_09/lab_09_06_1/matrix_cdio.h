#ifndef _MATRIX_CDIO_H_
#define _MATRIX_CDIO_H_

#define ENTER_ELEMS 1  // When allocating a row, scanf() elements
#define SKIP_ELEMS 0  // Do not enter elements, when allocating a row

int64_t *create_row(const int64_t size, const int key);

int input_matrix(dmatrix_t *const matrix, ...);
int crop_matrix(dmatrix_t *const matrix);
int expand_matrix(dmatrix_t *const matrix, const int64_t matrix_2_size);
void free_matrix(const dmatrix_t *const matrix);
void print_matrix(const dmatrix_t *const matrix);

#endif
