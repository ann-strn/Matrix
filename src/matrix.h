#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2, MALLOC_FAILED = 3 };

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int calc_complements(matrix_t *A, matrix_t *result);
int inverse_matrix(matrix_t *A, matrix_t *result);
// PUBLIC
int check_matrix(matrix_t *A);
int is_eq_size(matrix_t A, matrix_t B);
double calc_det(matrix_t *A);
void get_minor(matrix_t *A, int i, int j, matrix_t *tmp);
void calc_minor(matrix_t *A, matrix_t *result);

#endif