/**
 * @file interface.h
 * @brief Заголовочный файл интерфейса игры
 */
#ifndef INTERFACE_H
#define INTERFACE_H
#include "../../brick_game/tetris/tetris.h"
/**
 * @brief Печать дополнительных сведений об игре.
 * @param Указатель на структуру GameInfo_t.
 */
void print_information(GameInfo_t *g);
/**
 * @brief Печать рамки вокруг игрового поля.
 * @param Указатель на структуру GameInfo_t.
 */
void print_frame();
/**
 * @brief Печать игрового поля.
 * @param Current указатель на структуру Figure (текущая фигура), next указатель
 * на структуру Figure (следующая фигура), g указатель на структуру GameInfo_t.
 */
void PrintTable(Figure *current, Figure *next, GameInfo_t *g);
/**
 * @brief Конец игры.
 * После проигрыша ожидает ввода, чтобы перезапустить игру, либо завершить.
 * @param Указатель на структуру GameInfo_t.
 */
void game_over(Figure *current, GameInfo_t *g);
/**
 * @brief Поиск hight_score.
 * @return Возвращает hight_score если найден.
 */
int find_hight_score();
/**
 * @brief Запись hight_score в файл.
 * @param Указатель на структуру GameInfo_t.
 */
void write_score_to_file(GameInfo_t *g);

#endif