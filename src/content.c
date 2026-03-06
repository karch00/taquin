#include "../include/content.h"

const char TITLE[11][157] = {
" ███████████                                 ███            ",
"▒█▒▒▒███▒▒▒█                                ▒▒▒             ",
"▒   ▒███  ▒   ██████    ████████ █████ ████ ████  ████████  ",
"    ▒███     ▒▒▒▒▒███  ███▒▒███ ▒▒███ ▒███ ▒▒███ ▒▒███▒▒███ ",
"    ▒███      ███████ ▒███ ▒███  ▒███ ▒███  ▒███  ▒███ ▒███ ",
"    ▒███     ███▒▒███ ▒███ ▒███  ▒███ ▒███  ▒███  ▒███ ▒███ ",
"    █████   ▒▒████████▒▒███████  ▒▒████████ █████ ████ █████",
"   ▒▒▒▒▒     ▒▒▒▒▒▒▒▒  ▒▒▒▒▒███   ▒▒▒▒▒▒▒▒ ▒▒▒▒▒ ▒▒▒▒ ▒▒▒▒▒ ",
"                           ▒███                             ",
"                           █████                            ",
"                          ▒▒▒▒▒                             "
};

const int TITLE_SIZE[2] = {sizeof(TITLE) / sizeof(TITLE[0]), sizeof(TITLE[0]) / sizeof(TITLE[0][0])};

// Options
const char OPTIONS[4][10] = {
    "  Jouer  ",
    "Controles",
    " Quitter ",
    "\r"
};
const int OPTIONS_SIZE[2] = {sizeof(OPTIONS) / sizeof(OPTIONS[0]), sizeof(OPTIONS[0]) / sizeof(OPTIONS[0][0])};

// Controles
const char CONTROLS[23][45] = {
    "    -------[ Controles d'option ]-------    ",
    "      [^]: Select. Option precedente        ",
    "      [v]: Select. Option suivante          ",
    "  [ENTER]: Confirmer Option en curseur      ",
    "      [q]: Quitter le jeu / Revenir         ",
    "",
    "",
    "    -------[  Controles du jeu  ]-------    ",
    "      [^]  Deplacer case vers le haut       ",
    "      [v]  Deplacer case vers le bas        ",
    "      [>]  Deplacer case vers la droit      ",
    "      [<]  Deplacer case vers la gauche     ",
    "",
    "",
    "    -------[   Comment jouer?   ]-------    ",
    " Le but du jeu est de reordonner toutes les ",
    "    cases de 1 a 15 en deplaceant la case   ",
    "  vide pour reemplacer les cases adjacentes ",
    "   jusqu'a avoir ordonnee toutes les cases  ",
    "     avec la case vide en derniere place    ",
    "",
    "                 > Revenir                  ",
    "\r"
};
const int CONTROLS_SIZE[2] = {sizeof(CONTROLS) / sizeof(CONTROLS[0]), sizeof(CONTROLS[0]) / sizeof(CONTROLS[0][0])};

// Case
const int CASE_SIZE[2] = {5, 11};
const char CASE[5][11] = {
    "+--------+",
    "|        |",
    "|   %s   |",
    "|        |",
    "+--------+"
};
