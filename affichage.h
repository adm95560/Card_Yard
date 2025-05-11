#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>      // Pour les fonctions d'affichage comme printf
#include <stdlib.h>     // Pour les fonctions utilitaires générales (non utilisé ici mais parfois utile)
#include <stdbool.h>    // Pour utiliser le type bool
#include <time.h>       // Pour les fonctions liées au temps (non utilisé ici mais utile ailleurs dans le projet)

// Constantes liées à la taille du jeu
#define LIGNES 3                // Nombre de lignes dans la grille d’un joueur
#define COLONNES 4              // Nombre de colonnes dans la grille d’un joueur
#define MAX_JOUEURS 8           // Nombre maximal de joueurs autorisés
#define NB_MAX_CARTES 150       // Nombre maximal de cartes dans la pioche

// Codes couleur ANSI pour l'affichage stylisé dans le terminal
#define RESET "\033[0m"         // Réinitialise la couleur
#define VIOLET "\033[35m"       // Texte violet
#define BLEU_CLAIR "\033[36m"   // Texte bleu clair
#define VERT "\033[32m"         // Texte vert
#define JAUNE "\033[33m"        // Texte jaune
#define ROUGE "\033[31m"        // Texte rouge

#include "types.h" // Inclusion des structures de données (Carte, Joueur, Partie)

// Déclarations des fonctions d'affichage

// Affiche une ligne (1D) de cartes d’un joueur avec leurs états (visible/cachée)

void afficher_ligne_grille(const Carte ligne[]);

//Affiche la grille entière d’un joueur (3 lignes de 4 cartes)

void afficher_grille_joueur(const Joueur *joueur);

//Affiche l’ensemble de la table, c’est-à-dire toutes les grilles des joueurs ainsi que l’état de la pioche et de la défausse.

void afficher_table(const Partie *partie);

//Affiche le ou les gagnants de la partie en fonction des scores

void afficher_gagnant(const Partie *partie);

#endif // AFFICHAGE_H
