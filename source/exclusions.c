#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/helper.h"
#include "../headers/exclusions.h"
#include "../headers/precedences.h"


/*
 * Retourne les aretes d'exclusion lues dans le fichier texte
 * @param file_path : Chemin vers le fichier
 * @return aretes   : Tableau d'aretes
 */
Arete * get_arete(char * file_path, int * taille)
{
    printf("\nLecture du fichier %s...\n", file_path);
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            (*taille)++;
        }
    }
    printf("Il y a %d aretes :\n", *taille);

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Arete * aretes = malloc(*taille * sizeof(Arete));

    // remplissage du tableau d'operations
    for (int i = 0; i < *taille; i++) {
        fscanf(fichier, "%d %d", &aretes[i].op_depart, &aretes[i].op_arrivee);
    }

    afficher_aretes(aretes, *taille);

    fclose(fichier);
    return aretes;
}


/*
 * Tri les opérations par ordre décroissant de degré
 * @param operations : Tableau d'opérations
 * @param ordre      : Ordre du graphe
 */
Operation * triDecroissantDegre(Operation* operations, int* ordre)
{
    int i, j;
    Operation temp;

    for (i = 0; i < *ordre - 1; i++)
    {
        for (j = 0; j < *ordre - i - 1; j++)
        {
            if (operations[j].deg < operations[j + 1].deg)
            {
                temp = operations[j];
                operations[j] = operations[j + 1];
                operations[j + 1] = temp;
            }
        }
    }

    printf("Liste triee : \n");

    for(int k = 0; k < *ordre; k++){
        printf("Le degre du sommet  %d est %d \n", operations[k].id_operation, operations[k].deg );
    }
    return operations;
}


/*
 * Retourne les opérations lues dans le fichier texte
 * @param file_path : Chemin vers le fichier
 * @return operations   : Tableau d'opérations
 */
Operation * init_graphe(int* ordre)
{
    Operation * operations;
     // On initialise la taille à 1, et non 0 car on va compter le nbr de \n et la dernière n'en contient pas (End Of File)
    printf("lecture du fichier operations.txt...\n");
    FILE * fichier = file_loader("./data/operations.txt", "r");
    char c;
    while ((c = fgetc(fichier)) != EOF)
    {
        if (c == '\n')
        {
            (*ordre)++;
        }
    }

    printf("l'ordre du graphe est :  %d \n", *ordre);

    operations = malloc(*ordre * sizeof(Operation));
    // retour au debut du fichier
    rewind(fichier);

    for(int i = 0 ; i< *ordre; i++)
    {
        float temp; // on a pas besoin du temps de l'opération car on travaille seulement sur l'exclusion
        fscanf(fichier, "%d %f", &operations[i].id_operation, &temp);
        printf("%d \n",operations[i].id_operation);
    }
    fclose(fichier);

    printf("Lecture du fichier exclusions.txt...\n");
    FILE * fichier2 = file_loader("./data/exclusions.txt", "r");

    int taille = 1;
    while ((c = fgetc(fichier2)) != EOF)
    {
        if (c == '\n') {
            taille++;
        }
    }
    printf("La taille du graphe est :  %d \n",taille);

    rewind(fichier2);

    for(int l = 0; l < *ordre; l++)
    {
        operations[l].deg = 0;
    }

    /* pour toutes les exclusions on va verifier si elles se trouvent dans notre graphe,
      on utilise deux variable (temp2 et temp3) pour stocker les valeurs qu'on lis depuis le fichier
      ( on utilise deux valeurs car les exclusions sont écrites avec deux nombre sur la meme ligne)
      et ensuite si la valeur de temp est egal a un des noms dans notre tableau(on le fait avec une boucle for)
      alors on ajoute au degrée de ce sommet 1 (il faut bien retenir que temp est égal a l'id et non l'index du sommet dans le tableau)
    */

    for(int i = 0; i < taille; i++)
    {
        int temp2, temp3;
        fscanf(fichier2, "%d %d", &temp2, &temp3);

        for(int j = 0; j < *ordre; j++)
        {
            if(temp2 == operations[j].id_operation)
            {
                operations[j].deg++;
            }
            if(temp3 == operations[j].id_operation)
            {
                operations[j].deg++;
            }
        }

    }

    fclose(fichier2);

    return operations;
}