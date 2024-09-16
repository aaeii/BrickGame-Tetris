#include <check.h>
#include <stdio.h>

#include "../brick_game/tetris/tetris.h"
#include "../gui/cli/interface.h"

START_TEST(test_signal) {
  GameInfo_t g = updateCurrentState();
  UserAction_t result = 0;
  result = get_signal(0403);
  ck_assert_int_eq(result, Up);
  result = get_signal(0402);
  ck_assert_int_eq(result, Down);
  result = get_signal(0404);
  ck_assert_int_eq(result, Left);
  result = get_signal(0405);
  ck_assert_int_eq(result, Right);
  result = get_signal(27);
  ck_assert_int_eq(result, Terminate);
  result = get_signal(' ');
  ck_assert_int_eq(result, Pause);
  result = get_signal(10);
  ck_assert_int_eq(result, Action);
  delete_field(&g);
}
END_TEST

START_TEST(test_change2) {
  GameInfo_t g = {0};
  g.score = 0;
  g.level = 1;
  g.speed = 1000;
  g.high_score = 0;
  change_level_speed_score(&g, 1);
  ck_assert_int_eq(g.score, 100);
  change_level_speed_score(&g, 2);
  ck_assert_int_eq(g.score, 400);
  change_level_speed_score(&g, 3);
  ck_assert_int_eq(g.score, 1100);
  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.score, 2600);
}
END_TEST

START_TEST(test_change) {
  GameInfo_t g = {0};
  g.score = 0;
  g.level = 1;
  g.speed = 800000;
  g.high_score = 0;
  change_level_speed_score(&g, 3);
  ck_assert_int_eq(g.level, 2);
  ck_assert_int_eq(g.speed, 750000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 3);
  ck_assert_int_eq(g.speed, 700000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 4);
  ck_assert_int_eq(g.speed, 650000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 5);
  ck_assert_int_eq(g.speed, 600000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 6);
  ck_assert_int_eq(g.speed, 550000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 7);
  ck_assert_int_eq(g.speed, 500000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 8);
  ck_assert_int_eq(g.speed, 450000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 9);
  ck_assert_int_eq(g.speed, 400000);

  change_level_speed_score(&g, 4);
  ck_assert_int_eq(g.level, 10);
}
END_TEST
START_TEST(test_delete) {
  Figure Current = {0};
  GameInfo_t g = updateCurrentState();
  ck_assert_int_eq(check_position(&Current, &g), 1);
  game_over(&Current, &g);
  ck_assert_int_eq(g.game_status, 0);
  ck_assert_int_eq(g.game_exit, 0);
  // delete_figure(&Current);
  delete_field(&g);
}
END_TEST
START_TEST(test_deleting_lines1) {
  GameInfo_t g = updateCurrentState();
  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 10; j++) {
      g.field[i][j] = 1;
    }
  deleting_lines(&g);
  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 10; j++) {
      ck_assert_int_eq(g.field[i][j], 0);
    }
  delete_field(&g);
}
END_TEST

START_TEST(test_deleting_lines) {
  GameInfo_t g = updateCurrentState();
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 10; j++) {
      g.field[i][j] = 1;
    }
  deleting_lines(&g);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 10; j++) {
      ck_assert_int_eq(g.field[i][j], 0);
    }
  delete_field(&g);
}
END_TEST

START_TEST(test_stopping_figure) {
  Figure current = {0};
  current.y = 0;
  current.x = 0;
  current.array = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    current.array[i] = (int *)calloc(4, sizeof(int));
  }
  current.array[0][0] = 1;
  current.array[0][1] = 1;
  current.array[1][0] = 1;
  GameInfo_t g = updateCurrentState();
  stopping_figure(&current, &g);
  ck_assert_int_eq(g.field[0][0], 1);
  ck_assert_int_eq(g.field[0][1], 1);
  ck_assert_int_eq(g.field[1][0], 1);
  ck_assert_int_eq(check_position(&current, &g), 0);
  delete_figure(&current);
  delete_field(&g);
}
END_TEST

