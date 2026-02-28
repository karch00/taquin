#ifndef RENDER_H
#define RENDER_H

struct gradient {
    int rgb_i[3];
    int rgb_f[3];
};

struct gradient get_gradient();
void get_gradient_step(struct gradient grad, int lines, float rgb_output[3]);
int print_title(const int title_size[2], int row, int column, struct gradient grad, int flush);
int print_options(const int options_size[2], int option, int row, int column, int flush);
int print_controls(const int controls_size[2], int row, int column, int flush);
int print_main_menu(const int title_size[2], const int options_size[2], int title_row, int title_column, int options_row, int options_column); 
void print_case(const int case_size[2], int row, int column, int case_value);
int print_gameboard(const int case_size[2], int row, int column, int case_values[4][4]);

#endif