#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/constants.h"
#include "../include/content.h"
#include "../include/io.h"
#include "../include/render.h"
#include "../include/game.h"


// On shuffle un array contenant des chiffres de 0 a 15 en utilisant Fisher-Yates
void shuffle_case_values(int case_values[16]) {
    // Init variables
    int tmp;
    int max_idx, selected_idx;
    int values[16];

    // Generation du tableau de valeurs ordonnee et max_idx initial
    for (int i = 0; i < 16; i++) values[i] = i;
    max_idx = 15;

    // Shuffle values
    for (int i = 0; i < 16; i++) {
        // Index de case aleatoire
        if (max_idx) selected_idx = rand() % max_idx;
        else selected_idx = 0;

        // Append la case avec l'index selectionne a case_values
        case_values[i] = values[selected_idx];

        // On swap le dernier element des valeurs et on diminue l'index maximal
        // Dernier element (element deja dans case_values) ne peux pas etre selectionne a nouveau
        tmp = values[selected_idx];
        values[selected_idx] = values[max_idx];
        values[max_idx] = tmp;

        max_idx--;
    }
}

// On assigne les valeurs de l'array uni-dimensionel a celui de l'array des cases de jeu 2D
void init_case_values(int case_values[4][4], int current_position[2]) {
    // Init variables
    int unidim_case_values[16];
    shuffle_case_values(unidim_case_values);

    // Assign values
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            case_values[i][j] = unidim_case_values[i*4+j];
            
            // Assign current position quand case 0 (case vide)
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
// On passe en parametres la position de la case vide
// win_demo permet de gagner en 1 mouvement
void game_loop(int row, int column, bool win_demo) {
    // Variables de jeu
    bool continue_game_loop = true;
    int pressed_key;
    // Variables de position de case
    int current_position[2], old_position[2];
    int case_values[4][4];
   
    // Si on passe en parametre win_demo, on initialise un tableau a ganger en 1 mouvement
    if (win_demo) {
        current_position[0] = 3;
        current_position[1] = 3;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                case_values[i][j] = WINNING_ARRAY[i][j];
            }
        }
    }
    // On initialise un tableau aleatoire sinon
    else init_case_values(case_values, current_position);

    // Cleanup des options et on print le tableau initial
    erase_multiline(3, row, column, FLUSH);
    print_gameboard(row, column, case_values);

    // Boucle principal
    while (continue_game_loop) {
        pressed_key = get_key();
        
        // Action dependant de la touche
        switch (pressed_key) {
            // On se deplace vers le haut
            case UP:
                // Si on est pas a la limite superieure, deplacer vers haut
                if(current_position[0] > 0) {
                    // Copy valeur dans block de memoire de notre position actuelle vers position ancienne
                    memcpy(old_position, current_position, sizeof(old_position));
                    // Decrement le valeur de la position actuelle
                    current_position[0]--;
                    // On echange les cases dans le tableau
                    swap_case(case_values, old_position, current_position);
                }
                break;
            
            // On se deplace vers le bas
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
           
            // Appuye sur q - quit
            case QUIT:
                // Cleanup et return au menu principal
                erase_multiline(CASE_SIZE[0]*4 + 2, row, column, FLUSH);
                return;
            
            // Touche non valide, on appuye mais on break pas le switch
            default:
                pressed_key = get_key();
        }

        // On re-print le tableau
        print_gameboard(row, column, case_values);

        // On check pour victoire, si pas de victoire on continue
        // On parcour le tableau en ordre
        bool win = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Si un des valeurs ne correspond pas a celui du gagnant, on signale qu'on a pas gagne
                if (case_values[i][j] != WINNING_ARRAY[i][j]) {
                    win = false;
                    break;
                }
            }
            // Si on gagne, on sort du boucle
            if (win == false) break;
        }

        // Si on gagne, on indique qu'on sort du boucle principal apres finir l'iteration
        if (win) {
            continue_game_loop = false;
        }
    }
    
    // Print du texte de victoire sous le tableau
    print_line("----{ VICTOIRE }----", row + CASE_SIZE[0]*4 + 1, column + (CASE_SIZE[1]*4)/2 - 10, NOFLUSH);
    print_line("> Revenir", row + CASE_SIZE[0]*4 + 2, column + (CASE_SIZE[1]*4)/2 - 5, NOFLUSH);
    fflush(stdout);
    
    // Attendre appuyer Enter ou q pour revenir
    while (true) {
        pressed_key = get_key();
        if (pressed_key == ENTER || pressed_key == QUIT) break;
    };
}