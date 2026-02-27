#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void shuffle_case_values(int case_values[16]);
void init_case_values(int case_values[4][4]);
int game_loop(bool *continue_main_loop, const int case_size[2], const int gameboard_size[2], int row, int column);

#endif