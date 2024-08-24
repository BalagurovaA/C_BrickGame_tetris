#include <check.h>

#include "../brick_game/tetris/s21_backend.h"

void initialization_of_colors();
void initialization_of_windows(windows *wind_s);
void game_over_(windows *wind_s, int *window_flag);
void frame(gameplay *game, windows *wind_s);
int main_menu(windows *wind_s, int *window_flag);
int pause_menu(windows *wind_s);

START_TEST(test_s21_spawn_1) {
  gameplay test;
  figures test_fig;
  coor test_co;
  int test_win_flag = 0;
  zeroing_struct(&test);
  test.field_[0][2] = 1;
  test.field_[2][2] = 2;

  spawn(&test_fig, &test, &test_co, &test_win_flag);

  ck_assert_int_eq(test.state, GAMEOVER);
}
END_TEST;

START_TEST(test_s21_spawn_3) {
  gameplay test;
  figures test_fig;
  coor test_co;
  int test_win_flag = 0;
  zeroing_struct(&test);
  test.type_next_f = 1;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[0][3], 1);

  zeroing_struct(&test);
  test.type_next_f = 2;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[1][4], 1);

  zeroing_struct(&test);
  test.type_next_f = 3;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[0][3], 1);

  zeroing_struct(&test);
  test.type_next_f = 4;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[1][3], 1);

  zeroing_struct(&test);
  test.type_next_f = 5;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[0][3], 1);

  zeroing_struct(&test);
  test.type_next_f = 6;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[0][4], 1);

  zeroing_struct(&test);
  test.type_next_f = 7;
  spawn(&test_fig, &test, &test_co, &test_win_flag);
  ck_assert_int_eq(test.field_[1][3], 1);
}
END_TEST;

//????
START_TEST(test_s21_spawn_2) {
  gameplay test;
  figures test_fig;
  coor test_co;
  int test_win_flag = 0;
  zeroing_struct(&test);
  test.state = GAMEOVER;
  spawn(&test_fig, &test, &test_co, &test_win_flag);

  ck_assert_int_eq(test.state, 5);
}

////////////////////

Suite *spawn_test() {
  Suite *result;
  TCase *tc_spawn;

  result = suite_create("spawn");
  tc_spawn = tcase_create("spawn");
  tcase_add_test(tc_spawn, test_s21_spawn_1);
  tcase_add_test(tc_spawn, test_s21_spawn_2);
  tcase_add_test(tc_spawn, test_s21_spawn_3);

  suite_add_tcase(result, tc_spawn);
  return result;
}

START_TEST(test_s21_right_move_1) {
  gameplay test;

  coor test_co;

  zeroing_struct(&test);
  test_co.i = 3;
  test_co.j = 3;
  int check_the_field[HIGH][WIDTH] = {0};

  test.field_[2][4] = 1;
  test.field_[3][3] = 1;
  test.field_[3][4] = 1;
  test.field_[3][5] = 1;
  right_move(&test, &test_co);
  check_the_field[2][5] = 1;
  check_the_field[3][4] = 1;
  check_the_field[3][5] = 1;
  check_the_field[3][6] = 1;

  ck_assert_int_eq(test.field_[2][5], check_the_field[2][5]);
  ck_assert_int_eq(test.field_[3][4], check_the_field[3][4]);
  ck_assert_int_eq(test.field_[3][5], check_the_field[3][5]);
  ck_assert_int_eq(test.field_[3][6], check_the_field[3][6]);
}

Suite *right_move_test() {
  Suite *result;
  TCase *tc_right_move;

  result = suite_create("right_move");
  tc_right_move = tcase_create("right_move");
  tcase_add_test(tc_right_move, test_s21_right_move_1);

  suite_add_tcase(result, tc_right_move);
  return result;
}

