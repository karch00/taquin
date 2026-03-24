#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/content.h"
#include "../include/io.h"
#include "../include/render.h"



// Liste de gradients
// rgb_i = rgb initial
// rgb_f = rgb final
const struct gradient pink2blue = {
    {238,130,238},
    {0,  0,  139}
};
const struct gradient red2purple = {
    {139,0  ,0  },
    {128,0,  128}
};
const struct gradient pink2yellow = {
    {255, 182, 193},
    {255, 255, 0  }
};
const struct gradient forest = {
    {34 ,139,34 },
    {139,69 ,19 }
};
const struct gradient weathergirl = {
    {136, 235, 158},
    {136, 191, 235}
};
const struct gradient coil = {
    {255, 165, 0  },
    {0  , 255, 255}
};
const struct gradient kalcite = {
    {160, 180, 150},  
    {230, 240, 225}   
};
const struct gradient talulah = {
    {225, 105, 45},
    {95, 20, 20}
};

const struct gradient GRADIENT_LIST[8] = {pink2blue, red2purple, forest, pink2yellow, weathergirl, coil, kalcite, talulah};
//const struct gradient GRADIENT_LIST[1] = {talulah};
const int GRADIENT_LIST_SIZE = sizeof(GRADIENT_LIST) / sizeof(GRADIENT_LIST[0]); // Pas de valeur fixe car ajout de gradient toujours possible


// Selectionne une gradiente aleatoire pour le titre
struct gradient get_gradient() {
    int random_idx;
    struct gradient selected_gradient;
   
    // On selectione une gradiente aleatoire
    // Seed pour rand() initialisee en main.c
    random_idx = rand() % GRADIENT_LIST_SIZE;
    selected_gradient = GRADIENT_LIST[random_idx];
    
    return selected_gradient;
}

// Calcule combien de R, G et B on doit ajouter a chaque ligne pour avoir une gradiente lineaire pour la gradiente et le nombre de lignes donne
void get_gradient_step(struct gradient grad, int lines, float rgb_output[3]) {
    int color_i, color_f, rgb_steps[3];
    
    for (int i = 0; i < 3; i++) {
        color_i = grad.rgb_i[i];
        color_f = grad.rgb_f[i];

        // Si le color de depart est plus grande que celui final, step negative 
        if (color_i > color_f) {
            rgb_output[i] = -(float)(color_i - color_f) / lines;
        }
        // Sinon, step positive
        else {
            rgb_output[i] = (float)(color_f - color_i) / lines;
        }
    }
}

// Print le titre a la position [row, column] avec une gradiente appliquee. Si FLUSH alors print instantanee
// Anchor de position top left.
void print_title(int row, int column, struct gradient grad, int flush) {
    // Variables de taille
    int title_rows = TITLE_SIZE[0];
    int title_columns = TITLE_SIZE[1];
    // Variables de string
    char formatted_title[title_rows][title_columns + 25];
    char formatted_line[title_columns + 25];
    // Variables de couleur
    float color_steps[3], r, r_step, g, g_step, b, b_step;

    // Valeurs des couleurs initiales
    get_gradient_step(grad, title_rows, color_steps);
    r = grad.rgb_i[0];
    r_step = color_steps[0];
    g = grad.rgb_i[1];
    g_step = color_steps[1];
    b = grad.rgb_i[2];
    b_step = color_steps[2];
    
    // Parcour des lignes du titre pour appliquer format de couleur
    // Ajoute le code ANSI pour etablir le couleur a tous les caracteres dans la ligne
    for (int i = 0; i < title_rows; i++) {
        // Format la ligne et append a formatted_title. On cast float en int pour R G B valides
        snprintf(formatted_line, title_columns+25, "\033[38;2;%i;%i;%im%s\033[0m", (int)r, (int)g, (int)b, TITLE[i]); 
        strncpy(formatted_title[i], formatted_line, title_columns + 25); // 25 = len maximal du code ANSI
        
        // Ajout de step de couleur
        r += r_step;
        g += g_step;
        b += b_step;
    }

    // Print le titre a partir des coordonnees
    for (int i = 0; i < title_rows; i++) {
        print_line(formatted_title[i], row+i, column, NOFLUSH);
    }
    if (flush) fflush(stdout);
}

