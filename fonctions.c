#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "structures.h"
#include "fonctions.h"
#include <string.h>

#define L 10
#define C 6



// Fonction utilisée pour calculer la norme du vecteur
double normalise(double *vect, int size){
    double norme=0;
    int i;
    for (i=0; i < size-1; ++i){
        norme += pow(vect[i],2);
    }
    norme=sqrt(norme);
    return norme;
}


double tire_aleatoirement(double min, double max){
    return (rand()/ (double) RAND_MAX) * (max-min)+min;
}

    

double distance_euclidienne (double *x, double *y, int taille){
    int i;
    double dist=0.0,z=0.0;
    for ( i = 0; i < taille; ++i){
        z=x[i] -y[i];
        dist = dist + pow(z,2);
    }
    dist= sqrt(dist);
    return dist;
}



//La fonction shuffle prend un tableau d'indices et le melange aletoirement 

int* shuffle(int *tab_ind, int taille){
    int t=0;
    int i;
    for (i=0; i<taille;i++){
            int j=rand()%(taille);
            t=tab_ind[i];
            tab_ind[i]=tab_ind[j];
            tab_ind[j]=t;
        } 
    return tab_ind;
} 

// La fonction voisinag permet de calculer les coordonnées minimales et maximales de la matrice de voisinage
void voisinage(reseau *r,bmu bm, int rayon, double alpha, int pos, bdd b){
    
    int x_min=bm.ligne-rayon;
    if (x_min<0){
        x_min=0;
    }
    int y_min=bm.colonne-rayon;
    if (y_min<0){
        y_min=0;
    }
    int x_max=bm.ligne+rayon;
    if (x_max>=r->nb_lignes){
        x_max=r->nb_lignes-1;
    }

    int y_max=bm.colonne+rayon;
    if(y_max>=r->nb_colonnes){
        y_max=r->nb_colonnes-1;
    }
    int i,j,z;
    for(i=x_min;i<=x_max;i++){
        for(j=y_min;j<=y_max;j++){
            for(z=0;z<b.taille_vect;z++){
                r->Reseau[i][j].weight[z]=r->Reseau[i][j].weight[z]+alpha*(b.vecteur[pos].vecteur[z]-r->Reseau[i][j].weight[z]);
            }
        }
    }
}


int calculer_rayon(int iteration, int phase1, int rayon){
    int r;
    int chgmt =phase1/rayon;
    
    if (iteration<=chgmt){
        r=3;
    }
    else{
        if(iteration>phase1-chgmt){
            r=1;
        }
        else{
            r=2;
        }
    }
    return r;
}


void affecte_valeur(reseau *r,bmu bm, int pos, bdd b){
    if (strcmp(b.vecteur[pos].nom,"Iris-setosa\n")==0){
        r->Reseau[bm.ligne][bm.colonne].etiquette="S";
    }
    else{
        if(strcmp(b.vecteur[pos].nom,"Iris-versicolor\n")==0){
            r->Reseau[bm.ligne][bm.colonne].etiquette="V";
        }
        else{
            r->Reseau[bm.ligne][bm.colonne].etiquette="G";
        }
    }
}

void affecte_valeur_fin(reseau *r,bmu bm, int pos, bdd bd){
    if (r->Reseau[bm.ligne][bm.colonne].val[0]>r->Reseau[bm.ligne][bm.colonne].val[1] && r->Reseau[bm.ligne][bm.colonne].val[0]>r->Reseau[bm.ligne][bm.colonne].val[2]){
        r->Reseau[bm.ligne][bm.colonne].etiquette="S";
    }
    else {
        if (r->Reseau[bm.ligne][bm.colonne].val[1]>r->Reseau[bm.ligne][bm.colonne].val[0] && r->Reseau[bm.ligne][bm.colonne].val[1]>r->Reseau[bm.ligne][bm.colonne].val[2]){
            r->Reseau[bm.ligne][bm.colonne].etiquette="V";
        }
        else{
            if (r->Reseau[bm.ligne][bm.colonne].val[2]>r->Reseau[bm.ligne][bm.colonne].val[0] && r->Reseau[bm.ligne][bm.colonne].val[2]>r->Reseau[bm.ligne][bm.colonne].val[1]){
                r->Reseau[bm.ligne][bm.colonne].etiquette="G";
            }
            else {
                r->Reseau[bm.ligne][bm.colonne].etiquette="*";
            }
            
        }
            
    }
}


void affiche_res(reseau *r){
    int ligne;
    int colonne; 
    for (ligne=0; ligne<L;ligne++){
        for(colonne=0;colonne<C;colonne++){
            printf("%s ",r->Reseau[ligne][colonne].etiquette);
        }
        printf("\n");
    }   
}

void stat (reseau *r, bmu bm, int pos, bdd bd){
    if (strcmp(bd.vecteur[pos].nom,"Iris-setosa\n")==0){
        r->Reseau[bm.ligne][bm.colonne].val[0]+=1;
    }
    else{
        if(strcmp(bd.vecteur[pos].nom,"Iris-versicolor\n")==0){
            r->Reseau[bm.ligne][bm.colonne].val[1]+=1;
        }
        else{
            r->Reseau[bm.ligne][bm.colonne].val[2]+=1;
        }
    }
}



liste_bmus *initialisation(){
    liste_bmus *liste=malloc(sizeof(*liste));
    bmu *bmu =malloc(sizeof(*bmu));
     if (liste == NULL || bmu == NULL)
    {
        exit(EXIT_FAILURE);
    }

    bmu->ligne = 0;
    bmu->colonne=0;
    bmu->suivant = NULL;
    liste->premier = bmu;
    liste->nbr+=1;

    return liste;
}

void insertion(liste_bmus *liste, int ligne, int colonne)
{
    bmu *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->ligne = ligne;
    nouveau->colonne=colonne;

    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
    liste->nbr+=1;
}


void suppression(liste_bmus *liste)
{   
    while(liste->premier->suivant){
        bmu *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
    liste->premier=NULL;
    liste->nbr=0;
}


void afficherListe(liste_bmus *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    bmu *actuel = liste->premier;

    while (actuel != NULL)
    {
        printf("ligne -> %d\n, colonne ->%d\n ", actuel->ligne, actuel->colonne);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

bmu trouver_le_bmu (reseau *r, bdd b, int pos ){
    liste_bmus *liste=initialisation();
    double tmp=0.0;
    double distance_min=1.0;
    int i;
    int j;
    for(i=0; i<r->nb_lignes;i++){
        for (j=0;j<r->nb_colonnes;j++){
            tmp=distance_euclidienne(b.vecteur[pos].vecteur,r->Reseau[i][j].weight,b.taille_vect);
            //printf("i:%d,j:%d\n",i,j);
            if (tmp<distance_min){
                //printf("tmp<dist %f<%f\n", tmp, distance_min);
                suppression(liste);
                //afficherListe(liste);
                insertion(liste,i,j);
                //afficherListe(liste);
                distance_min=tmp;
            }
            else {
                if (tmp==distance_min){
                    insertion(liste,i,j);
                    //printf("tmp=dist %f<%f\n", tmp, distance_min);
                    //afficherListe(liste);
                }
            }
        }

    }

    bmu *bm = liste->premier;
    if (liste->nbr>1){
        //afficherListe(liste);
        int alea=rand()%liste->nbr;
        //printf("alea:%d\n",alea);
        int z;
        for (z=1; z<alea;z++){
            bm=bm->suivant;
        }
        //printf("i:%d,j:%d\n ", bm->ligne,bm->colonne);
    }
    return *bm;
}
    
    
