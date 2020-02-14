#ifndef _MATRIX_ALGEBRA_H_
#define _MATRIX_ALGEBRA_H_

int64_t dot_product(const dmatrix_t matr_a, const dmatrix_t matr_b, const int64_t index_row, const int64_t index_col);
int matrix_m12n(const dmatrix_t matr_a, const dmatrix_t matr_b, dmatrix_t *const product_matrix);

int identity_matrix(dmatrix_t *const id_matrix, const dmatrix_t matrix);
int raise_to_the_power(const dmatrix_t matrix, dmatrix_t *const raised_matrix, const int64_t power);

#endif
