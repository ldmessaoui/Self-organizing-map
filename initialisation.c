#include "assert.h"
#include "structures.h"
#include "fonctions.h"

//   
//
//    Initialisation
//
//



// Initialisation de la table des données

    bdd init_bdd(){
        bdd b;
        b.nbr_lignes=150;
        b.taille_vect=4;
        b.vecteur=(vecteur*) malloc(b.nbr_lignes*sizeof(struct bdd)); //Allocation de la memoire
        int i;
        for (i = 0; i<=b.nbr_lignes; i++){
            b.vecteur[i].vecteur=(double *) malloc( (b.taille_vect)*sizeof(double));
            b.vecteur[i].nom=(char *) malloc(30 *sizeof(char));
        }
        
    // Affecter chaque ligne présente dans le dataset a la structure de la base de données, chaque element represente une ligne du dataset

    FILE *dataset;
    dataset=fopen("iris.data", "r");
    char *sep=",";
    char *v;
    char *token;
    char line[300];
    int j=0;
    char *endPtr;
    int z;
    for (z=0; z < b.nbr_lignes; ++z)  {
        fgets(line, sizeof line, dataset); // Lecture ligne par ligne
        v = line;
        token=strtok(v,sep); // Decouper chaque ligne lue avec une virgule comme séparateur

        b.vecteur[z].vecteur[j]=strtod(token, &endPtr); //Transformer les chaines de caracteres en type double
         j++;
        while( token!= NULL){
            while(j<b.taille_vect){
                token=strtok(NULL,sep);
                b.vecteur[z].vecteur[j] = strtod(token,&endPtr);
                j++;    
            }
            //Attribuer une etiquette (nom de la fleur) pour chaque vecteur (donnee)
            token=strtok(NULL,sep);
            b.vecteur[z].nom=strcpy(b.vecteur[z].nom,token);
            token = NULL;
            j=0;
         
         }
    } 
    
    fclose (dataset); 

    //
    //Normalisation
    //

    //On calcule la norme pour chaque vecteur

        for( z=0; z<b.nbr_lignes; ++z ){
                b.vecteur[z].norme=normalise(b.vecteur[z].vecteur, b.taille_vect);
            }

        for( z=0; z<b.nbr_lignes; ++z ){
            for ( j=0; j<(b.taille_vect); ++j){
                b.vecteur[z].vecteur[j]/=b.vecteur[z].norme;
            }
        }


    // 
    //Calcul du vecteur moyen de la bd
    // 
    
    b.vect_moy = (double*) calloc ((b.taille_vect), sizeof(double));
    assert(b.vect_moy);
    for (j = 0; j< b.taille_vect; j++){
        for (i=0; i < b.nbr_lignes; i++){
            b.vect_moy[j]+= b.vecteur[i].vecteur[j];
        }
        
        b.vect_moy[j] = b.vect_moy[j] / b.nbr_lignes;
    }
   return b;
}





//
// Initialisation du reseau
//

reseau*initialisation_reseau(bdd b){
        reseau *r = malloc(sizeof(*r)); 
        r->nb_colonnes=6;
        r->nb_lignes=10;
        r->Reseau= (neurone **) malloc(r->nb_colonnes*r->nb_lignes*sizeof(*r->Reseau)); 
        int i,j,z; 
        for (i=0; i < r->nb_lignes; i++) {
            r->Reseau[i]=(neurone *)malloc(r->nb_colonnes*sizeof(*r->Reseau[i]));
            r->Reseau[i]->etiquette=(char *) malloc(30 *sizeof(char));
            
        }
        for (i= 0; i < r->nb_lignes; i++) {
            for (j = 0; j < r->nb_colonnes; j++) {
                r->Reseau[i][j].weight= (double *) malloc( (b.taille_vect) *sizeof(*r->Reseau[i][j].weight));
                
            }
        }
   
    //Initialisation du reseau de neurones en tirant des valeurs aletoirement dans un intervalle proche du vecteur moyen de la bd

   for (i = 0; i < r->nb_lignes; ++i){
        for (j= 0; j < r->nb_colonnes; ++j){
            for (z = 0; z < b.taille_vect; ++z){
                r->Reseau[i][j].weight[z]=tire_aleatoirement(-0.05 + b.vect_moy[z], 0.05 + b.vect_moy[z]);
            }
            r->Reseau[i][j].etiquette="#";
        }
    }

    return r;
}


