#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Définition des constantes pour les dimensions de la grille, le nombre maximal de joueurs et de cartes
#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
#define NB_MAX_CARTES 150

// Codes couleur ANSI pour affichage stylisé dans le terminal
#define RESET       "\033[0m"
#define VIOLET      "\033[35m"
#define BLEU_CLAIR  "\033[36m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define ROUGE       "\033[31m"

// Inclusion des fichiers d'en-tête contenant les définitions de structures et fonctions utilisées
#include "jeu.h"
#include "affichage.h"

int main() {
    // Initialisation du générateur de nombres aléatoires avec l'heure actuelle
    srand((unsigned)time(NULL));

    // Déclaration d'une structure Partie qui va contenir toutes les infos de la partie en cours
    Partie partie;

    // Démarre la partie : demande les noms, initialise la pioche, mélange, etc.
    debut_partie(&partie);

    // Distribue les cartes aux joueurs (12 cartes chacun, 2 révélées au hasard)
    distribuer_cartes(&partie);

    // Boucle principale du jeu : continue tant que la partie n'est pas terminée
    while (!partie_terminee(&partie)) {
        // Affiche la table de jeu (grilles de tous les joueurs, pioche et défausse)
        afficher_table(&partie);

        // Gère le tour du joueur actuel (piocher, échanger, révéler, etc.)
        tour_joueur(&partie);

        // Passe au joueur suivant
        partie.joueur_actuel = (partie.joueur_actuel + 1) % partie.nb_joueurs;
    }

    // Fin de partie : affichage des scores finaux
    printf("\n✅ La partie est terminée ! \n Scores :\n");
    for (int i = 0; i < partie.nb_joueurs; i++) {
        printf("Joueur %d (%s) : %d points\n", i + 1, partie.joueurs[i].nom, calculer_score(&partie.joueurs[i]));
    }

    // Affiche le ou les gagnants de la partie
    afficher_gagnant(&partie);

    return 0; // Fin du programme
}
