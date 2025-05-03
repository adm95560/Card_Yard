#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"
#include "affichage.c"

int main() {
    srand((unsigned)time(NULL));

    Partie partie;
    debut_partie(&partie);
    distribuer_cartes(&partie);

    while (!partie_terminee(&partie)) {
        afficher_table(&partie);
        tour_joueur(&partie);
        partie.joueur_actuel = (partie.joueur_actuel + 1) % partie.nb_joueurs;
    }

    printf("\n✅ La partie est terminée ! Scores :\n");
    for (int i = 0; i < partie.nb_joueurs; i++) {
        printf("Joueur %d (%s) : %d points\n", i + 1, partie.joueurs[i].nom, calculer_score(&partie.joueurs[i]));
    }

    return 0;
}
