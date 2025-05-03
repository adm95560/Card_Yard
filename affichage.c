#include <stdio.h>
#include "jeu.h"

// Affichage d'une ligne de grille pour un joueur
void afficher_ligne_grille(const Carte ligne[]) {
    for (int i = 0; i < 4; i++) {
        for (int c = 0; c < COLONNES; c++) {
            Carte carte = ligne[c];
            const char *couleur = carte.visible ? couleur_carte(carte.valeur) : "";
            switch (i) {
                case 0:
                    printf("%s+-----+%s ", couleur, RESET);
                    break;
                case 1:
                    if (carte.visible)
                        printf("%s| %3d |%s ", couleur, carte.valeur, RESET);
                    else
                        printf("|CARD | ");
                    break;
                case 2:
                    printf("|YARD | ");
                    break;
                case 3:
                    printf("%s+-----+%s ", couleur, RESET);
                    break;
            }
        }
        printf("\n");
    }
}

// Afficher la grille de chaque joueur
void afficher_grille_joueur(const Joueur *joueur) {
    for (int l = 0; l < LIGNES; l++) {
        afficher_ligne_grille(joueur->grille[l]);
    }
}

// Affichage de la table avec disposition des joueurs
void afficher_table(const Partie *partie) {
    printf("\n===================== TABLE CARD YARD =====================\n\n");

    for (int i = 0; i < partie->nb_joueurs; i++) {
        printf("\nJoueur %d (%s) :\n", i + 1, partie->joueurs[i].nom);
        afficher_grille_joueur(&partie->joueurs[i]);
    }

    if (partie->defausse_active) {
        printf("\nDéfausse actuelle : ");
        const char *couleur = couleur_carte(partie->defausse.valeur);
        printf("%s[ %d ]%s\n", couleur, partie->defausse.valeur, RESET);
    } else {
        printf("\nDéfausse vide.\n");
    }
}
