#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double normalise(double *vect, int size);
double tire_aleatoirement(double min, double max);
double distance_euclidienne (double *x, double *y, int taille);
bdd init_bdd();
reseau* initialisation_reseau(bdd b);
int* shuffle(int *tab_ind, int taille);
bmu trouver_le_bmu (reseau *r, bdd b, int pos );
void apprentissage( bdd b, reseau *r, int nb_iteration);
void voisinage(reseau *r,bmu bm, int rayon, double alpha, int pos, bdd b);
int calculer_rayon(int iteration, int phase1, int rayon);
void affecte_valeur(reseau *r,bmu bm, int pos, bdd b);
void affiche_res(reseau *r);
void stat (reseau *r, bmu bm, int pos, bdd b);
void affecte_valeur_fin(reseau *r,bmu bm, int pos, bdd b);
void afficherListe(liste_bmus *liste);
void suppression(liste_bmus *liste);
void insertion(liste_bmus *liste, int ligne, int colonne);
liste_bmus *initialisation();