START_TEST(test_s21_left_move_1) {
  gameplay test;
  coor test_co;
  test_co.i = 3;
  test_co.j = 3;
  zeroing_struct(&test);
  int check_the_field[HIGH][WIDTH] = {0};

  test.field_[2][5] = 1;
  test.field_[3][6] = 1;
  test.field_[3][5] = 1;
  test.field_[3][4] = 1;

  left_move(&test, &test_co);
  check_the_field[2][4] = 1;
  check_the_field[3][5] = 1;
  check_the_field[3][4] = 1;
  check_the_field[3][3] = 1;

  ck_assert_int_eq(test.field_[2][4], check_the_field[2][4]);
  ck_assert_int_eq(test.field_[3][5], check_the_field[3][5]);
  ck_assert_int_eq(test.field_[3][4], check_the_field[3][4]);
  ck_assert_int_eq(test.field_[3][3], check_the_field[3][3]);
}

Suite *left_move_test() {
  Suite *result;
  TCase *tc_left_move;

  result = suite_create("left_move");
  tc_left_move = tcase_create("left_move");
  tcase_add_test(tc_left_move, test_s21_left_move_1);
  suite_add_tcase(result, tc_left_move);
  return result;
}

START_TEST(test_s21_acceleration_1) {
  gameplay test;
  coor test_co;
  zeroing_struct(&test);
  int check_the_field[HIGH][WIDTH] = {0};

  test.field_[2][7] = 1;
  test.field_[3][6] = 1;
  test.field_[3][5] = 1;
  test.field_[3][4] = 1;

  acceleration(&test, &test_co);

  check_the_field[3][7] = 1;
  check_the_field[4][6] = 1;
  check_the_field[4][5] = 1;
  check_the_field[4][4] = 1;

  ck_assert_int_eq(test.field_[3][7], check_the_field[3][7]);
  ck_assert_int_eq(test.field_[4][6], check_the_field[4][6]);
  ck_assert_int_eq(test.field_[4][5], check_the_field[4][5]);
  ck_assert_int_eq(test.field_[4][4], check_the_field[4][4]);
}

Suite *acceleration_test() {
  Suite *result;
  TCase *tc_acceleration;

  result = suite_create("acceleration");
  tc_acceleration = tcase_create("acceleration");
  tcase_add_test(tc_acceleration, test_s21_acceleration_1);
  suite_add_tcase(result, tc_acceleration);
  return result;
}

START_TEST(test_s21_filling_fig_two_1) {
  gameplay test;
  // coor test_co;
  // windows test_wins;
  zeroing_struct(&test);
  int check_the_field[HIGH][WIDTH] = {0};

  test.field_[2][7] = 1;
  test.field_[3][6] = 1;
  test.field_[3][5] = 1;
  test.field_[3][4] = 1;

  filling_fig_two(&test);

  check_the_field[2][7] = 2;
  check_the_field[3][6] = 2;
  check_the_field[3][5] = 2;
  check_the_field[3][4] = 2;

  ck_assert_int_eq(test.field_[2][7], check_the_field[2][7]);
  ck_assert_int_eq(test.field_[3][6], check_the_field[3][6]);
  ck_assert_int_eq(test.field_[3][5], check_the_field[3][5]);
  ck_assert_int_eq(test.field_[3][4], check_the_field[3][4]);
}

Suite *filling_fig_two_test() {
  Suite *result;
  TCase *tc_filling_fig_two;

  result = suite_create("filling_fig_two");
  tc_filling_fig_two = tcase_create("filling_fig_two");
  tcase_add_test(tc_filling_fig_two, test_s21_filling_fig_two_1);
  suite_add_tcase(result, tc_filling_fig_two);
  return result;
}

START_TEST(test_delete_the_line_1) {
  gameplay test;
  zeroing_struct(&test);
  // int deleted_lines_test = 0;

  // int check_the_field[HIGH][WIDTH] = {0};
  test.field_[2][7] = 1;
  test.field_[3][6] = 1;
  test.field_[3][5] = 1;
  test.field_[3][4] = 1;

  int deleted_lines = delete_the_line(&test);
  ck_assert_int_eq(deleted_lines, 0);
}

START_TEST(test_delete_the_line_2) {
  gameplay test;

  zeroing_struct(&test);

  for (int j = 0; j < WIDTH; j++) {
    test.field_[1][j] = 2;
  }
  int deleted_lines = delete_the_line(&test);
  ck_assert_int_eq(deleted_lines, 1);
}

