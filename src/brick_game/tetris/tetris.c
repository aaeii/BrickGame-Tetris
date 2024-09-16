/**
 * @file tetris.c
 * @brief Основные функции игры
 */

#include "tetris.h"

#include "../../gui/cli/interface.h"
int timer = 800000;
struct timeval before, now;
Figure figures_array[7] = {
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){0, 1, 1, 0}, (int[4]){1, 1, 0, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){1, 1, 0, 0}, (int[4]){0, 1, 1, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){0, 1, 0, 0}, (int[4]){1, 1, 1, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){0, 0, 1, 0}, (int[4]){1, 1, 1, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){0, 1, 0, 0}, (int[4]){0, 1, 1, 1},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){0, 1, 1, 0}, (int[4]){0, 1, 1, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0},
    {(int *[]){(int[4]){0, 0, 0, 0}, (int[4]){1, 1, 1, 1}, (int[4]){0, 0, 0, 0},
               (int[4]){0, 0, 0, 0}},
     0, 0}};

Figure copy_figure(Figure *figure) {
  Figure new_figure = *figure;
  new_figure.array = (int **)malloc(ARRAY_SIZE * sizeof(int *));
  for (int i = 0; i < ARRAY_SIZE; i++) {
    new_figure.array[i] = (int *)malloc(ARRAY_SIZE * sizeof(int));
    memcpy(new_figure.array[i], figure->array[i], ARRAY_SIZE * sizeof(int));
  }
  return new_figure;
}

void delete_figure(Figure *f) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    free(f->array[i]);
  }
  free(f->array);
}

int check_position(Figure *figure, GameInfo_t *g) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0; j < ARRAY_SIZE; j++) {
      if ((figure->x + j < 0 || figure->x + j >= COLS ||
           figure->y + i >= ROWS)) {
        if (figure->array[i][j]) return 0;
      } else if (g->field[figure->y + i][figure->x + j] && figure->array[i][j])
        return 0;
    }
  }
  return 1;
}

void stopping_figure(Figure *current, GameInfo_t *g) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0; j < ARRAY_SIZE; j++) {
      if (current->array[i][j]) {
        g->field[current->y + i][current->x + j] = current->array[i][j];
      }
    }
  }
}
void change_level_speed_score(GameInfo_t *game, int count) {
  int decrease = 50000;
  switch (count) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;
    default:
      break;
  }
  if (game->score >= 600 && game->level == 1) {
    game->level = 2;
    game->speed -= decrease;
  } else if (game->score >= 1200 && game->level == 2) {
    game->level = 3;
    game->speed -= decrease;
  } else if (game->score >= 1800 && game->level == 3) {
    game->level = 4;
    game->speed -= decrease;
  } else if (game->score >= 2400 && game->level == 4) {
    game->level = 5;
    game->speed -= decrease;
  } else if (game->score >= 3000 && game->level == 5) {
    game->level = 6;
    game->speed -= decrease;
  } else if (game->score >= 3600 && game->level == 6) {
    game->level = 7;
    game->speed -= decrease;
  } else if (game->score >= 4200 && game->level == 7) {
    game->level = 8;
    game->speed -= decrease;
  } else if (game->score >= 4800 && game->level == 8) {
    game->level = 9;
    game->speed -= decrease;
  } else if (game->score >= 5400 && game->level == 9) {
    game->level = 10;
  }
  timer = game->speed;
  if (game->high_score < game->score) game->high_score = game->score;
}

void deleting_lines(GameInfo_t *g) {
  int sum, count = 0;
  for (int i = 0; i < ROWS; i++) {
    sum = 0;
    for (int j = 0; j < COLS; j++) {
      sum += g->field[i][j];
    }
    if (sum == COLS) {
      count++;
      for (int k = i; k >= 1; k--)
        for (int l = 0; l < COLS; l++) {
          g->field[k][l] = g->field[k - 1][l];
        }
      for (int j = 0; j < COLS; j++) {
        g->field[0][j] = 0;
      }
    }
  }

  change_level_speed_score(g, count);
}

