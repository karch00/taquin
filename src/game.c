#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/render.h"
#include "../include/io.h"
#include "../include/game.h"

// On shuffle un array contenant des chiffres de 0 a 15 en utilisant Fisher-Yates
void shuffle_case_values(int case_values[16]) {
    // Init variables
    int tmp;
    int max_idx, selected_idx;
    int values[16];
    // Generation du tableau et max_idx initial
    for (int i = 0; i < 16; i++) values[i] = i;
    max_idx = 15;

    // Shuffle values
    for (int i = 0; i < 16; i++) {
        // Index aleatoire
        if (max_idx) selected_idx = rand() % max_idx;
        else selected_idx = 0;

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
void init_case_values(int case_values[4][4], int current_position[2]) {
    // Init variables
    int raw_case_values[16];
    shuffle_case_values(raw_case_values);

    // Assign values
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            case_values[i][j] = raw_case_values[i*4+j];
            // Assign current position si value = 0
            if (case_values[i][j] == 0) {
                current_position[0] = i;
                current_position[1] = j;
            }
        }
    }
}

// Swap la case vide avec celle selectionnee par la touche de direction
void swap_case(int case_values[4][4], int old_pos[2], int new_pos[2]) {
    // Init variables
    int tmp;

    // a,b = b,a
    tmp = case_values[old_pos[0]][old_pos[1]];
    case_values[old_pos[0]][old_pos[1]] = case_values[new_pos[0]][new_pos[1]];
    case_values[new_pos[0]][new_pos[1]] = tmp;
}

// Loop principal du jeu - Toute la logique du jeu a lieu ici
int game_loop(const int winning_array[4][4], const int case_size[2], int row, int column, bool win_demo) {
    // Init variables
    bool continue_game_loop = true;
    int pressed_key;
    // Variables de position
    int current_position[2], old_position[2];
    int case_values[4][4];
    // Demonstration de victoire 
    if (win_demo) {
        int current_position[2] = {3, 2};
        int old_position[2];
        int case_values[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12},{13,14,0,15}};
    }
    else init_case_values(case_values, current_position);


    // Cleanup des options et Print tableau initial
    erase_multiline(3, row, column, FLUSH);
    print_gameboard(case_size, row, column, case_values);

    // Boucle principal
    while (continue_game_loop) {
        // Get key
        pressed_key = get_key();
        
        // Action dependant de la touche
        switch (pressed_key) {
            // On deplace vers le haut
            case UP:
                // Si on est pas a la limite superieure, deplacer vers haut
                if(current_position[0] > 0) {
                    // Copy block de memoire pour copier array de position vers old position
                    memcpy(old_position, current_position, sizeof(old_position));
                    // Decrement index des lignes et swap
                    current_position[0]--;
                    swap_case(case_values, old_position, current_position);
                }
                break;
            
            // On deplace vers le bas
            case DOWN:
                if(current_position[0] < 3) {
                    memcpy(old_position, current_position, sizeof(old_position));
                    current_position[0]++;
                    swap_case(case_values, old_position, current_position);
                }
                break;
                
            // On deplace vers la droit
            case RIGHT:
                if(current_position[1] < 3) {
                    memcpy(old_position, current_position, sizeof(old_position));
                    current_position[1]++;
                    swap_case(case_values, old_position, current_position);
                }
                break;
            
            // On deplace vers la gauche
            case LEFT:
                if(current_position[1] > 0) {
                    memcpy(old_position, current_position, sizeof(old_position));
                    current_position[1]--;
                    swap_case(case_values, old_position, current_position);
                }
                break;
            
            // Touche non valide - Enter
            default: break;
        }

        // On re-print le tableau
        if (print_gameboard(case_size, row, column, case_values)) return -1;

        // On check for win, si no win on continue
        bool win = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Si un valeur ne correspond pas a celui du gagnant, on signale qu'on a pas gagne
                if (case_values[i][j] != winning_array[i][j]) {
                    win = false;
                    break;
                }
            }
            // Si on a pas gagne, on sort du boucle
            if (win == false) break;
        }
        // Si on a gagne, on sort du boucle principal
        if (win) {
            continue_game_loop = false;
        }
    }
    
    // Print du texte de victoire
    // PLACEHOLDER
    print_line("----{ VICTOIRE }----", row + case_size[0]*4 + 1, column + (case_size[1]*4)/2 - 10, NOFLUSH);
    print_line("> Revenir", row + case_size[0]*4 + 2, column + (case_size[1]*4)/2 - 5, NOFLUSH);
    fflush(stdout);
    
    // Attendre appuyer Enter pour revenir
    while (get_key() != ENTER);

    // Cleanup
    erase_multiline(case_size[0]*4 + 2, row, column, FLUSH);

    return 0;
}