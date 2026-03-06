#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void shuffle_case_values(int case_values[16]);
void init_case_values(int case_values[4][4], int current_position[2]);
void swap_case(int case_values[4][4], int old_pos[2], int new_pos[2]);
int game_loop(int row, int column, bool win_demo);

#endif