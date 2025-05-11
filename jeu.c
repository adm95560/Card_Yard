#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Constantes de configuration du jeu
#define LIGNES 3
#define COLONNES 4
#define MAX_JOUEURS 8
#define NB_MAX_CARTES 150

// Codes couleur ANSI pour affichage terminal coloré
#define RESET       "\033[0m"
#define VIOLET      "\033[35m"
#define BLEU_CLAIR  "\033[36m"
#define VERT        "\033[32m"
#define JAUNE       "\033[33m"
#define ROUGE       "\033[31m"

// Couleurs supplémentaires pour affichage esthétique
#define COLOR_RESET   "\033[0m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_WHITE   "\033[1;37m"

// Inclusion des en-têtes contenant les structures et prototypes
#include "jeu.h"
#include "affichage.h"

// Fonction qui retourne une couleur selon la valeur de la carte
const char* couleur_carte(int valeur) {
    if (valeur == -2 || valeur == -1) return VIOLET;
    if (valeur == 0) return BLEU_CLAIR;
    if (valeur >= 1 && valeur <= 4) return VERT;
    if (valeur >= 5 && valeur <= 8) return JAUNE;
    return ROUGE;
}

// Initialisation d’une nouvelle partie
void debut_partie(Partie *partie) {
    // Affichage de l’écran de bienvenue
    printf("\033[1;32m");
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               🌟 CARD YARD 🌟                                ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                Bienvenue dans le monde stratégique du Card Yard !            ║\n");
    printf("║       Chaque joueur possède 12 cartes et doit les échanger ou les révéler    ║\n");
    printf("║      de manière stratégique pour accumuler le moins de points possible !     ║\n");
    printf("║        Serez-vous le maître du Yard ou resterez-vous à la traîne ? 👀        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m");

    // Saisie sécurisée du nombre de joueurs
    int valid_input;
    do {
        printf(COLOR_YELLOW "👥 Nombre de joueurs " COLOR_RESET "(" COLOR_CYAN "2-%d" COLOR_RESET ") : 🃏 ", MAX_JOUEURS);
        valid_input = scanf("%d", &partie->nb_joueurs);
        if (valid_input != 1 || partie->nb_joueurs < 2 || partie->nb_joueurs > MAX_JOUEURS) {
            printf("Erreur ! Vous devez entrer un nombre entre 2 et %d.\n", MAX_JOUEURS);
            while (getchar() != '\n'); // Vide le buffer en cas d’erreur
        }
    } while (valid_input != 1 || partie->nb_joueurs < 2 || partie->nb_joueurs > MAX_JOUEURS);

    // Saisie des noms des joueurs
    for (int i = 0; i < partie->nb_joueurs; i++) {
        printf(COLOR_BLUE "🧑‍💻 Nom du joueur " COLOR_MAGENTA "%d" COLOR_RESET " : ", i + 1);
        scanf("%19s", partie->joueurs[i].nom); // Max 19 caractères
    }

    // Remplissage de la pioche selon les quantités de chaque valeur
    partie->taille_pioche = 0;
    for (int i = -2; i <= 12; i++) {
        int quantite = (i == -2) ? 5 : (i == -1) ? 10 : (i == 0) ? 15 : 10;
        for (int j = 0; j < quantite; j++) {
            partie->pioche[partie->taille_pioche++] = (Carte){i, false};
        }
    }

    // Mélange de la pioche
    melanger_pioche(partie->pioche, partie->taille_pioche);

    // Initialisation des variables de partie
    partie->index_pioche = 0;
    partie->defausse_active = false;
    partie->joueur_actuel = 0;
}

// Mélange aléatoire des cartes de la pioche (algorithme de Fisher-Yates)
void melanger_pioche(Carte *pioche, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte tmp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = tmp;
    }
}

// Distribution des cartes à chaque joueur (12 cartes : 3 lignes x 4 colonnes)
void distribuer_cartes(Partie *partie) {
    for (int i = 0; i < partie->nb_joueurs; i++) {
        for (int l = 0; l < LIGNES; l++) {
            for (int c = 0; c < COLONNES; c++) {
                partie->joueurs[i].grille[l][c] = partie->pioche[partie->index_pioche++];
                partie->joueurs[i].grille[l][c].visible = false;
            }
        }
        reveler_deux_cartes(&partie->joueurs[i]); // Révèle 2 cartes au hasard
    }
}

// Révélation de 2 cartes aléatoires pour un joueur donné
void reveler_deux_cartes(Joueur *joueur) {
    int revelees = 0;
    while (revelees < 2) {
        int l = rand() % LIGNES;
        int c = rand() % COLONNES;
        if (!joueur->grille[l][c].visible) {
            joueur->grille[l][c].visible = true;
            revelees++;
        }
    }
}

