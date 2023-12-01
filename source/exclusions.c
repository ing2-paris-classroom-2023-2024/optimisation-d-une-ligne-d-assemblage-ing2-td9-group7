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
Arete * get_exclusions(char * file_path, int * taille)
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
 * Tri les operations par ordre decroissant de degre
 * @param operations : Tableau d'operations
 * @param ordre      : Nombre d'operations
 * @param taille     : Nombre d'aretes
 * @return           : Tableau d'operations triees par degre decroissant
 */
Operation * tri_operations_degre_decroissant(Operation * operations, int ordre, int taille)
{
    Operation * operations_triees = malloc(ordre * sizeof(Operation));
    memcpy(operations_triees, operations, ordre * sizeof(Operation));

    for (int i = 0; i < ordre - 1; i++) {
        for (int j = 0; j < ordre - i - 1; j++) {
            if (operations_triees[j].deg < operations_triees[j + 1].deg) {
                Operation temp = operations_triees[j];
                operations_triees[j] = operations_triees[j + 1];
                operations_triees[j + 1] = temp;
            }
        }
    }

    printf("\nListe triee : \n");

    for (int k = 0; k < ordre; k++) {
        printf("S%d\t- D %d \n", operations_triees[k].id_operation, operations_triees[k].deg);
    }

    return operations_triees;
}


/*
 * Determine si deux opérations doivent etre separees
 * @param operations_1 : premiere operation de l'arete
 * @param operations_2 : deuxieme operation de l'arete
 * @param aretes       : Tableau d'aretes
 * @param taille       : Nombre d'aretes
 * @return             : 1 si les deux operations doivent etre separees, 0 sinon
*/
int voisins(Operation * operation_1, Operation * operation_2, Arete * aretes, int taille)
{
    // renvoie 1 si le sommet est voisin d'un autre sommet, 0 sinon
    for (int i = 0; i < taille; i++) {
        if ((aretes[i].op_depart == operation_1->id_operation && aretes[i].op_arrivee == operation_2->id_operation) || (aretes[i].op_depart == operation_2->id_operation && aretes[i].op_arrivee == operation_1->id_operation)) {
            return 1;
        }
    }

    return 0;
}


/*
 * Attribution des couleurs aux opérations selon l'algorithme de Welsh-Powell
 * @param operations : Tableau d'opérations
 * @param aretes     : Tableau d'aretes
 * @param ordre      : Nombre d'opérations
*/
void welsh_powell_coloration(Operation * operations, Arete * aretes, int ordre, int taille)
{
    /* 1. Trier les sommets par ordre décroissant de degré (deja fait)
       2. tant que tous les sommets ne sont pas coloriés
       3. Considerer une couleur C, differente de toutes les couleurs deja utilisees
       4. Considerer le premier sommet dans l'ordre decroissant des degres et lui attribuer la couleur C
       5. Considerer chacun des autres sommets non colories dans l'ordre decroissant des degres
       6. S'il est adjacent a un sommet deja colorie avec la couleur C, ne lui affecter aucune couleur
       7. Sinon, lui affecter la couleur C
    */

    // 2. tant que tous les sommets ne sont pas coloriés
    for (int i = 0; i < ordre; i++) {
        // 3. Considerer une couleur C, differente de toutes les couleurs deja utilisees
        int couleur = 1;

        // 4. Considerer le premier sommet dans l'ordre decroissant des degres et lui attribuer la couleur C
        // 5. Considerer chacun des autres sommets non colories dans l'ordre decroissant des degres
        for (int j = 0; j < ordre; j++) {
            // 6. S'il est adjacent a un sommet deja colorie avec la couleur C, ne lui affecter aucune couleur
            if (voisins(&operations[i], &operations[j], aretes, taille) && operations[j].color == couleur) {
                couleur++;
                j = 0;
            }
        }

        // 7. Sinon, lui affecter la couleur C
        operations[i].color = couleur;
    }
}


/*
 * Affiche les couleurs des opérations
 * @param operations : Tableau d'opérations
 * @param ordre      : Nombre d'opérations
*/
void afficher_couleurs(Operation * operations, int ordre)
{
    printf("\nCouleurs\n");

    for (int i = 0; i < ordre; i++) {
        printf("S%d\t- C %d \n", operations[i].id_operation, operations[i].color);
    }
}


/*
 * Assigne les couleurs aux opérations
 * @param operations : Tableau d'opérations
 * @param aretes     : Tableau d'aretes
 * @param ordre      : Nombre d'opérations
 * @param taille     : Nombre d'aretes
*/
Operation * assigner_couleurs(Operation * operations, Arete * aretes, int * ordre, int * taille)
{
    operations = tri_operations_degre_decroissant(operations, *ordre, *taille);

    welsh_powell_coloration(operations, aretes, *ordre, *taille);

    afficher_couleurs(operations, *ordre);

    return operations;
}


/*
 * Initialise les degres des operations
 * @param operations : Tableau d'operations
 * @param aretes     : Tableau d'aretes
 * @param ordre      : Nombre d'operations
 * @param taille     : Nombre d'aretes
 */
void init_degres(Operation * operations, Arete * aretes, int * ordre, int * taille)
{
    // initialiser les degres des operations a 0
    for(int i = 0; i < *ordre; i++)
    {
        operations[i].deg = 0;
    }

    // calculer les degres des operations
    for(int i = 0; i < *taille; i++)
    {
        for(int j = 0; j < *ordre; j++)
        {
            if(aretes[i].op_depart == operations[j].id_operation)
            {
                operations[j].deg++;
            }

            if(aretes[i].op_arrivee == operations[j].id_operation)
            {
                operations[j].deg++;
            }
        }

    }

    afficher_operations(operations, *ordre);
}