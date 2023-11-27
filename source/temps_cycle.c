// temps_cycle.c

#include "../headers/helper.h"
#include <stdlib.h>


/*
* Retourne les opérations triées par temps décroissant en conservant la profondeur.
* @param operations : Tableau d'opérations
* @param taille : Nombre d'opérations
* @return operations_triees : Tableau d'opérations triées
*/
Operation * tri_operations_temps_decroissant(Operation * operations, int taille) {

    // Tri des opérations par temps décroissant en conservant la profondeur
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille - 1; j++) {
            if (operations[j].temps_operation < operations[j + 1].temps_operation && operations[j].profondeur == operations[j + 1].profondeur) {
                Operation temp = operations[j];
                operations[j] = operations[j + 1];
                operations[j + 1] = temp;
            }
        }
    }

    return operations;
}


/*
Cette fonction répartit les opérations entre les stations de manière optimisée en respectant le temps de cycle.
* @param chaine_production : Chaîne de production
* @param operations : Tableau d'opérations à répartir
* @param nb_operations : Nombre d'opérations
* @param aretes : Tableau des arêtes
* @param taille_aretes : Nombre d'arêtes
* @param temps_cycle : Temps de cycle à respecter
*/
void repartir_operations_optimise(Chaine_production * chaine_production, Operation * operations, int nb_operations, Arete * aretes, int taille_aretes, int temps_cycle)
{
    printf("\nRepartition des operations entre les stations de maniere optimisee...\n");

    float temps_total = 0;
    int num_bloc = 0;

    int i = 0;
    while (i < nb_operations) {
        Operation * operation_actuelle = &operations[i];
        float temps_operation = operation_actuelle->temps_operation;

        if (temps_total + temps_operation > temps_cycle) {
            int j = i + 1;
            float temps_suivant = 0;
            int meilleur_j = -1;
            float meilleur_diff = temps_cycle;
            while (j < nb_operations && operations[j].profondeur == operation_actuelle->profondeur) {
                temps_suivant += operations[j].temps_operation;
                float diff = abs((temps_total + temps_suivant) - temps_cycle);
                if (diff < meilleur_diff) {
                    meilleur_diff = diff;
                    meilleur_j = j;
                }
                j++;
            }
            if (meilleur_j != -1) {
                temps_suivant = 0;
                for (int k = i + 1; k <= meilleur_j; k++) {
                    temps_suivant += operations[k].temps_operation;
                }
                if (temps_total + temps_suivant <= temps_cycle) {
                    for (int k = i + 1; k <= meilleur_j; k++) {
                        printf("ajouter l'operation %d au bloc %d\n", operations[k].id_operation, num_bloc);
                        Bloc * bloc_actuel = chaine_production->blocs[num_bloc];
                        bloc_actuel->operations[k] = operations[k];
                    }
                    i = meilleur_j;
                }
            }
            num_bloc++;
            temps_total = temps_operation;
        } else {
            temps_total += temps_operation;
        }

        printf("tps total : %.1f\n", temps_total);
        printf("ajouter l'operation %d au bloc %d\n", operation_actuelle->id_operation, num_bloc);

        Bloc * bloc_actuel = chaine_production->blocs[num_bloc];
        bloc_actuel->operations[i] = *operation_actuelle;
        i++;
    }
}