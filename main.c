#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"


int main(){
   
    bdd b;
    b=init_bdd();
    reseau *r;
    r=initialisation_reseau(b);
    
    printf("------------------Inititialisation-------------------\n");
    affiche_res(r);
    printf("------------------Apprentissage------------------\n");
    int iteration_totale =500*b.taille_vect; 
    apprentissage(b,r,iteration_totale);
    
    /*printf("------------------------Fin------------------------\n");
    affiche_res(r);*/

    
    return 0;
}


