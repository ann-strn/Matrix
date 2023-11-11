#include "tests.h"

// CREATE

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_2) {
  const int rows = 1;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), OK);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 1;

  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), OK);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_4) {
  const int rows = -1;
  const int cols = -1;

  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_5) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_6) {
  const int rows = 0;
  const int cols = 10;

  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_7) {
  const int rows = 50;
  const int cols = 50;

  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), OK);
  remove_matrix(&m);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_4);
  tcase_add_test(tc, create_5);
  tcase_add_test(tc, create_6);
  tcase_add_test(tc, create_7);

  suite_add_tcase(s, tc);
  return s;
}

// EQUAL

START_TEST(eq_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(rows, cols, &mtx);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(DBL_MIN, DBL_MAX);
      m.matrix[i][j] = rand_val;
      mtx.matrix[i][j] = rand_val;
    }
  }
  ck_assert_int_eq(eq_matrix(&m, &mtx), SUCCESS);
  remove_matrix(&m);
  remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }
  ck_assert_int_eq(eq_matrix(&m, &mtx), 0);
  remove_matrix(&m);
  remove_matrix(&mtx);
}
END_TEST

START_TEST(not_eq1) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  create_matrix(rows1, cols1, &mtx);
  ck_assert_int_eq(eq_matrix(&m, &mtx), FAILURE);
  remove_matrix(&m);
  remove_matrix(&mtx);
}
END_TEST

START_TEST(zero_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
}

START_TEST(zero_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(0, 0, &A);
  create_matrix(0, 0, &B);
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(1, 1, &A);
  create_matrix(1, 1, &B);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(1, 1, &A);
  create_matrix(1, 1, &B);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 2;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.01;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1.01;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_6) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.01;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = -4;
  B.matrix[0][0] = 1.01;
  B.matrix[0][1] = -2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = -4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_7) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.00000000234;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(1, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

START_TEST(casual_matrix_8) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0001;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  int result = eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  remove_matrix(&A);
  remove_matrix(&B);
}

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("suite_eq_matrix");
  TCase *tc = tcase_create("case_eq_matrix");

  tcase_add_test(tc, not_eq);
  tcase_add_loop_test(tc, eq_matrix, 0, 100);
  tcase_add_test(tc, not_eq1);

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, zero_matrix_1);
  tcase_add_test(tc, casual_matrix_1);
  tcase_add_test(tc, casual_matrix_2);
  tcase_add_test(tc, casual_matrix_3);
  tcase_add_test(tc, casual_matrix_4);
  tcase_add_test(tc, casual_matrix_5);
  tcase_add_test(tc, casual_matrix_6);
  tcase_add_test(tc, casual_matrix_7);
  tcase_add_test(tc, casual_matrix_8);

  suite_add_tcase(s, tc);
  return s;
}

// SUM

START_TEST(sum_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(sum_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);
  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(sum_matrix(&m, &mtx, &res), CALC_ERROR);
  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
}
END_TEST

START_TEST(sum_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);

  matrix_t res = {0};

  ck_assert_int_eq(sum_matrix(&m, &mtx, &res), INCORRECT_MATRIX);
  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

Suite *suite_sum_matrix(void) {
  Suite *s = suite_create("suite_sum_matrix");
  TCase *tc = tcase_create("case_sum_matrix");

  tcase_add_loop_test(tc, sum_matrix, 0, 100);
  tcase_add_loop_test(tc, sum_matrix1, 0, 100);
  tcase_add_loop_test(tc, sum_matrix2, 0, 100);

  suite_add_tcase(s, tc);
  return s;
}

// SUB

