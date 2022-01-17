
#include "structures.h"
#include "fonctions.h"


void apprentissage( bdd b, reseau *r, int nb_iteration){
    int *tab_ind;
    tab_ind=(int *) malloc(b.nbr_lignes*sizeof(int));
    int rayon;
    bmu bm;
    int phase1= nb_iteration/4;
    int phase2= nb_iteration-phase1;
    int i;
    for (i=0; i < b.nbr_lignes; i++)
    {
        tab_ind[i]=i;  
    }
    double alpha_init=0.9; // Initialiser le taux d'apprentissage a 0.9
    double alpha=alpha_init;
    printf("------------------------Phase1------------------------\n");
    int j;
    int ind;
    for (j=0; j<phase1;j++){
        tab_ind=shuffle(tab_ind, b.nbr_lignes);
        for (ind=0;ind<b.nbr_lignes;ind++){
            bm=trouver_le_bmu(r,b,tab_ind[ind]);
            rayon=calculer_rayon(j,phase1,3);
            voisinage(r,bm,rayon,alpha,tab_ind[ind],b);

            affecte_valeur(r,bm,tab_ind[ind],b);
        }
        alpha=alpha_init*(1-((double)j/(double)phase1)); //Formule qui permet de faire evoluer le taux d'apprentissage.
        
        if (j%100==0){
            affiche_res(r);
            printf("------------------------\n\n");
        }
       
    } 

    printf("------------------------Phase2------------------------\n");
    alpha_init=0.07;
    alpha=alpha_init;
    for (j=0; j<phase2;j++){
        tab_ind=shuffle(tab_ind, b.nbr_lignes);
        for (ind=0;ind<b.nbr_lignes;ind++){
            bm = trouver_le_bmu(r,b,tab_ind[ind]);
            voisinage(r,bm,1,alpha,tab_ind[ind],b);
            affecte_valeur(r,bm,tab_ind[ind],b);
        }
        alpha=alpha_init*(1-((double)j/(double)phase2));
        
        if (j%400==0){
            affiche_res(r);
            printf("------------------------\n");

        }
       
    }

   
    
    
}

