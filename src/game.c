#include <stdbool.h>
#include <stdlib.h>
#include "../include/render.h"
#include "../include/io.h"


// On shuffle un array contenant des chiffres de 0 a 15 en utilisant Fisher-Yates
void shuffle_case_values(int case_values[16]) {
    // Init variables
    int tmp;
    int array_len = 16;
    int values[array_len];
    int max_idx, selected_idx;
    // Generation du tableau et max_idx initial
    for (int i = 0; i < array_len; i++) values[i] = i;
    max_idx = array_len - 1;

    // Shuffle values
    for (int i = 0; i < 16; i++) {
        // Index aleatoire
        selected_idx = rand() % max_idx;

        // Append a case_values
        case_values[i] = values[selected_idx];

        // On swap le dernier element des valeurs et on diminue l'index maximal
        tmp = values[selected_idx];
        values[selected_idx] = values[max_idx];
        values[max_idx] = tmp;

        max_idx--;
    }
}

// On assignel es valeurs de l'array uni-dimensionel a celui de l'array des cases de jeu 2D
void init_case_values(int case_values[4][4]) {
    // Init variables
    int raw_case_values[16];
    shuffle_case_values(raw_case_values);

    // Assign values
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            case_values[i][j] = raw_case_values[i*4+j];
        }
    }
}

// Loop principal du jeu - Toute la logique du jeu a lieu ici
int game_loop(bool *continue_main_loop, const int case_row_size[2], const int gameboard_size[2], int row, int column) {
    // Init variables
    bool continue_game_loop = true;
    int case_values[4][4];
    init_case_values(case_values);

    // Print tableau initial
    // Implement

    // Boucle principal
    while (continue_game_loop) {
        // Implement
    }
}