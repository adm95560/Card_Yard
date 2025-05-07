#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
#define NB_MAX_CARTES 150

// Codes couleur ANSI
#define RESET       "\033[0m"
#define VIOLET      "\033[35m"
#define BLEU_CLAIR  "\033[36m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define ROUGE       "\033[31m"

#include "jeu.h"
#include "affichage.h"


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

    printf("\n✅ La partie est terminée ! \n Scores :\n");
for (int i = 0; i < partie.nb_joueurs; i++) {
    printf("Joueur %d (%s) : %d points\n", i + 1, partie.joueurs[i].nom, calculer_score(&partie.joueurs[i]));
}

afficher_gagnant(&partie);
    return 0;
}
