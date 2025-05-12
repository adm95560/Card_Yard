#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h> // Permet d'utiliser le type bool (true/false)

// Constantes globales du jeu
#define LIGNES 3            // Nombre de lignes de la grille d’un joueur
#define COLONNES 4          // Nombre de colonnes de la grille d’un joueur
#define MAX_JOUEURS 8       // Nombre maximal de joueurs autorisés
#define NB_MAX_CARTES 150   // Nombre maximal de cartes disponibles dans la pioche

// Structure représentant une carte
typedef struct {
    int valeur;     // Valeur de la carte 
    bool visible;   // true si la carte est retournée, false si elle est face cachée
} Carte;

// Structure représentant un joueur
typedef struct {
    char nom[20];                           // Nom du joueur (chaîne de caractères)
    Carte grille[LIGNES][COLONNES];        // Grille 3x4 contenant les cartes du joueur
} Joueur;

// Structure représentant l’état global de la partie
typedef struct {
    Joueur joueurs[MAX_JOUEURS];           // Tableau contenant tous les joueurs de la partie
    Carte pioche[NB_MAX_CARTES];           // Pioche principale avec toutes les cartes
    int index_pioche;                      // Index de la prochaine carte à piocher
    Carte defausse;                        // Carte actuellement visible dans la défausse
    bool defausse_active;                  // true si une carte est déjà présente dans la défausse
    int nb_joueurs;                        // Nombre total de joueurs participant à la partie
    int joueur_actuel;                     // Index du joueur qui joue actuellement (0 à nb_joueurs-1)
    int taille_pioche;                     // Nombre réel de cartes dans la pioche (dépend des variantes)
} Partie;

#endif // TYPES_H
