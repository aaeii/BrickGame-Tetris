/**
 * @file main.c
 * @brief Основной исполняемый файл
 */

#include "../../gui/cli/interface.h"
/**
 * @brief Основная функция
 */
int main() {
  srand(time(NULL));
  int c = 0;
  initscr();
  start_color();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  gettimeofday(&before, NULL);
  keypad(stdscr, TRUE);
  timeout(100);
  GameInfo_t G = {0};
  while (!G.game_exit) {
    G = updateCurrentState();
    Figure Current = {0}, Next = {0};
    game_begining(&G, c);
    generating_next_figure(&Next);
    generating_current_figure(&Current, &Next, &G);
    PrintTable(&Current, &Next, &G);
    while (G.game_status && c != ESCAPE) {
      c = getch();
      game_actions(c, &Current, &Next, &G);
      PrintTable(&Current, &Next, &G);
      refresh();
      game_over(&Current, &G);
    }
    delete_figure(&Current);
    delete_figure(&Next);
  }
  delete_field(&G);
  endwin();
  return 0;
}

void game_begining(GameInfo_t *game, int c) {
  mvprintw(ROWS / 3, 4, "Press ENTER to start the game");
  refresh();
  while (game->game_status == 0) {
    c = getch();
    if (c == ENTER_KEY) {
      game->game_status = 1;
      clear();
    } else if (c == ESCAPE) {
      game->game_exit = 1;
      break;
    }
  }
}