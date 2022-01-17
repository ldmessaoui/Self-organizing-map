#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Structure d'un neurone
typedef struct neurone {
    double *weight;
    double *val[3];
    char *etiquette;
    
}neurone;

//Structure d'un vecteur (une donnée)
typedef struct vecteur {
     double *vecteur;
     char *nom;
     double norme;
}vecteur; 

//Structure de la base de données
typedef struct bdd {
     struct vecteur* vecteur;
     int taille_vect;
     int nbr_lignes;
     double *vect_moy;
}bdd;

//Structure de la grille du réseau
typedef struct reseau {
    struct neurone** Reseau; 
    int nb_lignes;
    int nb_colonnes;
}reseau;

//Structure d'une best matching unit
typedef struct bmu{
    int ligne;
    int colonne;
    struct bmu *suivant;
}bmu;

//Structure de la liste chainée des BMUs
typedef struct liste_bmus{
    int nbr;
    bmu *premier;
    //bmu *dernier;?
}liste_bmus;



