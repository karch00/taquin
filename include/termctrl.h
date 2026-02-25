#ifndef TERMCTRL_H
#define TERMCTRL_H

#include <termios.h>

int toggle_tui_mode(struct termios config);
void toggle_cursor();
int get_termsize(int output[2]);

#endif