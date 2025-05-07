#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
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
    Joueur joueurs[MAX_JOUEURS];
    Carte pioche[NB_MAX_CARTES];
    int index_pioche;
    Carte defausse;
    bool defausse_active;
    int nb_joueurs;
    int joueur_actuel;
    int taille_pioche;
} Partie;

#endif // TYPES_H