START_TEST(sub_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(sub_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(sub_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(sub_matrix(&m, &mtx, &res), CALC_ERROR);
  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);

  matrix_t res = {0};
  ck_assert_int_eq(sub_matrix(&m, &mtx, &res), INCORRECT_MATRIX);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

Suite *suite_sub_matrix(void) {
  Suite *s = suite_create("suite_sub_matrix");
  TCase *tc = tcase_create("case_sub_matrix");

  tcase_add_loop_test(tc, sub_matrix, 0, 100);
  tcase_add_loop_test(tc, sub_matrix1, 0, 100);
  tcase_add_loop_test(tc, sub_matrix2, 0, 100);

  suite_add_tcase(s, tc);
  return s;
}

// MULT NUMBER

START_TEST(mult_number_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);
  remove_matrix(&m);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t check = {0};
  create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);

  matrix_t res = {0};
  ck_assert_int_eq(mult_number(&m, mult_number, &res), INCORRECT_MATRIX);

  remove_matrix(&m);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

Suite *suite_mult_number_matrix(void) {
  Suite *s = suite_create("suite_mult_number_matrix");
  TCase *tc = tcase_create("case_mult_number_matrix");

  tcase_add_loop_test(tc, mult_number_matrix, 0, 100);
  tcase_add_loop_test(tc, mult_number_matrix2, 0, 100);

  suite_add_tcase(s, tc);
  return s;
}

// MULT MATRIX

START_TEST(mult_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(cols, rows, &mtx);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

  matrix_t check = {0};
  create_matrix(m.rows, mtx.columns, &check);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < mtx.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m.columns; k++)
        check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(simple_mult) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  create_matrix(cols, rows, &mtx);

  matrix_t check = {0};
  create_matrix(m.rows, mtx.columns, &check);

  matrix_t res = {0};
  ck_assert_int_eq(mult_matrix(&m, &mtx, &res), INCORRECT_MATRIX);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix3) {
  matrix_t m = {0};
  int rows = 2;
  int cols = 3;
  create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  int rows1 = 4;
  int cols1 = 5;
  create_matrix(rows1, cols1, &mtx);

  matrix_t check = {0};
  create_matrix(m.rows, mtx.columns, &check);

  matrix_t res = {0};
  ck_assert_int_eq(mult_matrix(&m, &mtx, &res), CALC_ERROR);

  remove_matrix(&m);
  remove_matrix(&mtx);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

Suite *suite_mult_matrix(void) {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc = tcase_create("case_mult_matrix");

  tcase_add_loop_test(tc, mult_matrix, 0, 100);
  tcase_add_loop_test(tc, mult_matrix2, 0, 100);
  tcase_add_test(tc, mult_matrix3);
  tcase_add_test(tc, simple_mult);

  suite_add_tcase(s, tc);
  return s;
}

// TRANSPOSE

START_TEST(transpose_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);

  matrix_t check = {0};
  create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(transpose(&m, &res), OK);
  ck_assert_int_eq(eq_matrix(&check, &res), SUCCESS);

  remove_matrix(&m);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

START_TEST(transpose_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  create_matrix(rows, cols, &m);
  matrix_t check = {0};
  create_matrix(cols, rows, &check);

  matrix_t res = {0};
  ck_assert_int_eq(transpose(&m, &res), INCORRECT_MATRIX);

  remove_matrix(&m);
  remove_matrix(&res);
  remove_matrix(&check);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("suite_transpose_matrix");
  TCase *tc = tcase_create("case_transpose_matrix");

  tcase_add_loop_test(tc, transpose_matrix, 0, 100);
  tcase_add_loop_test(tc, transpose_matrix2, 0, 100);

  suite_add_tcase(s, tc);
  return s;
}

// DETERMINANT

START_TEST(determinant1) {
  const int size = 5;
  matrix_t m = {0};
  create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
  const int size = 4;
  matrix_t m = {0};
  create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
  const int size = 5;
  matrix_t m = {0};
  create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
  const int size = 3;
  matrix_t m = {0};
  create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
  const int size = 2;
  matrix_t m = {0};
  create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant6) {
  const int size = 1;
  matrix_t m = {0};
  create_matrix(size, size, &m);
  m.matrix[0][0] = -5;

  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_double_eq_tol(res, -5, 1e-6);
  ck_assert_int_eq(code, OK);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant7) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  rows = -rows;
  create_matrix(rows, rows, &m);
  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  remove_matrix(&m);
}
END_TEST

