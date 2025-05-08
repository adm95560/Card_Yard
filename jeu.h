#ifndef JEU_H
#define JEU_H


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


#include "types.h"



const char* couleur_carte(int valeur);
void debut_partie(Partie *partie);
void melanger_pioche(Carte *pioche, int taille);
void distribuer_cartes(Partie *partie);
void reveler_deux_cartes(Joueur *joueur);
void tour_joueur(Partie *partie);
void verifier_et_supprimer_colonnes(Joueur *joueur);
bool partie_terminee(const Partie *partie);
int calculer_score(const Joueur *joueur);

#endif // JEU_H