void rotate_figure(Figure *figure) {
  Figure temp = copy_figure(figure);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    for (int j = 0, k = ARRAY_SIZE - 1; j < ARRAY_SIZE; j++, k--) {
      figure->array[i][j] = temp.array[k][i];
    }
  }
  delete_figure(&temp);
}

void generating_next_figure(Figure *next) {
  int n1 = rand() % 7;
  if (next->array) {
    delete_figure(next);
  }
  *next = copy_figure(&figures_array[n1]);
}

void generating_current_figure(Figure *current, Figure *next, GameInfo_t *g) {
  if (current->array) {
    delete_figure(current);
  }
  *current = copy_figure(next);
  current->x = rand() % (COLS - ARRAY_SIZE) + 1;
  current->y = 0;
  generating_next_figure(next);
  if (!check_position(current, g)) {
    g->game_status = 0;
  }
}

UserAction_t get_signal(int user_input) {
  UserAction_t sign = -1;
  if (user_input == KEY_UP)
    sign = Up;
  else if (user_input == KEY_DOWN)
    sign = Down;
  else if (user_input == KEY_LEFT)
    sign = Left;
  else if (user_input == KEY_RIGHT)
    sign = Right;
  else if (user_input == ESCAPE)
    sign = Terminate;
  else if (user_input == ENTER_KEY)
    sign = Action;
  else if (user_input == KEY_SPACE)
    sign = Pause;

  return sign;
}

void userInput(UserAction_t action, Figure *current, Figure *next,
               GameInfo_t *g) {
  Figure temp = copy_figure(current);
  switch (action) {
    case Left:
      temp.x--;
      if (check_position(&temp, g)) current->x--;
      break;
    case Right:
      temp.x++;
      if (check_position(&temp, g)) current->x++;
      break;
    case Down:
      temp.y++;
      if (check_position(&temp, g))
        current->y++;
      else {  // figure has reached the end
        stopping_figure(current, g);
        deleting_lines(g);
        generating_current_figure(current, next, g);
      }
      break;
    case Up:
      break;
    case Action:
      rotate_figure(&temp);
      if (check_position(&temp, g)) rotate_figure(current);
      break;
    case Pause:
      g->pause = 1;
      if (g->pause) {
        mvprintw(ROWS / 2, 4, "Game paused. Press SPACE to resume.");
        refresh();
        while (getch() != ' ') {
          g->pause = 0;
        }
        clear();
        PrintTable(current, next, g);
      }
      refresh();
      break;
    case Terminate:
      g->game_exit = 1;
      g->game_status = 0;
      break;
    case Start:
      g->game_status = 1;
      break;
  }
  delete_figure(&temp);
  PrintTable(current, next, g);
}

GameInfo_t updateCurrentState() {
  GameInfo_t state = {0};
  set_start(&state);
  return state;
}
void delete_field(GameInfo_t *game) {
  for (int i = 0; i < ROWS; i++) {
    free(game->field[i]);
  }
  free(game->field);
}
void set_start(GameInfo_t *game) {
  game->pause = 0;
  game->high_score = find_hight_score();
  game->score = 0;
  game->speed = timer;
  game->level = 1;
  if (game->field != NULL) {
    delete_field(game);
  }
  game->field = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; i++) {
    game->field[i] = (int *)calloc(COLS, sizeof(int));
  }
}
void game_actions(int sign, Figure *curr, Figure *n, GameInfo_t *g) {
  while (g->game_status == 1 && g->game_exit == 0) {
    if ((sign = getch())) {
      UserAction_t action = get_signal(sign);
      userInput(action, curr, n, g);
    }
    if (g->pause == 0) {
      gettimeofday(&now, NULL);
      if ((now.tv_sec * 1000000 - before.tv_sec * 1000000) >
          timer) {  // checking the time
        userInput(Down, curr, n, g);
        gettimeofday(&before, NULL);
      }
    }
    if (g->level == FINAL_LEVEL) {
      mvprintw(ROWS / 2, 15, "Victory! You have completed the game!");
      refresh();
      while (getch() != ESCAPE) {
        g->game_exit = 1;
        return;
      }
    }
  }
}
