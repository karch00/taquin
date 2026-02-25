#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/render.h"
#include "../include/termctrl.h"
#include "../include/io.h"
#include "../include/constants.h"

int main() {
    // ####################
    // ####### INIT #######
    // ####################

    // Init des variables de terminal
    struct termios termconf;
    int terminal_size[2];

    tcgetattr(STDIN_FILENO, &termconf);
    if (get_termsize(terminal_size)) return -1; // Si le code return n'est 0, error
    
    // On assure un minimum de taille de terminal, sinon print et exit
    if (terminal_size[0]<MIN_TERMSIZE[0] || terminal_size[1]<MIN_TERMSIZE[1]) {
        printf("Taille de terminal trop petit!\n");
        return 0;
    }
    
    // On active le mode TUI complet
    toggle_tui_mode(termconf);
    toggle_cursor();
    clear_terminal();

    // Init random seed pour generer la gradiente et le tableau
    srand(time(NULL));




    // ###################
    // ####### JEU #######
    // ###################
    // Variables de selection
    int key;
    int main_menu_option;
    bool continuer_jeu = true;
    bool selectionner_options = true;
    // Variables de taille
    int title_rows = TITLE_SIZE[0];
    int title_columns = TITLE_SIZE[1];
    int options_rows = OPTIONS_SIZE[0];
    int options_columns = OPTIONS_SIZE[1];
    int controls_rows = CONTROLS_SIZE[0];
    int controls_columns = CONTROLS_SIZE[1];
    // Variables de coordonnees pour le main menu
    int main_menu_title_row = (terminal_size[0] / 2) - title_rows;  
    int main_menu_title_column = (terminal_size[1] / 2) - (TITLE_SIZE[1] / 2) + 1;
    int main_menu_options_row = main_menu_title_row + title_rows + 2;
    int main_menu_options_column = main_menu_title_column + (title_columns / 2) - (options_columns / 2);
    int main_menu_controls_row = main_menu_title_row + title_rows + 2;
    int main_menu_controls_column = main_menu_title_column + (title_columns / 2) - (controls_columns / 2);

    // On print le menu principal
    print_main_menu(TITLE_SIZE, OPTIONS_SIZE,main_menu_title_row, main_menu_title_column, main_menu_options_row, main_menu_options_column);

    main_menu_option = 0;
    
    // Boucle selection d'options
    while (selectionner_options) {
        // On assigne la touche a l'option adequate
        key = get_key();
        switch (key) {
            // Move options up
            case UP:
                if (main_menu_option == 0) main_menu_option = 2;
                else main_menu_option -= 1;
                print_options(OPTIONS_SIZE, main_menu_option, main_menu_options_row, main_menu_options_column, FLUSH);
                break;
            
            // Move options down
            case DOWN:
                if (main_menu_option == 2) main_menu_option = 0;
                else main_menu_option += 1;
                print_options(OPTIONS_SIZE, main_menu_option, main_menu_options_row, main_menu_options_column, FLUSH);
                break;

            // Select option
            case ENTER:
                    // Jouer                        
                    // Voir controles
                    if (main_menu_option == 1) {
                        // Print les controles et attendre a pressioner Enter pour revenit
                        print_controls(CONTROLS_SIZE, main_menu_controls_row, main_menu_controls_column, FLUSH);
                        while (get_key() != ENTER); 
                        // Effacer les controles, print options a nouveau et positioner curseur a 0
                        erase_multiline(controls_rows, main_menu_controls_row, main_menu_controls_column, FLUSH);
                        print_options(OPTIONS_SIZE, 0, main_menu_options_row, main_menu_options_column, FLUSH);
                        main_menu_option = 0;
                    }
                    // Quitter
                    else if (main_menu_option == 2) {
                        continuer_jeu = false;
                        selectionner_options = false;
                    }
                    break;

            // Key sans valeur 
            default:
                break;
        }
    }


    
    
    // ###################
    // ##### CLEANUP #####
    // ###################

    // Return to normal
    toggle_tui_mode(termconf);
    toggle_cursor();
    clear_terminal();
    return 0;
}