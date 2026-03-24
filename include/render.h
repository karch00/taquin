#ifndef RENDER_H
#define RENDER_H

struct gradient {
    int rgb_i[3];
    int rgb_f[3];
};

struct gradient get_gradient();
void get_gradient_step(struct gradient grad, int lines, float rgb_output[3]);
void print_title(int row, int column, struct gradient grad, int flush);
void print_options(int option, int row, int column, int flush);
void print_controls(int row, int column, int flush);
void print_main_menu(int title_row, int title_column, int options_row, int options_column); 
void print_case(int row, int column, int case_value);
void print_gameboard(int row, int column, int case_values[4][4]);

#endif