#include "matrix.h"

// Сравнение размеров: 1 - ОК, 0 - не Ок
int is_eq_size(matrix_t A, matrix_t B) {
  int flag = -1;
  if (A.rows == B.rows && A.columns == B.columns && A.rows > 0 &&
      A.columns > 0) {
    flag = 1;
  } else {
    flag = 0;
  }
  return flag;
}

// Проверка матриц
int check_matrix(matrix_t *A) {
  int error = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  }
  return error;
}

// Вычисление детерминанта
double calc_det(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else if (A->rows == 2) {
    res = (A->matrix[0][0] * A->matrix[1][1]) -
          (A->matrix[0][1] * A->matrix[1][0]);
  } else {
    for (int col = 0; col < A->columns; col++) {
      matrix_t tmp;
      create_matrix(A->rows - 1, A->columns - 1, &tmp);
      get_minor(A, 0, col, &tmp);
      if (col % 2 == 0) {
        res += A->matrix[0][col] * calc_det(&tmp);
      } else {
        res -= A->matrix[0][col] * calc_det(&tmp);
      }
      remove_matrix(&tmp);
    }
  }
  return res;
}

// Функция для вычисления минора с учетов номера столбца и строки
void get_minor(matrix_t *A, int i, int j, matrix_t *tmp) {
  int rows = A->rows;
  int columns = A->columns;
  int tmp_row = 0;
  int tmp_col = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < columns; col++) {
      if (col != j && row != i) {
        tmp->matrix[tmp_row][tmp_col] = A->matrix[row][col];
        tmp_col++;
      }
    }
    if (row != i) {
      tmp_row++;
      tmp_col = 0;
    }
  }
}

// Вычисление матрицы миноров
void calc_minor(matrix_t *A, matrix_t *result) {
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      matrix_t tmp;
      create_matrix(A->rows - 1, A->columns - 1, &tmp);
      get_minor(A, row, col, &tmp);
      result->matrix[row][col] = calc_det(&tmp);
      remove_matrix(&tmp);
    }
  }
}