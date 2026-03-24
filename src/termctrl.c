#include <stdio.h>
#include <termios.h>
#include <unistd.h> 
#include <stdbool.h> 
#include <sys/ioctl.h> 
#include "../include/termctrl.h"


// Toggle raw et echo mode pour avoir une experience TUI
int toggle_tui_mode(struct termios config) {
    static int tui_enabled = 0; 

    // On change la valeur des bits
    switch (tui_enabled) {
        case 0:
            // Modifie les flags de la terminal dans le scope local, pas global   
            // Modifie les bits precis par operation bitmask 
            // Inverse mode Canonique et Echo. Si 1, devient 0. Si 0, devient 1.
            // Pas besoin de modifier les flags si case 1 (desactiver mode TUI), on passe le config original pour faire un restore default
            config.c_lflag &= ~ (ICANON | ECHO);
            break;
    }
    // Swap tui_enabled 0->1 ou 1->0
    // Reste valide entre appels de fonction car static
    tui_enabled = !tui_enabled;

    return tcsetattr(STDIN_FILENO, 0, &config);
}

// Active ou Desactive l'affichage du cursor dans la terminal en utilisant le code ANSI correspondant
void toggle_cursor() {
    static int cursor_enabled = 1;
    char mode;

    // On change le charactere d'echape correspondant a enable ou disable et on flip son valeur
    switch (cursor_enabled) {
        case 1:
            // Mode cursor on
            mode = 'l';
            break;
        case 0:
            // Cursor off
            mode = 'h';
            break;
    }
    cursor_enabled = !cursor_enabled;
 
    printf("\033[?25%c", mode);
}

// Get et Assigne la taille de la terminal dans l'etat actuel en rows et columns
int get_termsize(int output[2]) {
    // Structure window size, on prend sa valeur depuis le file de terminal
    int columns, rows, code;
    struct winsize size;

    // Return si erreur seulement (code!=0)
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size)) return 1;

    // On assigne les valeurs de colonne et row
    output[0] = size.ws_row;
    output[1] = size.ws_col;

    return 0;
}