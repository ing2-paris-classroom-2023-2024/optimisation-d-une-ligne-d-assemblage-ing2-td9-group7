#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/helper.h"
#include "../headers/exclusions.h"
typedef struct sommet  {
    int nom;
    int deg;
    int couleur;
}t_sommet;

typedef struct graphe{
    int ordre;
    int taille;
    t_sommet* tab_sommet;
}t_graphe;

t_graphe triDecroissant(t_graphe graphe, int taille) {
    int i, j;
    t_sommet temp;
    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            if (graphe.tab_sommet[j].deg < graphe.tab_sommet[j + 1].deg) {
                temp = graphe.tab_sommet[j];
                graphe.tab_sommet[j] = graphe.tab_sommet[j + 1];
                graphe.tab_sommet[j + 1] = temp;
            }
        }
    }
    return graphe;
}

t_graphe* init_graphe(){
    t_graphe graphe;
    graphe.ordre = 1; // On initialise la taille à 1, et non 0 car on va compter le nbr de \n et la dernière n'en contient pas (End Of File)
    FILE * fichier = file_loader("./data/operations.txt", "r");
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            graphe.ordre++;
        }
    }
    printf("l'ordre du graphe est :  %d \n", graphe.ordre);

    graphe.tab_sommet = malloc(graphe.ordre * sizeof(t_sommet));
    // retour au debut du fichier
    rewind(fichier);

    for(int i = 0 ; i<graphe.ordre; i++){
        float temp; // Pour se débarasser de la valeur "parasite"
        fscanf(fichier, "%d %f", &graphe.tab_sommet[i].nom, &temp);
        printf("%d \n",graphe.tab_sommet[i].nom);
    }
    fclose(fichier);

    FILE * fichier2 = file_loader("./data/exclusions.txt", "r");

    graphe.taille = 1;
    while ((c = fgetc(fichier2)) != EOF) {
        if (c == '\n') {
            graphe.taille++;
        }
    }
    printf("La taille du graphe est :  %d \n", graphe.taille);

    rewind(fichier2);

    for(int l = 0; l < graphe.ordre; l++){
        graphe.tab_sommet[l].deg = 0;
    }

    // pour toutes les exclusions on va verifier si elles se trouvent dans notre graphe,
    // on utilise deux variable (temp2 et temp3) pour stocker les valeurs qu'on lis depuis le fichier
    // ( on utilise deux valeurs car les exclusions sont écrites avec deux nombre sur la meme ligne)
    // et ensuite si la valeur de temp est egal a un des noms dans notre tableau(on le fait avec une boucle for)
    // alors on ajoute au degrée de ce sommet 1 (il faut bien retenir que temp est égal au nom et non l'index du sommet dans le tableau)

    for(int i = 0; i < graphe.taille; i++){
        int temp2, temp3;
        fscanf(fichier2, "%d %d", &temp2, &temp3);
        for(int j = 0; j < graphe.ordre; j++){
            if(temp2 == graphe.tab_sommet[j].nom){
                graphe.tab_sommet[j].deg++;
            }
            if(temp3 == graphe.tab_sommet[j].nom){
                graphe.tab_sommet[j].deg++;
            }
        }

    }

    for(int k = 0; k < graphe.ordre; k++){
        printf("Le degre du sommet  %d est %d \n", graphe.tab_sommet[k].nom, graphe.tab_sommet[k].deg );
    }

    printf("\n");

    fclose(fichier2);

    triDecroissant(graphe,graphe.ordre);
    printf("Liste triée : \n");

    for(int k = 0; k < graphe.ordre; k++){
        printf("Le degre du sommet  %d est %d \n", graphe.tab_sommet[k].nom, graphe.tab_sommet[k].deg );
    }
    
}



