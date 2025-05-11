#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Dimensions de la grille
#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
#define NB_MAX_CARTES 150

// Codes couleur ANSI pour affichage coloré dans le terminal
#define RESET       "\033[0m"
#define VIOLET      "\033[35m"
#define BLEU_CLAIR  "\033[36m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define ROUGE       "\033[31m"

// Inclusion des fichiers d'en-tête définissant les structures et fonctions associées
#include "jeu.h"
#include "affichage.h"

/// Fonction d'affichage d'une ligne de la grille d'un joueur
void afficher_ligne_grille(const Carte ligne[]) {
    for (int i = 0; i < 4; i++) { // Chaque carte est affichée sur 4 lignes
        for (int c = 0; c < COLONNES; c++) {
            Carte carte = ligne[c];  // On récupère la carte de la colonne c
            // Détermine la couleur si la carte est visible
            const char *couleur = carte.visible ? couleur_carte(carte.valeur) : "";

            switch (i) {
                case 0:
                    // Première ligne : haut de la carte
                    printf("%s╔════╗%s ", couleur, RESET);
                    break;

                case 1:
                    // Deuxième ligne : valeur ou texte "CARD"
                    if (carte.visible)
                        printf("%s║%3d ║%s ", couleur, carte.valeur, RESET);
                    else
                        printf("║CARD║ ");
                    break;

                case 2:
                    // Troisième ligne : vide ou texte "YARD"
                    if (carte.visible)
                        printf("%s║    ║%s ", couleur, RESET);
                    else
                        printf("║YARD║ ");
                    break;

                case 3:
                    // Dernière ligne : bas de la carte
                    printf("%s╚════╝%s ", couleur, RESET);
                    break;
            }
        }
        printf("\n"); // Retour à la ligne après chaque ligne de l'affichage graphique
    }
}

/// Affiche la grille entière d'un joueur (3 lignes)
void afficher_grille_joueur(const Joueur *joueur) {
    for (int l = 0; l < LIGNES; l++) {
        afficher_ligne_grille(joueur->grille[l]);  // Affiche chaque ligne de la grille
    }
}

/// Affiche la table de jeu avec tous les joueurs et la défausse
void afficher_table(const Partie *partie) {
    // En-tête esthétique de la table
    printf("\n");
    printf("\033[31m");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                      🎴 TABLE CARD YARD 🎴                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m");

    // Affiche la grille de chaque joueur avec son nom
    for (int i = 0; i < partie->nb_joueurs; i++) {
        printf("\x1b[1;34m🎲 Joueur %d : \x1b[1;33m%s\x1b[0m\n", i + 1, partie->joueurs[i].nom);
        afficher_grille_joueur(&partie->joueurs[i]);
    }

    // Affiche la défausse actuelle si elle est active
    if (partie->defausse_active) {
        printf("\nDéfausse actuelle : ");
        const char *couleur = couleur_carte(partie->defausse.valeur);
        printf("%s[ %d ]%s\n", couleur, partie->defausse.valeur, RESET);
    } else {
        printf("\nDéfausse vide.\n");
    }
}

/// Affiche le gagnant et le perdant à la fin de la partie
void afficher_gagnant(const Partie *partie) {
    int min_score = calculer_score(&partie->joueurs[0]);
    int max_score = min_score;
    int gagnant_index = 0;
    int perdant_index = 0;

    // On parcourt tous les joueurs pour trouver le gagnant (score le plus bas)
    for (int i = 1; i < partie->nb_joueurs; i++) {
        int score = calculer_score(&partie->joueurs[i]);
        if (score < min_score) {
            min_score = score;
            gagnant_index = i;
        }
        if (score > max_score) {
            max_score = score;
            perdant_index = i;
        }
    }

    // Affichage stylisé du message de victoire
    printf("\n");
    printf("🎊🎊🎊===========================================================🎊🎊🎊\n");
    printf("🎉             🌟🌟🌟  FÉLICITATIONS  🌟🌟🌟                🎉\n");
    printf("🎖️       Le joueur ** %s ** remporte la partie avec %d points !       🎖️\n",
           partie->joueurs[gagnant_index].nom, min_score);
    printf("🏆              🥇🥇 LE GRAND MAÎTRE DU CARD YARD 🥇🥇              🏆\n");
    printf("🎊🎊🎊===========================================================🎊🎊🎊\n");

    // Message humoristique pour le perdant
    printf("\n😅 Et pendant ce temps, %s termine avec %d points...\n",
           partie->joueurs[perdant_index].nom, max_score);
    printf("💥 Courage ! Même les plus grands ont commencé avec une défaite 😎\n");
}