Suite *delete_the_line_test() {
  Suite *result;
  TCase *tc_delete_the_line;

  result = suite_create("delete_the_line");
  tc_delete_the_line = tcase_create("delete_the_line");
  tcase_add_test(tc_delete_the_line, test_delete_the_line_1);
  tcase_add_test(tc_delete_the_line, test_delete_the_line_2);

  suite_add_tcase(result, tc_delete_the_line);
  return result;
}

START_TEST(test_updating_score_1) {
  gameplay test_1;
  zeroing_struct(&test_1);
  updating_score(1, &test_1);

  gameplay test_2;
  zeroing_struct(&test_2);
  updating_score(2, &test_2);

  gameplay test_3;
  zeroing_struct(&test_3);
  updating_score(3, &test_3);

  gameplay test_4;
  zeroing_struct(&test_4);
  updating_score(4, &test_4);

  ck_assert_int_eq(test_1.score, 100);
  ck_assert_int_eq(test_2.score, 300);
  ck_assert_int_eq(test_3.score, 700);
  ck_assert_int_eq(test_4.score, 1500);
}

Suite *updating_score_test() {
  Suite *result;
  TCase *tc_updating_score;

  result = suite_create("updating_score");
  tc_updating_score = tcase_create("updating_score");
  tcase_add_test(tc_updating_score, test_updating_score_1);
  // tcase_add_test(tc_delete_the_line, test_delete_the_line_2); !!!!!!!!!!!!!

  suite_add_tcase(result, tc_updating_score);
  return result;
}

START_TEST(test_levels_1) {
  gameplay test_1;
  int lvl_res = 2;
  test_1.score = 1200;
  int my_res = system_of_levels(&test_1);

  gameplay test_2;
  test_2.level = 4;
  int my_speed = system_of_timeout(&test_2);

  ck_assert_int_eq(my_res, lvl_res);
  ck_assert_int_eq(my_speed, 800);
}

Suite *test_levels() {
  Suite *result;
  TCase *tc_levels;
  result = suite_create("levels");
  tc_levels = tcase_create("levels");
  tcase_add_test(tc_levels, test_levels_1);
  suite_add_tcase(result, tc_levels);
  return result;
}

START_TEST(test_cut_mat_1) {
  gameplay test;
  coor test_co;

  int cut_matrix_t[4][4] = {0};
  int check_matrix[4][4] = {0};
  test_co.i = 3;
  test_co.j = 3;

  zeroing_struct(&test);

  test.field_[0][1] = 1;
  test.field_[1][0] = 1;
  test.field_[1][1] = 1;
  test.field_[1][2] = 1;
  cut_matrix_from_field(&test, &test_co, cut_matrix_t);

  check_matrix[0][1] = 1;
  check_matrix[1][0] = 1;
  check_matrix[1][1] = 1;
  check_matrix[1][2] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(cut_matrix_t[i][j], check_matrix[i][j]);
    }
  }
}

Suite *test_cut_mat() {
  Suite *result;
  TCase *tc_cut_mat;
  result = suite_create("cut_mat");
  tc_cut_mat = tcase_create("cut_mat");
  tcase_add_test(tc_cut_mat, test_cut_mat_1);
  suite_add_tcase(result, tc_cut_mat);
  return result;
}

START_TEST(test_rotation_1) {
  gameplay test;
  zeroing_struct(&test);
  int cut_mat_[4][4] = {0};
  int rota_test[4][4] = {0};
  int check_matrix[4][4] = {0};

  check_matrix[0][1] = 1;
  check_matrix[1][1] = 1;
  check_matrix[1][2] = 1;
  check_matrix[2][1] = 1;

  cut_mat_[0][1] = 1;
  cut_mat_[1][0] = 1;
  cut_mat_[1][1] = 1;
  cut_mat_[1][2] = 1;
  rotation(rota_test, cut_mat_, &test);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(rota_test[i][j], check_matrix[i][j]);
    }
  }

  gameplay test_1;
  coor test_c;
  test_c.i = 3;
  test_c.j = 3;
  zeroing_struct(&test_1);

  figures_rotation(&test_1, &test_c);

  ck_assert_int_eq(3, test_c.i);
  ck_assert_int_eq(3, test_c.j);
}

