#ifndef IO_H
#define IO_H

#include <stdbool.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ENTER 5
#define FLUSH true
#define NOFLUSH false
#define MAX_MULTIPRINT_ROWS 100
#define MAX_MULTIPRINT_COLUMNS 1024

void clear_terminal();
int print_line(const char *text, int row, int column, bool flush);
int erase_line(int row, int column, bool flush);
int erase_multiline(int lines, int row, int column, bool flush);
int get_key();

#endif