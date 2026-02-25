#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include "../include/termctrl.h"


// On toggle raw et echo mode pour avoir une experience TUI
int toggle_tui_mode(struct termios config) {
    static int TUI_ENABLED = 0;

    // On change la valeur des bits
    switch (TUI_ENABLED) {
        case 0:
            // Modifie les flags de la terminal dans le scope local, pas global    
            config.c_lflag &= ~ (ICANON | ECHO);
            break;
    }
    // Pas besoin de modifier les flags si case 1, on passe le config original
    TUI_ENABLED = !TUI_ENABLED;

    return tcsetattr(STDIN_FILENO, 0, &config);
}

// Active ou Desactive l'affichage du cursor dans la terminal en utilisant le code ANSI correspondant
void toggle_cursor() {
    static int CURSOR_ENABLED = 1;
    char mode;

    // On change le charactere d'echape correspondant a enable ou disable et on flip son valeur
    switch (CURSOR_ENABLED) {
        case 1:
            mode = 'l';
            break;
        case 0:
            mode = 'h';
            break;
    }
    CURSOR_ENABLED = !CURSOR_ENABLED;
 
    printf("\033[?25%c", mode);
}

// Prend la taille de la terminal dans l'etat actuel en rows et columns
int get_termsize(int output[2]) {
    // Structure window size, on prend sa valeur depuis le file de terminal
    int columns, rows, code;
    struct winsize size;
    code = ioctl(STDIN_FILENO, TIOCGWINSZ, &size);

    // On assigne les valeurs de colonne et row
    output[0] = size.ws_row;
    output[1] = size.ws_col;

    return code;
}