Suite *test_rotation() {
  Suite *result;
  TCase *tc_rotation;
  result = suite_create("rotation");
  tc_rotation = tcase_create("rotation");
  tcase_add_test(tc_rotation, test_rotation_1);
  suite_add_tcase(result, tc_rotation);
  return result;
}

START_TEST(test_write_field_1) {
  coor test_co;
  gameplay test;
  test_co.i = 3;
  test_co.j = 3;
  zeroing_struct(&test);

  int to_fill_matrix[4][4] = {0};

  to_fill_matrix[0][2] = 1;
  to_fill_matrix[1][2] = 1;
  to_fill_matrix[1][3] = 1;
  to_fill_matrix[2][2] = 1;

  writig_in_field(to_fill_matrix, &test, &test_co);
}

START_TEST(test_write_field_2) {
  coor test_co_2;
  gameplay test_2;
  test_co_2.i = 8;
  test_co_2.j = 8;
  zeroing_struct(&test_2);

  int matrix_[4][4] = {0};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_[i][j] = 1;
    }
  }
  writig_in_field(matrix_, &test_2, &test_co_2);
  ck_assert_int_eq(test_2.field_[5][5], 1);
}

Suite *test_rwite_field() {
  Suite *result;
  TCase *tc_test_write_field;
  result = suite_create("test_write_field");
  tc_test_write_field = tcase_create("test_write_field");
  tcase_add_test(tc_test_write_field, test_write_field_1);
  tcase_add_test(tc_test_write_field, test_write_field_2);

  suite_add_tcase(result, tc_test_write_field);
  return result;
}

///////////------------WORK WITH THE FIGURES------------///////////

