#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void shuffle_case_values(int case_values[16]);
void init_case_values(int case_values[4][4], int current_position[2]);
int game_loop(const int winning_array[4][4], const int case_size[2], int row, int column, bool win_demo);

#endif