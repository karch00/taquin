#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/content.h"
#include "../include/io.h"
#include "../include/render.h"


// Liste de gradients
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
const struct gradient kaltsit = {
    {180, 200, 170},  
    {230, 240, 225}   
};
const struct gradient GRADIENT_LIST[7] = {pink2blue, red2purple, forest, pink2yellow, weathergirl, coil, kaltsit};
const int GRADIENT_LIST_SIZE = 7;


// Selectionne une gradiente aleatoire pour le titre
struct gradient get_gradient() {
    int random_idx;
    struct gradient selected_gradient;
   
    // On selectione une gradiente aleatoire
    random_idx = rand() % GRADIENT_LIST_SIZE;
    selected_gradient = GRADIENT_LIST[random_idx];
    
    return selected_gradient;
}

// Calcule combien de R, G et B on doit ajouter a chaque ligne pour avoir une gradiente lineaire
// pour le nombre de lignes donne
void get_gradient_step(struct gradient grad, int lines, float rgb_output[3]) {
    int color_i, color_f, rgb_steps[3];
    
    for (int i = 0; i < 3; i++) {
        color_i = grad.rgb_i[i];
        color_f = grad.rgb_f[i];

        // Si le color de depart est plus grande que celui d'arrive, step negative 
        // Cast float pour arreter les betises de l'IDE
        if (color_i > color_f) {
            rgb_output[i] = -(float)(color_i - color_f) / lines;
        }
        // Sinon, step positive
        else {
            rgb_output[i] = (float)(color_f - color_i) / lines;
        }
    }
}

// Print le titre a la position row, column avec une gradiente appliquee
// La position est equivalente au corner top left
int print_title(const int title_size[2], int row, int column, struct gradient grad, int flush) {
    // Variables de taille
    int title_rows = title_size[0];
    int title_columns = title_size[1];
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
    for (int i = 0; i < title_rows; i++) {
        // Format la ligne et append a formatted_title. On cast float en int pour R G B valides
        snprintf(formatted_line, title_columns+25, "\033[38;2;%i;%i;%im%s\033[0m", (int)r, (int)g, (int)b, TITLE[i]); 
        strncpy(formatted_title[i], formatted_line, title_columns + 25);
        
        // Ajout de step de couleur
        r += r_step;
        g += g_step;
        b += b_step;
    }

    // Print le titre a partir des coordonnees
    for (int i = 0; i < title_rows; i++) {
        print_line(formatted_title[i], row+i, column, NOFLUSH);
    }
    if (flush) return fflush(stdout);

    return 0;
}

// Print les options initiales. Ajoute un curseur a la ligne de loption selectionnee
// La position est equivalente au corner top left. Ajuste automatiquement pour afficher le curseur a l'option.
int print_options(const int options_size[2], int option, int row, int column, int flush) {
    // Variables de taille
    int options_rows = options_size[0];
    int options_columns = options_size[1];
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
    if (flush) return fflush(stdout);

    return 0;
}


int print_controls(const int controls_size[2], int row, int column, int flush) {
    // Variables de taille
    int controls_rows = controls_size[0];
    int controls_columns = controls_size[1];

    // Print des controles
    for (int i = 0; i < controls_rows; i++) {
        print_line(CONTROLS[i], row+i, column, NOFLUSH);
    }
    if (flush) return fflush(stdout);

    return 0;
}

// Print main menu - Titre et options initiales
// Print le titre et les options initiales sans padding, avec les options sous le titre au centre
int print_main_menu(const int title_size[2], const int options_size[2], int title_row, int title_column, int options_row, int options_column) {
    // Gradiente aleatoire
    struct gradient grad = get_gradient();

    // Print titre
    print_title(title_size, title_row, title_column, grad, NOFLUSH);
    print_options(options_size, 0, options_row, options_column, NOFLUSH);
    return fflush(stdout);
}