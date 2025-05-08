#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
#define NB_MAX_CARTES 150

// Codes couleur ANSI
#define RESET "\033[0m"
#define VIOLET "\033[35m"
#define BLEU_CLAIR "\033[36m"
#define VERT "\033[32m"
#define JAUNE "\033[33m"
#define ROUGE "\033[31m"

#include "types.h"

// Fonctions d'affichage
void afficher_ligne_grille(const Carte ligne[]);
void afficher_grille_joueur(const Joueur *joueur);
void afficher_table(const Partie *partie);
void afficher_gagnant(const Partie *partie);

#endif // AFFICHAGE_H