START_TEST(determinant8) {
  matrix_t m = {0};
  int rows = 4;
  int cols = 5;
  create_matrix(rows, cols, &m);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  double res = 0;
  int code = determinant(&m, &res);
  ck_assert_int_eq(code, CALC_ERROR);

  remove_matrix(&m);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("case_determinant");

  tcase_add_test(tc, determinant1);
  tcase_add_test(tc, determinant2);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_loop_test(tc, determinant7, 0, 100);
  tcase_add_test(tc, determinant8);

  suite_add_tcase(s, tc);
  return s;
}

// COMPLEMENTS

START_TEST(test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 1, &m);
  if (codec) {
    int code = calc_complements(&m, &result);
    ck_assert_int_eq(code, CALC_ERROR);
    remove_matrix(&result);
  }
  remove_matrix(&m);
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = calc_complements(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(3, 4, &m);
  if (codec == OK) {
    int code = calc_complements(&m, &result);
    ck_assert_int_eq(code, CALC_ERROR);
  }
  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_normal) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  int code1 = create_matrix(3, 3, &m);
  int code2 = create_matrix(3, 3, &expected);
  if (code1 && code2) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 0;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;

    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;

    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    int code = calc_complements(&m, &result);

    ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);
  }
  remove_matrix(&m);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_incorrect);
  tcase_add_test(tc, test_one_by_one);

  suite_add_tcase(s, tc);
  return s;
}

// INVERSE

START_TEST(test_one_by_one_inv) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 1, &m);
  if (codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
    remove_matrix(&result);
  }
  remove_matrix(&m);
}
END_TEST

START_TEST(test_zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 1, &m);
  if (codec) {
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALC_ERROR);
  }
  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_incorrect_inv) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = inverse_matrix(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(determinant) {
  const int size = 2;
  matrix_t m = {0};
  create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;

  matrix_t result = {0};
  int code = inverse_matrix(&m, &result);
  ck_assert_int_eq(code, CALC_ERROR);

  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_not_sqare_inv) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = create_matrix(1, 4, &m);
  if (codec) {
    int code = inverse_matrix(&m, &result);
    ck_assert_int_eq(code, CALC_ERROR);
  }
  remove_matrix(&m);
  remove_matrix(&result);
}
END_TEST

START_TEST(test_normal_inv) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int codec1, codec2;
  codec1 = create_matrix(3, 3, &m);
  if (codec1) codec2 = create_matrix(3, 3, &expected);

  if (codec1 && codec2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    matrix_t result = {0};
    int code = inverse_matrix(&m, &result);

    ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);
    remove_matrix(&result);
  }
  remove_matrix(&m);
  remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_1) {
  matrix_t A, C;
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  inverse_matrix(&A, &B);
  int res = eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&C);
}
END_TEST

START_TEST(inverse) {
  /* const int size = rand() % 100 + 1; */
  const int size = 3;
  matrix_t m = {0};
  create_matrix(size, size, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  matrix_t res = {0};
  inverse_matrix(&m, &res);

  matrix_t expected = {0};
  create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(eq_matrix(&expected, &res), SUCCESS);

  remove_matrix(&expected);
  remove_matrix(&res);
  remove_matrix(&m);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("case_inverse_matrix");

  tcase_add_test(tc, determinant);

  tcase_add_test(tc, test_normal_inv);
  tcase_add_test(tc, test_not_sqare_inv);
  tcase_add_test(tc, test_zero_det);
  tcase_add_test(tc, test_incorrect_inv);
  tcase_add_test(tc, test_one_by_one_inv);
  tcase_add_test(tc, inverse_1);
  tcase_add_test(tc, inverse);

  suite_add_tcase(s, tc);
  return s;
}

// MAIN
void run_tests(void) {
  Suite *list_cases[] = {suite_create_matrix(),
                         suite_eq_matrix(),
                         suite_sum_matrix(),
                         suite_sub_matrix(),
                         suite_mult_number_matrix(),
                         suite_mult_matrix(),
                         suite_transpose_matrix(),
                         suite_determinant(),
                         suite_calc_complements(),
                         suite_inverse_matrix(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  run_tests();
  return 0;
}