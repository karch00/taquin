# Jeu du taquin
[> Repo github <](https://github.com/karch00/taquin)
### Regles du Jeu
Dans le jeu du taquin le joueur doit deplacer les nombres du 1 au 15 dans un carreau 4x4 jusqu'a ordonner
toutes les pieces en ordre croissant. Le joueur ne peut pas deplacer les nombres comme il veut, il doit se
servir d'un carreau vide qui pourra etre remplace par un des 4 nombres adjacentes. <br>

> [!TIP]
> Le joueur gagne quand toutes les cases sont ordennees de 1 au 15 avec la case vide en derniere place.

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

### Controles

> **[^]** - Option precedente / Deplacer case vide vers le haut<br>
> **[>]** - Deplacer case vide vers la droite<br>
> **[v]** - Option suivante / Deplacer case vide vers le bas<br>
> **[<]** - Deplacer case vide vvers la gauche<br>

> **[ENTER]** - Selectionner option<br>
> **[q]** - Quitter le jeu / Aller vers le menu

---

# Details techniques
Pour developper ce jeu, le probleme principal c'etait de comprendre comment les terminaux fonctionnent
et comment l'appliquer dans le code.<br>
En plus de cela, j'ai du developper un systeme pour formatter, afficher et appliquer la logique de jeu, ce qui
entraine la creation du tableau aleatoire, l'affichage du tableau par cases, comment reemplacer la case vide par une autre.

A l'aide de plusieurs sources, j'ai fait une recherche individuelle qui m'a amene a la structure du jeu actuelle.<br>
J'ai du implementer des headers pour pouvoir importer les differentes fonctionnes vers les autres fichiers C.

Le code est compris de plusieurs fichiers. Voici le resume du code.<br>

### 0 - Les terminaux
#### I) Fonctionnement des terminaux
Sous Linux, une terminal est une interface qui sert que a lire sur une entree et a afficher du texte sur une sortie.
Toute la logique qui permet d'executer des commandes et des instructions a lieu dans la shell, le programme ou
le process qu'on a lance.<br>
Une session de terminal est associee a un fichier trouve dans `/dev/pts/X` ou X est un nombre. Ce fichier contient le texte
concernant la session actuelle de TTY.

Ainsi, on represente la terminal comme un peripherique. Ecrire vers ce fichier permet d'afficher ce qu'on a ecris dans la terminal.
Lire ce fichier permet de voir ce qui est deja affiche avant d'envoyer la commande en pressionant Enter.

C'est ainsi qu'on manipule les etats de la terminal et le texte affiche.

> [!TIP]
> Pour tester cette fonctionnement, ouvrez 2 terminaux.
> 
> Executez la commande `tty` sur la premiere et copiez le chemin.
>
> Sur la deuxieme executez la commande<br>
> `echo "Hello" | tee {CHEMIN}`<br>
> 
> Regardez ce qui s'affiche dans la premiere terminal.

#### II) Mode des terminaux
Les terminaux ont des modes differentes de comportement et d'affichage.

Le mode basique d'interaction s'appelle **Mode Canonique**. Ce mode affiche le caractere le moment qu'on appuye sur une touche
et attends a qu'on pressione sur Enter pour envoyer la commande vers la pipeline de processus dans l'OS.<br>
Le mode dont on base le jeu s'appelle **Mode Cru** ou **Raw Mode**. Ici, quand on appuye sur une touche, elle est envoye
directement a la pipeline de processus de l'OS sans attendre a appuyer sur ENTER. Cela nous permet de processer des commandes
instantaneement dans notre programme des qu'on appuye la touche.

#### III) Affichages speciaux
Sous Linux, l'affichage se base sur **le modele POSIX**. Ce modele offre des nombreux **codes ANSI** pour modifier l'affichage de certains
elements dans la terminal.

Les codes ANSI se forment par le format: `\033[CODE TEXTE`<br>
Ou `\033` est le caractere d'echappe qui va indiquer que c'est un code ANSI; `CODE` est un code predefini et `TEXTE` c'est le texte
a formatter par le code (optionnel).

#### IV) Mode TUI
En appliquant les modes et les notions precedentes, on arrive a une experience qu'on appelle **TUI (Terminal User Interface)**.<br>
Cette experience est interactive et permet l'execution et affichage instantanee des commandes.

Le mode TUI resemble le mode **GUI (Graphic user interface)**, mais reste plus basique avec des graphiques purement basees sur du texte en
terminal.

### 1 - constants.c + content.c
Ces fichiers contiennent les valeurs des constants et du contenu principal.<br>
Permet de ne pas declarer les valeurs a chaque fichier, restant coherent dans le scope global mais a la fois
ne compliquant pas le code pour eviter des fonctions pour lire des fichiers externes (Des .yml, .json, .txt, ...)
- **constants.c** contient des valeurs constants generiques (Taille terminal minimale, Tableau gagnant)
- **content.c** contient des valeurs liees au contenu principal (Titre, Options, ...) et ses tailles.

### 2 - termctrl.c
Contient le code permettant de manipuler les etats de la terminal<br>
Permet de simplifier le control d'etat de terminal en creant des fonctions wrapper pour des fonctions de base dans les
bibliotheques suivantes.

Se base sur les bibliotheques: 
- **termios.h**: Permet le control des etats de terminal en modifiant leurs attributs
- **unistd.h**: Dans notre code, permet de controler le stdin (indiquer et manipuler le fichier de terminal)
- **stdbool.h**: Offre des statements booleans
- **sys/ioctl.h**: Dans notre code, permet de lire la taille de la terminal

### 3 - io.c
Contient le code permettant de manipuler l'affichage basique et l'input des touches.<br>
Offre des fonctions wrapper pour l'affichage et l'input de touches dediees au mode de terminal TUI.

Se base sur les bibliotheques: **stdio.h  unistd.h**
- **stdio.h**: Permet l'affichage sur stdout
- **unistd.h** -

### 4 - render.c
Contient le code qui permet d'afficher le contenu d'une facon formattee: Titre, Options, tableau.

Se base sur les bibliotheques:
- **string.h**: Permet de manipuler des strings d'une facon secure.
- **stdlib.h**: Dans le code, offre la fonction rand() pour generer un nombre aleatoire
- **../io.h**: Permet d'afficher et manipuler le texte dans la terminal en TUI
- **../content.h**: Offre les tailles des tableaux du contenu
- **stdio.h** -

### 5 - game.c
La logique principale du jeu est ici. Offre la creation et initialisation du tableau et le boucle principal deu jeu.

Se base sur les bibliotheques:
- **../render.h**: Offre les fonctions d'affichage du tableau
- **../constants.h**: Offre le tableau gagnant
- **../content.h** -
- **../io.h** -
- **stdbool.h** -
- **stdlib.h** -
- **stdio.h** -
- **string.h** -

### 6 - main.c
Logique entiere du jeu. Initialise la seed pour le module random, les variables, modifie l'etat de la terminal et applique la logique
du menu principal.

Se base sur toutes les bibliotheques mentionnees precedement plus **time.h** qui offre la fonction time() pour passer en parametre l'epoch
UNIX a la seed random.

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

### Design, colors
- [patorjk - ASCII art generator](https://patorjk.com/software/taag/)
- [Pastel - CLI color tool](https://github.com/sharkdp/pastel)

### Algorithmique
- [Algorithme de Fish-Yate](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)