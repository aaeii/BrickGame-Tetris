/**
 * @file interface.c
 * @brief Интерфейс игры
 */
#include "interface.h"
int find_hight_score() {
  FILE *f = fopen("score.txt", "r");
  if (!f) {
    return 0;
  }
  int max_score = 0, score = 0;
  while (fscanf(f, "%d ", &score) == 1) {
    if (score > max_score) {
      max_score = score;
    }
  }
  fclose(f);
  return max_score;
}
void print_information(GameInfo_t *g) {
  int i = 1;
  mvprintw(i++, COLS + 3, "Hight Score: %d", g->high_score);
  mvprintw(i++, COLS + 3, "Score: %d", g->score);
  mvprintw(i++, COLS + 3, "Level: %d", g->level);
  mvprintw(i++, COLS + 3, "Speed: %d", g->speed);
  mvprintw(i++, COLS + 3, "Next:");
  mvprintw(ROWS - 4, COLS + 3, "Pause - SPACE");
  mvprintw(ROWS - 3, COLS + 3, "Exit - ESC");
  mvprintw(ROWS - 2, COLS + 3, "Move - ENTER");
}
void print_frame() {
  mvaddch(0, 0, ACS_ULCORNER);
  mvhline(0, 1, ACS_HLINE, COLS);
  mvaddch(0, COLS + 1, ACS_URCORNER);

  mvaddch(ROWS + 1, 0, ACS_LLCORNER);
  mvhline(ROWS + 1, 1, ACS_HLINE, COLS);
  mvaddch(ROWS + 1, COLS + 1, ACS_LRCORNER);
  for (int i = 1; i < ROWS + 1; i++) {
    mvaddch(i, 0, ACS_VLINE);
    mvaddch(i, COLS + 1, ACS_VLINE);
  }
}
void PrintTable(Figure *current, Figure *next, GameInfo_t *g) {
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  int Buffer[ROWS][COLS] = {0};
  // current figure
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0; j < ARRAY_SIZE; j++) {
      if (current->array[i][j])
        Buffer[current->y + i][current->x + j] = current->array[i][j];
    }
  }
  //  next figure
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0; j < ARRAY_SIZE; j++) {
      int color = 3;
      if (next->array[i][j] != 0) {
        color = 6;
      }
      attron(COLOR_PAIR(color));
      mvaddch(i + 6, j + COLS + 4, ' ');
      attroff(COLOR_PAIR(color));
    }
  }
  // field
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int color = 6;
      if (g->field[i][j] + Buffer[i][j] != 0) {
        color = 3;
      }
      attron(COLOR_PAIR(color));
      mvaddch(i + 1, j + 1, ' ');
      attroff(COLOR_PAIR(color));
    }
  }
  print_frame();
  attron(COLOR_PAIR(1));
  print_information(g);
  refresh();
  attroff(COLOR_PAIR(1));
}
void game_over(Figure *current, GameInfo_t *g) {
  if (check_position(current, g) == 0) {
    mvprintw(ROWS / 2 - 1, 4, "Game over. Press ENTER to restart.");
    mvprintw(ROWS / 2, 4, "Score: %d", g->score);
    refresh();
    write_score_to_file(g);
    int c = 0;
    while ((c = getch()) != ENTER_KEY && c != ESCAPE) {
      // waiting for action
    }
    if (c == ENTER_KEY) {
      clear();
      g->game_status = 0;
    } else if (c == ESCAPE) {
      g->game_exit = 1;
    }
  }
}
void write_score_to_file(GameInfo_t *g) {
  char h_score[16];
  sprintf(h_score, "%d ", g->score);  // convert
  FILE *in = fopen("score.txt", "a");
  if (in) {
    fputs(h_score, in);
    fclose(in);
  }
}