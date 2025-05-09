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


// Affichage d'une ligne de grille pour un joueur

void afficher_ligne_grille(const Carte ligne[]) {
    for (int i = 0; i < 4; i++) {
        for (int c = 0; c < COLONNES; c++) {
            Carte carte = ligne[c];
            const char *couleur = carte.visible ? couleur_carte(carte.valeur) : "";
            switch (i) {
                case 0:
                    printf("%s╔════╗%s ", couleur, RESET);
                    
                    break;
                
                case 1:
                   	if (carte.visible)
                        printf("%s║%3d ║%s ", couleur, carte.valeur, RESET);
                    	
                    	else
                        printf("║CARD║ ");
                    
                    break;
                
                case 2:
                	if (carte.visible)
                        	printf("%s║    ║%s ", couleur, RESET);
                    	else
                    printf("║YARD║ ");
                    
                    break;
                case 3:
                    printf("%s╚════╝%s ", couleur, RESET);
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

printf("\n");
printf("\033[31m");
printf("╔════════════════════════════════════════════════════════════════╗\n");
printf("║                      🎴 TABLE CARD YARD 🎴                     ║\n");
printf("╚════════════════════════════════════════════════════════════════╝\n\n");
printf("\033[0m");


    for (int i = 0; i < partie->nb_joueurs; i++) {
printf("\x1b[1;34m🎲 Joueur %d : \x1b[1;33m%s\x1b[0m\n", i + 1, partie->joueurs[i].nom);
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


void afficher_gagnant(const Partie *partie) {
    int min_score = calculer_score(&partie->joueurs[0]);
    int max_score = min_score;
    int gagnant_index = 0;
    int perdant_index = 0;

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

    // Message de victoire esthétique
    printf("\n");
    printf("🎊🎊🎊===========================================================🎊🎊🎊\n");
    printf("🎉             🌟🌟🌟  FÉLICITATIONS  🌟🌟🌟                🎉\n");
    printf("🎖️       Le joueur ** %s ** remporte la partie avec %d points !       🎖️\n",
           partie->joueurs[gagnant_index].nom, min_score);
    printf("🏆              🥇🥇 LE GRAND MAÎTRE DU CARD YARD 🥇🥇              🏆\n");
    printf("🎊🎊🎊===========================================================🎊🎊🎊\n");

    // Message fun pour le perdant
    printf("\n😅 Et pendant ce temps, %s termine avec %d points...\n",
           partie->joueurs[perdant_index].nom, max_score);
    printf("💥 Courage ! Même les plus grands ont commencé avec une défaite 😎\n");
}
