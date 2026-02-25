#ifndef CONTENT_H
#define CONTENT_H

// Titre
const char TITLE[9][62] = {
    " _________  ________  ________  ___  ___  ___  ________      ",
    "|\\___   ___\\\\   __  \\|\\   __  \\|\\  \\|\\  \\|\\  \\|\\   ___  \\    ",
    "\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\   ",
    "     \\ \\  \\ \\ \\   __  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\  ",
    "      \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ \\  \\\\ \\  \\ ",
    "       \\ \\__\\ \\ \\__\\ \\__\\ \\_____  \\ \\_______\\ \\__\\ \\__\\\\ \\__\\",
    "        \\|__|  \\|__|\\|__|\\|___| \\__\\|_______|\\|__|\\|__| \\|__|",
    "                               \\|__|                         ",
    "\r"
};

// Options
const char OPTIONS[4][10] = {
    "  Jouer  ",
    "Controles",
    " Quitter ",
    "\r"
};

// Controles
const char CONTROLS[19][45] = {
    "            Controles de selection          ",
    "       🠡: Select. Option precedente      ",
    "       🠣: Select. Option suivante        ",
    "       ⮠: Select. Option en curseur      ",
    "",
    "               Controles de jeu             ",
    "       🠡: Deplacer case vers le haut     ",
    "       🠣: Deplacer case vers le bas      ",
    "       🠢: Deplacer case vers la droit    ",
    "       🠠: Deplacer case vers la gauche   ",
    "",
    "                  But du jeu                ",
    "   Le but du jeu est d'ordonner toutes les  ",
    "   cases de 1 a 15 en deplaceant la case    ",
    "   vide pour reemplacer les cases numerotees",
    "   de 1 a 15                                ",
    "",
    "                  > Revenir                 ",
    "\r"
};

#endif