#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

// Fonction utilitaire pour obtenir la couleur selon la valeur
const char* couleur_carte(int valeur) {
    if (valeur == -2 || valeur == -1) return VIOLET;
    if (valeur == 0) return BLEU_CLAIR;
    if (valeur >= 1 && valeur <= 4) return VERT;
    if (valeur >= 5 && valeur <= 8) return JAUNE;
    return ROUGE;
}

// Début de la partie
void debut_partie(Partie *partie) {
    printf("\n====================================CARD YARD===================================\n\nBienvenue au jeu Card Yard!\nLes règles sont simples, chaque joueur possède 12 cartes et doit s'en débarrasser le plus vite possible!\n");

    do {
        printf("Nombre de joueurs (2-%d) : ", MAX_JOUEURS);
        scanf("%d", &partie->nb_joueurs);
        if (partie->nb_joueurs < 2 || partie->nb_joueurs > MAX_JOUEURS) {
            printf("Erreur ! Vous devez choisir un nombre de joueurs entre 2 et 8.\n");
        }
    } while (partie->nb_joueurs < 2 || partie->nb_joueurs > MAX_JOUEURS);

    for (int i = 0; i < partie->nb_joueurs; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%19s", partie->joueurs[i].nom);
    }

    partie->taille_pioche = 0;
    for (int i = -2; i <= 12; i++) {
        int quantite = (i == -2) ? 5 : (i == -1) ? 10 : (i == 0) ? 15 : 10;
        for (int j = 0; j < quantite; j++) {
            partie->pioche[partie->taille_pioche++] = (Carte){i, false};
        }
    }

    melanger_pioche(partie->pioche, partie->taille_pioche);
    partie->index_pioche = 0;
    partie->defausse_active = false;
    partie->joueur_actuel = 0;
}

// Mélanger la pioche
void melanger_pioche(Carte *pioche, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte tmp = pioche[i];
        pioche[i] = pioche[j];
        pioche[j] = tmp;
    }
}

// Distribuer les cartes aux joueurs
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

// Révéler deux cartes aléatoires
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

// Gestion du tour d'un joueur
void tour_joueur(Partie *partie) {
    Joueur *joueur = &partie->joueurs[partie->joueur_actuel];
    printf("\n🔁 Tour de %s\n", joueur->nom);

    int choix;
    Carte carte_choisie;

    if (partie->defausse_active) {
        printf("1. Prendre carte de la pioche\n2. Prendre la carte de la défausse (%d)\nChoix : ", partie->defausse.valeur);
        scanf("%d", &choix);
        if (choix == 2) {
            carte_choisie = partie->defausse;
            partie->defausse_active = false;
        } else {
            carte_choisie = partie->pioche[partie->index_pioche++];
        }
    } else {
        printf("Pioche automatique (défausse vide).\n");
        carte_choisie = partie->pioche[partie->index_pioche++];
    }

    printf("Carte choisie : %d\n", carte_choisie.valeur);

    int l, c;
    do {
        printf("Échange avec quelle carte ? (Ligne 0-2 / Colonne 0-3) : ");
        scanf("%d %d", &l, &c);
        if ((l < 0 || l > 2) || (c < 0 || c > 3)) {
            printf("Erreur. Coordonnées incorrectes !\n");
        }
    } while ((l < 0 || l > 2) || (c < 0 || c > 3));

    Carte ancienne = joueur->grille[l][c];
    joueur->grille[l][c] = carte_choisie;
    joueur->grille[l][c].visible = true;

    partie->defausse = ancienne;
    partie->defausse.visible = true;
    partie->defausse_active = true;

    verifier_et_supprimer_colonnes(joueur);
}

// Vérifier et supprimer automatiquement les colonnes identiques
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
                joueur->grille[l][c].valeur = 0;
                joueur->grille[l][c].visible = true;
            }
        }
    }
}

// Vérifier si la partie est terminée
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

// Calculer le score total d'un joueur
int calculer_score(const Joueur *joueur) {
    int score = 0;
    for (int l = 0; l < LIGNES; l++) {
        for (int c = 0; c < COLONNES; c++) {
            score += joueur->grille[l][c].valeur;
        }
    }
    return score;
}
