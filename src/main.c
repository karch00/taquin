#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/render.h"
#include "../include/termctrl.h"
#include "../include/io.h"
#include "../include/game.h"
#include "../include/content.h"
#include "../include/constants.h"



int main(int argc, char *argv[]) {
    // Init variable demonstration victoire
    bool win_demo = false;
    // Init des variables de terminal
    struct termios termconf;
    int terminal_size[2];
    // Initialisation des variables de terminal
    tcgetattr(STDIN_FILENO, &termconf);
    if (get_termsize(terminal_size)) {
        printf("Erreur: Impossible de lire taille de terminal!\n");
        return 1;
    }
    // Variables de selection
    int pressed_key;
    int main_menu_option;
    bool continue_main_loop = true;
    // Variables de taille
    int title_rows = TITLE_SIZE[0];
    int title_columns = 60; // Hardcoded car caracteres non uniformes
    int options_rows = OPTIONS_SIZE[0];
    int options_columns = OPTIONS_SIZE[1];
    int controls_rows = CONTROLS_SIZE[0];
    int controls_columns = CONTROLS_SIZE[1];
    int case_rows = CASE_SIZE[0];
    int case_columns = CASE_SIZE[1];
    int gameboard_rows = case_rows * 4;
    int gameboard_columns = case_columns * 4;
    // Variables de coordonnees 
    int main_menu_title_row = (int)(terminal_size[0] / 2.5) - title_rows;  
    int main_menu_title_column = (terminal_size[1] / 2) - (title_columns / 2) + 1;
    int main_menu_options_row = main_menu_title_row + title_rows + 2;
    int main_menu_options_column = main_menu_title_column + (title_columns / 2) - (options_columns / 2);
    int main_menu_controls_row = main_menu_title_row + title_rows + 2;
    int main_menu_controls_column = main_menu_title_column + (title_columns / 2) - (controls_columns / 2);
    int gameboard_row = main_menu_title_row + title_rows + 2;
    int gameboard_column = main_menu_title_column + (title_columns / 2) - (gameboard_columns / 2);



    // On set win_demo a true si argument -w
    if (argc >= 2 && !strcmp(argv[1], "-w")) win_demo = true;

    // On assure un minimum de taille de terminal, sinon print et exit
    if (terminal_size[0]<MIN_TERMSIZE[0] || terminal_size[1]<MIN_TERMSIZE[1]) {
        printf("Taille de terminal trop petit!\n");
        return 1;
    }
    
    // On active le mode TUI complet
    toggle_tui_mode(termconf);
    toggle_cursor();
    clear_terminal();

    // Init random seed pour generer la gradiente et le tableau
    srand(time(NULL));

    // On print le menu principal
    print_main_menu(main_menu_title_row, main_menu_title_column, main_menu_options_row, main_menu_options_column);
    main_menu_option = 0;
    
    // Boucle selection d'options
    while (continue_main_loop) {
        pressed_key = get_key();
        
        // On associe la touche a une option valide
        switch (pressed_key) {
            // Move options up
            case UP:
                if (main_menu_option == 0) main_menu_option = 2;
                else main_menu_option -= 1;
                print_options(main_menu_option, main_menu_options_row, main_menu_options_column, FLUSH);
                break;
            
            // Move options down
            case DOWN:
                if (main_menu_option == 2) main_menu_option = 0;
                else main_menu_option += 1;
                print_options(main_menu_option, main_menu_options_row, main_menu_options_column, FLUSH);
                break;

            // Selectionner option
            case ENTER:
                    // Jouer                        
                    if (main_menu_option == 0) {
                        // On lance le boucle du jeu
                        game_loop(gameboard_row, gameboard_column, win_demo);

                        // Effacer le jeu, print options a nouveau et pos curseur a 0
                        erase_multiline(case_rows*4 + 3, gameboard_row, gameboard_column, NOFLUSH);
                        print_options(0, main_menu_options_row, main_menu_options_column, FLUSH);
                        main_menu_option = 0;
                    }
                    // Voir controles
                    else if (main_menu_option == 1) {
                        // Print les controles et attendre a pressioner Enter ou quit pour revenir
                        print_controls(main_menu_controls_row, main_menu_controls_column, FLUSH);
                        while (true) {
                            pressed_key = get_key();
                            if (pressed_key == ENTER || pressed_key == QUIT) break;
                        };

                        // Effacer les controles, print options a nouveau et positioner curseur a 0
                        erase_multiline(controls_rows, main_menu_controls_row, main_menu_controls_column, NOFLUSH);
                        print_options(0, main_menu_options_row, main_menu_options_column, FLUSH);
                        main_menu_option = 0;
                    }
                    // Quitter
                    else if (main_menu_option == 2) {
                        continue_main_loop = false;
                    }

                    break;

            // Appuye sur q - quit
            case QUIT:
                    continue_main_loop = false;

            // Key sans valeur 
            default: break;
        }
    }

    // Return to regular terminal
    toggle_tui_mode(termconf);
    toggle_cursor();
    clear_terminal();

    return 0;
}