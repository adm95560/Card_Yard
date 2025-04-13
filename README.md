# Card_Yard

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NB_MAX_JOUEURS 8
#define LIGNES 3
#define COLONNES 4
#define NB_MAX_CARTES 150


typedef struct {
    int valeur;
    bool visible;
} Carte;

typedef struct {
    char nom[20];
    Carte grille[LIGNES][COLONNES];
} Joueur;

typedef struct {
    Joueur joueurs[NB_MAX_JOUEURS];
    Carte pioche[NB_MAX_CARTES];
    int taille_pioche;
    int index_pioche;
    int nb_joueurs;
    int joueur_actuel;
} Partie;


void debut_partie(Partie *partie) {
    printf("\n====================================CARD YARD===================================\n\nBonjour et bienvenue aux jeu du Card Yard!\nLes règles sont simples chaque joueurs possède 12 cartes à vous de vous en débarrasser le plus vite possible\n BONNE CHANCE ;) \n\n");

    do {
        printf("Nombre de joueurs (2-%d) : ", NB_MAX_JOUEURS);
        scanf("%d", &partie->nb_joueurs);
       
        if (partie->nb_joueurs < 2 || partie->nb_joueurs > 8) {
            printf("Erreur ! Vous devez choisir un nombre de joueurs entre 2 et 8 \n");
        }
    } while (partie->nb_joueurs < 2 || partie->nb_joueurs > 8);
   
    for (int i = 0; i < partie->nb_joueurs; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%s", partie->joueurs[i].nom);
    }

    partie->taille_pioche = 0;
    for (int i = -2; i <= 12; i++) {
        int quantite;
             
        if (i == -2) {
            quantite = 5;
        } else if (i == -1) {
            quantite = 10;
        } else if (i == 0) {
            quantite = 15;
        } else {
            quantite = 10;
        }

        for (int j = 0; j < quantite; j++) {
            pioche[taille_pioche].valeur = val;
            pioche[taille_pioche].visible = false;
            taille_pioche++;
        }
    }

    melanger_pioche(partie->pioche, partie->taille_pioche);
    partie->index_pioche = 0;
    partie->joueur_actuel = 0;
}

void melanger_pioche(Carte *pioche, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte tmp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = tmp;
    }
}

void distribuer_cartes(Partie *partie) {
    for (int i = 0; i < partie->nb_joueurs; i++) {
        for (int l = 0; l < LIGNES; l++) {
            for (int c = 0; c < COLONNES; c++) {
                partie->joueurs[i].grille[l][c] = partie->pioche[partie->index_pioche++];
                partie->joueurs[i].grille[l][c].visible = false;
            }
        }
        reveler_deux_cartes(&partie->joueurs[i]);
    }
}
