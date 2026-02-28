#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/io.h"

// Efface tout le texte curament present dans la terminal et positione le curseur dans la case initiale
void clear_terminal() {
    printf("\033[2J\033[H");
}

// Print une ligne de texte a partir de la position indiquee a la ligne (row) et la colonne (column).
// Modifie la ligne instantaneement si flush est true. 
int print_line(const char *text, int row, int column, bool flush) {
    // Se positionner a ligne x colonne y et print le texte
    printf("\033[%i;%iH", row, column);
    printf("%s", text);
    // Si flush specified, afficher le texte en buffer
    if (flush == FLUSH) return fflush(stdout);

    return 0;
}

// Efface tout le texte curament present dans la ligne row, optionelement a partir de la colonne column
int erase_line(int row, int column, bool flush) {
    // On se positione a la ligne et la colonne, et on efface a partir du curseur
    printf("\033[%i;%iH\033[K", row, column);
    // Si flush, flush le buffer
    if (flush == FLUSH) return fflush(stdout);
    
    return 0;
}

// Efface le texte des lignes row specifiees a partir de la colonne column
int erase_multiline(int lines, int row, int column, bool flush) {
    int code;
    // On parcour les lignes et on erase a partir de leurs colonnes 
    for (int i = 0; i < lines; i++) {
        code = erase_line(row + i, column, NOFLUSH);
        if (code) return code;
    }
    // SI flush, flush buffer
    if (flush == FLUSH) code = fflush(stdout);

    return code;
}

// Lit quand on appuye sur une touche et valide que ce soit dedans les controles
// Renvoie la valeur definie de la touche appuye, si definie
int get_key() {
    char byte1, byte2, byte3;
    // Valeur des touches especiaux compose de 3 bytes
    while (1) {
        // On lis le premier caractere et on valide
        read(STDIN_FILENO, &byte1, 1);
        if (byte1 == '\n') return ENTER;
        else if (byte1 == 'q') return QUIT;
        if (byte1 != '\033') continue;

        // Pareil pour le deuxieme
        read(STDIN_FILENO, &byte2, 1);
        if (byte2 != '[') continue;

        // Pareil pour le troiseme
        // On renvoie la touche correspondante, si ne correspond pas on continue le loop
        read(STDIN_FILENO, &byte3, 1);
        switch (byte3) {
            case 'A':
                return UP;
            case 'B':
                return DOWN;
            case 'C':
                return RIGHT;
            case 'D':
                return LEFT;
            default:
                continue;
        }
    }
}