// Print les options initiales. Ajoute un curseur a la ligne de l'option selectionnee
// Anchor de position top left. Adjuste automatiquement pour afficher le curseur a l'option selecitonnee
void print_options(int option, int row, int column, int flush) {
    // Variables de taille
    int options_rows = OPTIONS_SIZE[0];
    int options_columns = OPTIONS_SIZE[1];
    // Variable string option selectionnee
    char formatted_option[options_columns + 2];
    
    // Print des options
    for (int i = 0; i < options_rows; i++){
        // Ajout du curseur si i = option
        if (option == i) {
            snprintf(formatted_option, options_columns + 2, "> %s", OPTIONS[i]);
            print_line(formatted_option, row + i, column - 2, NOFLUSH);
        }
        // On ajoute pas le curseur
        else {
            snprintf(formatted_option, options_columns + 2, "  %s", OPTIONS[i]);
            print_line(formatted_option, row + i, column - 2, NOFLUSH);
        }
    }
    if (flush) fflush(stdout);
}

// Print les controles.
// Anchor de position top left.
void print_controls(int row, int column, int flush) {
    // Variables de taille
    int controls_rows = CONTROLS_SIZE[0];
    int controls_columns = CONTROLS_SIZE[1];

    // Print des controles
    for (int i = 0; i < controls_rows; i++) {
        print_line(CONTROLS[i], row+i, column, NOFLUSH);
    }
    if (flush) fflush(stdout);
}

// Print main menu - Titre et options initiales
// Print le titre et les options initiales sans padding, avec les options sous le titre au centre
// Anchor de position top left
void print_main_menu(int title_row, int title_column, int options_row, int options_column) {
    // Gradiente aleatoire
    struct gradient grad = get_gradient();

    // Print titre et options, flush
    print_title(title_row, title_column, grad, NOFLUSH);
    print_options(0, options_row, options_column, NOFLUSH);
    
    fflush(stdout);
}

// Print case a la position [row, column]
// Anchor de position top left
void print_case(int row, int column, int case_value) {
    // Variables de taille
    int case_rows = CASE_SIZE[0];
    int case_columns = CASE_SIZE[1];
    // Variables de formatting
    int row_to_format = case_rows / 2;
    char preformatted_row[case_columns+1], formatted_row[case_columns];
    
    // Printing loop
    for (int i = 0; i < case_rows; i++) {
        // Check si row = a formatter
        if (i == row_to_format) {
            // Check si value = 0, on replace valeur de case par 2 space 
            if (!case_value) {
                snprintf(formatted_row, case_columns, CASE[i], "  ");
            }
            // Sinon, on replace le format %s par format de int %2i puis avec le valeur de la case
            else {
                snprintf(preformatted_row, case_columns+1, CASE[i], "%2i");
                snprintf(formatted_row, case_columns, preformatted_row, case_value);
            }
            print_line(formatted_row, row+i, column, NOFLUSH);
        }
        // Si pas a formatter, print directement
        else print_line(CASE[i], row+i, column, NOFLUSH);
    }
}

// Print l'ensemble de lignes de cases pour former le tableau complet
// Anchor de position top left.
void print_gameboard(int row, int column, int case_values[4][4]) {
    // Variables de taille
    int case_rows = CASE_SIZE[0];
    int case_columns = CASE_SIZE[1];

    // Loop de print
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // On print chaque case a sa position
            print_case(row + case_rows*i, column + case_columns*j, case_values[i][j]);
        }
    }
    fflush(stdout);
}