START_TEST(test_figures_1) {
  figures test;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      test.stick[i][j] = 0;
      test.cube[i][j] = 0;
      test.left_wing[i][j] = 0;
      test.right_wing[i][j] = 0;
      test.left_snake[i][j] = 0;
      test.right_snake[i][j] = 0;
      test.pyramide[i][j] = 0;
    }
  }
  fill_with_cycle(&test);

  stick_fill(&test);
  cube_fill(&test);
  left_wing_fill(&test);
  right_wing_fill(&test);
  left_snake_fill(&test);
  right_snake_fill(&test);
  pyramide_fill(&test);

  int check_stick[4][4] = {0};
  check_stick[0][0] = 1;
  check_stick[0][1] = 1;
  check_stick[0][2] = 1;
  check_stick[0][3] = 1;

  int check_cube[4][4] = {0};
  check_cube[1][1] = 1;
  check_cube[1][2] = 1;
  check_cube[2][1] = 1;
  check_cube[2][2] = 1;

  int check_left_w[4][4] = {0};
  check_left_w[0][0] = 1;
  check_left_w[1][0] = 1;
  check_left_w[1][1] = 1;
  check_left_w[1][2] = 1;

  int check_right_w[4][4] = {0};
  check_right_w[0][2] = 1;
  check_right_w[1][0] = 1;
  check_right_w[1][1] = 1;
  check_right_w[1][2] = 1;

  int check_left_s[4][4] = {0};
  check_left_s[0][0] = 1;
  check_left_s[0][1] = 1;
  check_left_s[1][1] = 1;
  check_left_s[1][2] = 1;

  int check_right_s[4][4] = {0};
  check_right_s[0][1] = 1;
  check_right_s[0][2] = 1;
  check_right_s[1][0] = 1;
  check_right_s[1][1] = 1;

  int check_pyramide[4][4] = {0};
  check_pyramide[0][1] = 1;
  check_pyramide[1][0] = 1;
  check_pyramide[1][2] = 1;
  check_pyramide[1][1] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(test.stick[i][j], check_stick[i][j]);
      ck_assert_int_eq(test.cube[i][j], check_cube[i][j]);
      ck_assert_int_eq(test.left_wing[i][j], check_left_w[i][j]);
      ck_assert_int_eq(test.right_wing[i][j], check_right_w[i][j]);
      ck_assert_int_eq(test.left_snake[i][j], check_left_s[i][j]);
      ck_assert_int_eq(test.right_snake[i][j], check_right_s[i][j]);
      ck_assert_int_eq(test.pyramide[i][j], check_pyramide[i][j]);
    }
  }

  ////------------next fig------------
  //шаблонная фигура
  //проверка фигуры

  // stick
  int stick_ch[4][4] = {0};
  int stick_matr_[4][4] = {0};
  stick_matr_[0][0] = 1;
  stick_matr_[0][1] = 1;
  stick_matr_[0][2] = 1;
  stick_matr_[0][3] = 1;
  next_stick(stick_ch);
  // cube
  int cube[4][4] = {0};
  int cube_matr_[4][4] = {0};
  cube_matr_[1][1] = 1;
  cube_matr_[1][2] = 1;
  cube_matr_[2][1] = 1;
  cube_matr_[2][2] = 1;
  next_cube(cube);

  // left wing
  int left_w[4][4] = {0};
  int lw_matr_[4][4] = {0};
  lw_matr_[0][0] = 1;
  lw_matr_[1][0] = 1;
  lw_matr_[1][1] = 1;
  lw_matr_[1][2] = 1;
  next_left_wing(left_w);

  // right wing
  int r_w[4][4] = {0};
  int r_w_matr[4][4] = {0};
  r_w_matr[0][2] = 1;
  r_w_matr[1][0] = 1;
  r_w_matr[1][1] = 1;
  r_w_matr[1][2] = 1;
  next_right_wing(r_w);

  // left wing
  int l_s[4][4] = {0};
  int l_s_matr[4][4] = {0};
  l_s_matr[0][0] = 1;
  l_s_matr[0][1] = 1;
  l_s_matr[1][1] = 1;
  l_s_matr[1][2] = 1;
  next_left_snake(l_s);

  //
  int r_s[4][4] = {0};
  int r_s_matr[4][4] = {0};
  r_s_matr[0][1] = 1;
  r_s_matr[0][2] = 1;
  r_s_matr[1][0] = 1;
  r_s_matr[1][1] = 1;
  next_right_snake(r_s);

  int pyr[4][4] = {0};
  int pyr_matr[4][4] = {0};
  pyr_matr[0][1] = 1;
  pyr_matr[1][0] = 1;
  pyr_matr[1][2] = 1;
  pyr_matr[1][1] = 1;
  next_pyramide(pyr);

  int null[4][4] = {0};
  int check_null[4][4] = {0};
  next_fig_null(null);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(stick_matr_[i][j], stick_ch[i][j]);
      ck_assert_int_eq(cube_matr_[i][j], cube[i][j]);
      ck_assert_int_eq(lw_matr_[i][j], left_w[i][j]);
      ck_assert_int_eq(r_w_matr[i][j], r_w[i][j]);
      ck_assert_int_eq(l_s_matr[i][j], l_s[i][j]);
      ck_assert_int_eq(r_s_matr[i][j], r_s[i][j]);
      ck_assert_int_eq(pyr_matr[i][j], pyr[i][j]);
      ck_assert_int_eq(null[i][j], check_null[i][j]);
    }
  }
}

Suite *test_figures() {
  Suite *result;
  TCase *tc_test_figures;
  result = suite_create("test_figures");
  tc_test_figures = tcase_create("test_figures");
  tcase_add_test(tc_test_figures, test_figures_1);

  suite_add_tcase(result, tc_test_figures);
  return result;
}

int main() {
  Suite *result;
  int failed = 0;
  SRunner *runner;

  result = spawn_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = right_move_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = left_move_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = acceleration_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = filling_fig_two_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = delete_the_line_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = updating_score_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = test_levels();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = test_cut_mat();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = test_rotation();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = test_rwite_field();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = test_figures();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : CK_FAILURE;
}