START_TEST(test_rotate_figure) {
  Figure figure = {0};
  figure.array = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    figure.array[i] = (int *)calloc(4, sizeof(int));
  }
  figure.array[0][0] = 1;
  figure.array[0][1] = 1;
  figure.array[0][2] = 1;
  figure.array[0][3] = 1;
  rotate_figure(&figure);
  ck_assert_int_eq(figure.array[0][0], 0);
  ck_assert_int_eq(figure.array[0][1], 0);
  ck_assert_int_eq(figure.array[0][2], 0);
  ck_assert_int_eq(figure.array[0][3], 1);
  ck_assert_int_eq(figure.array[1][3], 1);
  ck_assert_int_eq(figure.array[2][3], 1);
  ck_assert_int_eq(figure.array[3][3], 1);

  for (int i = 0; i < 4; i++) {
    free(figure.array[i]);
  }
  free(figure.array);
}
END_TEST

START_TEST(test_generating_next_shape2) {
  Figure next = {0}, current = {0};
  GameInfo_t g = updateCurrentState();
  generating_next_figure(&next);
  generating_current_figure(&current, &next, &g);
  // set_start(&g);
  ck_assert_int_ne(current.x, 0);
  delete_figure(&current);
  delete_figure(&next);
  delete_field(&g);
}
END_TEST

START_TEST(test_write_score) {
  GameInfo_t g = updateCurrentState();
  g.high_score = 100;
  write_score_to_file(&g);
  delete_field(&g);
}
END_TEST

START_TEST(test_userInput) {
  GameInfo_t g = updateCurrentState();
  Figure current = {0};
  Figure next = {0};
  generating_next_figure(&next);
  generating_current_figure(&current, &next, &g);
  current.x = 3;
  userInput(Start, &current, &next, &g);
  ck_assert_int_eq(current.x, 3);
  ck_assert_int_eq(g.game_exit, 0);
  ck_assert_int_eq(g.game_status, 1);
  ck_assert_int_eq(g.pause, 0);
  userInput(Right, &current, &next, &g);
  ck_assert_int_eq(current.x, 4);
  ck_assert_int_eq(g.game_status, 1);
  userInput(Left, &current, &next, &g);
  ck_assert_int_eq(current.x, 3);
  userInput(Down, &current, &next, &g);
  ck_assert_int_eq(current.y, 1);
  current.y = 9;
  userInput(Down, &current, &next, &g);
  ck_assert_int_eq(current.y, 10);
  userInput(Up, &current, &next, &g);
  ck_assert_int_eq(current.x, 3);
  userInput(Action, &current, &next, &g);
  ck_assert_int_eq(current.x, 3);
  userInput(Terminate, &current, &next, &g);
  ck_assert_int_eq(g.game_exit, 1);
  ck_assert_int_eq(g.game_status, 0);
  delete_figure(&current);
  delete_figure(&next);
  delete_field(&g);
}
END_TEST

START_TEST(test_game_actions) {
  GameInfo_t g = updateCurrentState();
  Figure current = {0}, next = {0};
  game_actions(KEY_RIGHT, &current, &next, &g);
  ck_assert_int_eq(current.x, 0);
  game_actions(0403, &current, &next, &g);
  game_actions(' ', &current, &next, &g);
  ck_assert_int_eq(g.pause, 0);
  game_actions(' ', &current, &next, &g);
  ck_assert_int_eq(g.pause, 0);
  game_actions(27, &current, &next, &g);
  ck_assert_int_eq(g.game_status, 0);
  delete_field(&g);
}
END_TEST
void srunner_state_funcs(SRunner *sr) {
  Suite *Suite1 = suite_create("s21_brick_game");
  TCase *Test1 = tcase_create("s21_brick_game");
  suite_add_tcase(Suite1, Test1);

  tcase_add_test(Test1, test_delete);
  tcase_add_test(Test1, test_signal);
  tcase_add_test(Test1, test_change2);
  tcase_add_test(Test1, test_change);
  tcase_add_test(Test1, test_deleting_lines1);
  tcase_add_test(Test1, test_deleting_lines);
  tcase_add_test(Test1, test_stopping_figure);
  tcase_add_test(Test1, test_rotate_figure);
  tcase_add_test(Test1, test_generating_next_shape2);
  tcase_add_test(Test1, test_write_score);
  tcase_add_test(Test1, test_userInput);
  tcase_add_test(Test1, test_game_actions);
  srunner_add_suite(sr, Suite1);
}
int main() {
  Suite *s = suite_create("s21_TETRIS");
  SRunner *sr = srunner_create(s);
  srunner_state_funcs(sr);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int f = srunner_ntests_failed(sr);
  srunner_free(sr);
  return f;
}