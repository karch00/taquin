# Jeu du taquin
[> Repo github <](https://github.com/karch00/taquin)
### Règles du Jeu
Dans le jeu du taquin, le joueur doit déplacer les nombres du 1 au 15 dans un carreau 4x4 jusqu'à ordonner
toutes les pièces en ordre croissant. Le joueur ne peut pas déplacer les nombres comme il veut, il doit se
servir d'un carreau vide qui pourra être remplacé par un des 4 nombres adjacents. <br>
 
> [!TIP]
> Le joueur gagne quand toutes les cases sont ordonnées de 1 à 15 avec la case vide en dernière place.
 
```
 ----+----+----+----          ----+----+----+----
|  5 | 11 |  4 |  8 |        |  1 |  2 |  3 |  4 |
 ----+----+----+----          ----+----+----+----
|  6 |  1 | 15 |  7 |        |  5 |  6 |  7 |  8 |
 ----+----+----+----   --->   ----+----+----+----
| 13 |    |  2 | 12 |        |  9 | 10 | 11 | 12 |
 ----+----+----+----          ----+----+----+----
|  3 | 10 |  9 | 14 |        | 13 | 14 | 15 |    |
 ----+----+----+----          ----+----+----+----
```
 
### Contrôles
 
> **[^]** - Option précédente / Déplacer case vide vers le haut<br>
> **[>]** - Déplacer case vide vers la droite<br>
> **[v]** - Option suivante / Déplacer case vide vers le bas<br>
> **[<]** - Déplacer case vide vers la gauche<br>
 
> **[ENTER]** - Sélectionner option<br>
> **[q]** - Quitter le jeu / Aller vers le menu
 
---
 
# Détails techniques
Pour développer ce jeu, le problème principal était de comprendre comment les terminaux fonctionnent
et comment l'appliquer dans le code.<br>
En plus de cela, j'ai dû développer un système pour formater, afficher et appliquer la logique de jeu, ce qui
entraîne la création du tableau aléatoire, l'affichage du tableau par cases et comment remplacer la case vide par une autre.
 
À l'aide de plusieurs sources, j'ai fait une recherche individuelle qui m'a amené à la structure du jeu actuelle.<br>
J'ai dû implémenter des headers pour pouvoir importer les différentes fonctions vers les autres fichiers C.
 
Le code est composé de plusieurs fichiers. Voici le résumé du code.<br>
 
### 0 - Les terminaux
#### I) Fonctionnement des terminaux
Sous Linux, un terminal est une interface qui sert uniquement à lire sur une entrée et à afficher du texte sur une sortie.
Toute la logique qui permet d'exécuter des commandes et des instructions a lieu dans le shell, le programme ou
le processus qu'on a lancé.<br>
Une session de terminal est associée à un fichier trouvé dans `/dev/pts/X` où X est un nombre. Ce fichier contient le texte
concernant la session actuelle de TTY.
 
Ainsi, on représente le terminal comme un périphérique. Écrire vers ce fichier permet d'afficher ce qu'on a écrit dans le terminal.
Lire ce fichier permet de voir ce qui est déjà affiché avant d'envoyer la commande en pressant Enter.
 
C'est ainsi qu'on manipule les états du terminal et le texte affiché.
 
> [!TIP]
> Pour tester ce fonctionnement, ouvrez 2 terminaux.
> 
> Exécutez la commande `tty` sur le premier et copiez le chemin.
>
> Sur le deuxième, exécutez la commande<br>
> `echo "Hello" | sudo tee {CHEMIN}`<br>
> 
> Regardez ce qui s'affiche dans le premier terminal.
 
#### II) Modes des terminaux
Les terminaux ont différents modes de comportement et d'affichage.
 
Le mode basique d'interaction s'appelle **Mode Canonique**. Ce mode affiche le caractère au moment où on appuie sur une touche
et attend qu'on appuie sur Enter pour envoyer la commande vers le pipeline de processus dans l'OS.<br>
Le mode sur lequel on base le jeu s'appelle **Mode Brut** ou **Raw Mode**. Ici, quand on appuie sur une touche, elle est envoyée
directement au pipeline de processus de l'OS sans attendre d'appuyer sur ENTER. Cela nous permet de traiter des commandes
instantanément dans notre programme dès qu'on appuie sur la touche.
 
#### III) Affichages spéciaux
Sous Linux, l'affichage se base sur **le modèle POSIX**. Ce modèle offre de nombreux **codes ANSI** pour modifier l'affichage de certains
éléments dans le terminal.
 
Les codes ANSI se forment par le format : `\033[CODE TEXTE`<br>
Où `\033` est le caractère d'échappement qui va indiquer que c'est un code ANSI ; `CODE` est un code prédéfini et `TEXTE` c'est le texte
à formater par le code (optionnel).
 
#### IV) Mode TUI
En appliquant les modes et les notions précédentes, on arrive à une expérience qu'on appelle **TUI (Terminal User Interface)**.<br>
Cette expérience est interactive et permet l'exécution et l'affichage instantanés des commandes.
 
Le mode TUI ressemble au mode **GUI (Graphic User Interface)**, mais reste plus basique avec des graphiques purement basés sur du texte en
terminal.
 
### 1 - constants.c + content.c
Ces fichiers contiennent les valeurs des constantes et du contenu principal.<br>
Permet de ne pas déclarer les valeurs dans chaque fichier, restant cohérent dans le scope global mais à la fois
sans compliquer le code pour éviter des fonctions lisant des fichiers externes (des .yml, .json, .txt, ...)
- **constants.c** contient des valeurs constantes génériques (taille minimale du terminal, tableau gagnant)
- **content.c** contient des valeurs liées au contenu principal (titre, options, ...) et leurs tailles.
 
### 2 - termctrl.c
Contient le code permettant de manipuler les états du terminal.<br>
Permet de simplifier le contrôle d'état du terminal en créant des fonctions wrapper pour des fonctions de base dans les
bibliothèques suivantes.
 
Se base sur les bibliothèques : 
- **termios.h** : Permet le contrôle des états du terminal en modifiant leurs attributs
- **unistd.h** : Dans notre code, permet de contrôler le stdin (indiquer et manipuler le fichier de terminal)
- **stdbool.h** : Offre des instructions booléennes
- **sys/ioctl.h** : Dans notre code, permet de lire la taille du terminal
 
### 3 - io.c
Contient le code permettant de manipuler l'affichage basique et la saisie des touches.<br>
Offre des fonctions wrapper pour l'affichage et la saisie de touches dédiées au mode de terminal TUI.
 
Se base sur les bibliothèques : **stdio.h  unistd.h**
- **stdio.h** : Permet l'affichage sur stdout
- **unistd.h** -
 
### 4 - render.c
Contient le code qui permet d'afficher le contenu d'une façon formatée : titre, options, tableau.
 
Se base sur les bibliothèques :
- **string.h** : Permet de manipuler des chaînes de caractères d'une façon sécurisée.
- **stdlib.h** : Dans le code, offre la fonction rand() pour générer un nombre aléatoire
- **../io.h** : Permet d'afficher et de manipuler le texte dans le terminal en TUI
- **../content.h** : Offre les tailles des tableaux du contenu
- **stdio.h** -
 
### 5 - game.c
La logique principale du jeu est ici. Offre la création et l'initialisation du tableau ainsi que la boucle principale du jeu.
 
Se base sur les bibliothèques :
- **../render.h** : Offre les fonctions d'affichage du tableau
- **../constants.h** : Offre le tableau gagnant
- **../content.h** -
- **../io.h** -
- **stdbool.h** -
- **stdlib.h** -
- **stdio.h** -
- **string.h** -
 
### 6 - main.c
Logique entière du jeu. Initialise la graine pour le module aléatoire, les variables, modifie l'état du terminal et applique la logique
du menu principal.
 
Se base sur toutes les bibliothèques mentionnées précédemment, plus **time.h** qui offre la fonction time() pour passer en paramètre l'epoch
UNIX à la graine aléatoire.
 
---
 
# Sources
### Terminal, TTY & ANSI
- [Linus akesson - TTY Demystified](https://www.linusakesson.net/programming/tty/)
- [Ahmad Awais - Full stack of terminals explained](https://ahmadawais.com/the-full-stack-of-terminals-explained-terminal-shell-tty-console-posix-ansi-escapes-ptys/#part-1-the-vocabulary)
- [Termios Manpage](https://www.man7.org/linux/man-pages/man3/termios.3.html)
- [Wikipedia - ANSI Codes](https://en.wikipedia.org/wiki/ANSI_escape_code)
 
### Langage C
- [GeeksforGeeks](https://www.geeksforgeeks.org/c/c-programming-language/)
- [Wikipedia - C data types](https://en.wikipedia.org/wiki/C_data_types)
 
### Design, couleurs
- [patorjk - ASCII art generator](https://patorjk.com/software/taag/)
- [Pastel - CLI color tool](https://github.com/sharkdp/pastel)
 
### Algorithmique
- [Algorithme de Fisher-Yates](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)