// Tour de jeu d’un joueur
void tour_joueur(Partie *partie) {
    Joueur *joueur = &partie->joueurs[partie->joueur_actuel];
    printf("\n🔁 Tour de %s\n", joueur->nom);

    int choix;
    Carte carte_choisie;
    char buffer[100];

    // Choix entre pioche et défausse
    if (partie->defausse_active) {
        printf("1. Prendre carte de la pioche\n2. Prendre la carte de la défausse (%d)\nChoix : ", partie->defausse.valeur);
        while (1) {
            if (!fgets(buffer, sizeof(buffer), stdin)) continue;
            if (sscanf(buffer, "%d", &choix) != 1 || (choix != 1 && choix != 2)) {
                printf("❌ Entrée invalide. Veuillez taper 1 ou 2 : ");
            } else {
                break;
            }
        }

        // Appliquer le choix
        carte_choisie = (choix == 2) ? partie->defausse : partie->pioche[partie->index_pioche++];
        if (choix == 2) partie->defausse_active = false;
    } else {
        // Défausse vide → pioche automatique
        printf("Pioche automatique (défausse vide).\n");
        carte_choisie = partie->pioche[partie->index_pioche++];
    }

    printf("Carte choisie : %d\n", carte_choisie.valeur);

    // Choix de la carte à remplacer
    int l, c;
    do {
        printf(COLOR_GREEN "🔁 Échange avec quelle carte ? " COLOR_RESET
        "(" COLOR_CYAN "Ligne 0-2" COLOR_RESET " / " COLOR_YELLOW "Colonne 0-3" COLOR_RESET ") : ");

        if (!fgets(buffer, sizeof(buffer), stdin)) continue;

        if (sscanf(buffer, "%d %d", &l, &c) != 2 || l < 0 || l > 2 || c < 0 || c > 3) {
            printf(COLOR_RED "❌ Erreur : Vous devez entrer deux entiers valides.\n"
            "📌 Exemple valide : 1 2 (ligne 0-2 et colonne 0-3)\n" COLOR_RESET);
        } else {
            break;
        }
    } while (1);

    // Échange de la carte
    Carte ancienne = joueur->grille[l][c];
    joueur->grille[l][c] = carte_choisie;
    joueur->grille[l][c].visible = true;

    // Mise à jour de la défausse
    partie->defausse = ancienne;
    partie->defausse.visible = true;
    partie->defausse_active = true;

    // Vérifie s’il faut supprimer une colonne (si toutes les cartes révélées et identiques)
    verifier_et_supprimer_colonnes(joueur);
}

// Vérifie et supprime les colonnes dont les 3 cartes sont visibles et identiques
void verifier_et_supprimer_colonnes(Joueur *joueur) {
    for (int c = 0; c < COLONNES; c++) {
        int v0 = joueur->grille[0][c].valeur;
        int v1 = joueur->grille[1][c].valeur;
        int v2 = joueur->grille[2][c].valeur;

        bool visibles = joueur->grille[0][c].visible && joueur->grille[1][c].visible && joueur->grille[2][c].visible;
        bool memes_valeurs = (v0 == v1) && (v1 == v2);

        if (visibles && memes_valeurs) {
            printf("\n💥 Colonne %d supprimée pour %s (valeur %d)\n", c, joueur->nom, v0);
            for (int l = 0; l < LIGNES; l++) {
                joueur->grille[l][c].valeur = 0;       // Réduction du score
                joueur->grille[l][c].visible = true;   // Marque la colonne comme révélée
            }
        }
    }
}

// Vérifie si la partie est terminée (si un joueur a toutes ses cartes révélées)
bool partie_terminee(const Partie *partie) {
    for (int i = 0; i < partie->nb_joueurs; i++) {
        bool tout_visible = true;
        for (int l = 0; l < LIGNES; l++) {
            for (int c = 0; c < COLONNES; c++) {
                if (!partie->joueurs[i].grille[l][c].visible) {
                    tout_visible = false;
                }
            }
        }
        if (tout_visible) return true;
    }
    return false;
}

// Calcule le score total d’un joueur (somme des valeurs de toutes les cartes)
int calculer_score(const Joueur *joueur) {
    int score = 0;
    for (int l = 0; l < LIGNES; l++) {
        for (int c = 0; c < COLONNES; c++) {
            score += joueur->grille[l][c].valeur;
        }
    }
    return score;
}

