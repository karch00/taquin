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
const char CONTROLS[21][45] = {
    "    -------[ Controles d'option ]-------    ",
    "      [^]: Select. Option precedente        ",
    "      [v]: Select. Option suivante          ",
    "  [ENTER]: Confirmer Option en curseur      ",
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
    "  vide pour reemplacer les cases numerotes  ",
    "                 de 1 a 15                  ",
    "",
    "                 > Revenir                  ",
    "\r"
};

#endif