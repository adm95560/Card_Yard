#ifndef JEU_H
#define JEU_H

#include <stdio.h>      // Pour les entrées/sorties standard (ex : printf)
#include <stdlib.h>     // Pour fonctions utilitaires (ex : malloc, rand, etc.)
#include <stdbool.h>    // Pour le type booléen (true/false)
#include <time.h>       // Pour initialiser le générateur aléatoire (srand, time)

#define LIGNES 3                // Nombre de lignes dans la grille d’un joueur
#define COLONNES 4              // Nombre de colonnes dans la grille d’un joueur
#define MAX_JOUEURS 8           // Nombre maximum de joueurs
#define NB_MAX_CARTES 150       // Nombre maximal de cartes dans la pioche

// Codes couleur ANSI pour un affichage coloré dans le terminal
#define RESET       "\033[0m"
#define VIOLET      "\033[35m"
#define BLEU_CLAIR  "\033[36m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define ROUGE       "\033[31m"

#include "types.h" // Inclusion des structures (Carte, Joueur, Partie)

// Retourne une chaîne ANSI représentant la couleur associée à une valeur de carte.
 
const char* couleur_carte(int valeur);

//Initialise une nouvelle partie : demande les noms, initialise la pioche, la défausse, etc.
void debut_partie(Partie *partie);

//Mélange aléatoirement la pioche de cartes.
 
void melanger_pioche(Carte *pioche, int taille);

// Distribue les cartes aux joueurs et en pose une dans la défausse.

void distribuer_cartes(Partie *partie);

// Permet à un joueur de retourner deux de ses cartes en début de partie.

void reveler_deux_cartes(Joueur *joueur);

// Gère le tour d’un joueur : pioche, choix d’action, échanges, etc.
 
void tour_joueur(Partie *partie);

//Vérifie si une colonne complète de cartes visibles contient la même valeur, et la retire si c’est le cas.

void verifier_et_supprimer_colonnes(Joueur *joueur);

//Vérifie si la partie est terminée (toutes les cartes d’un joueur sont visibles).

bool partie_terminee(const Partie *partie);

//Calcule le score d’un joueur en additionnant les valeurs de ses cartes visibles.
 
int calculer_score(const Joueur *joueur);

#endif // JEU_H
