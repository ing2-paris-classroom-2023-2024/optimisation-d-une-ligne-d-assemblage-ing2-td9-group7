// temps_cycle.c

#include "../headers/helper.h"
#include <stdlib.h>
#include <stdbool.h>


/*
 * Retourne les opérations triées par temps décroissant en conservant la profondeur.
 * @param operations : Tableau d'opérations
 * @param taille : Nombre d'opérations
 * @return operations_triees : Tableau d'opérations triées
*/
Operation * tri_operations_temps_decroissant(Operation * operations, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille - 1; j++)
        {
            if (operations[j].temps_operation < operations[j + 1].temps_operation && operations[j].profondeur == operations[j + 1].profondeur)
            {
                Operation temp = operations[j];
                operations[j] = operations[j + 1];
                operations[j + 1] = temp;
            }
        }
    }

    return operations;
}


/*
 * Répartit les opérations entre les stations de manière optimisée en respectant le temps de cycle.
 * @param chaine_production : Chaîne de production
 * @param operations : Tableau d'opérations à répartir
 * @param nb_operations : Nombre d'opérations
 * @param aretes : Tableau des arêtes
 * @param taille_aretes : Nombre d'arêtes
 * @param temps_cycle : Temps de cycle à respecter
*/
void repartir_operations_optimise(Chaine_production * chaine_production, Operation * operations, int nb_operations, Arete * aretes, int taille_aretes, int temps_cycle)
{
    float temps_total = 0;
    int num_bloc = 0;

    // Tableau pour marquer les opérations incluses dans un bloc
    bool * operation_incluse = (bool *)malloc(nb_operations * sizeof(bool));

    if (operation_incluse == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nb_operations; i++)
    {
        operation_incluse[i] = false;
    }

    int i = 0;
    while (i < nb_operations)
    {
        if (operation_incluse[i])
        {
            i++;
            continue;
        }

        Operation * operation_actuelle = &operations[i];
        float temps_operation = operation_actuelle->temps_operation;

        if (temps_total + temps_operation > temps_cycle)
        {
            int j = i + 1;
            float temps_suivant = 0;
            int meilleur_j = -1;
            float meilleur_diff = temps_cycle - temps_total;

            while (j < nb_operations && operations[j].profondeur == operation_actuelle->profondeur)
            {
                temps_suivant += operations[j].temps_operation;
                float diff = abs((temps_total + temps_suivant) - temps_cycle);

                if (diff < meilleur_diff)
                {
                    meilleur_diff = diff;
                    meilleur_j = j;
                }
                j++;
            }

            // boucle permettant de parcourir les opérations de même profondeur que la dernière du bloc afin d'optimiser les blocs et leurs nombres
            j = i + 1;
            while (j < nb_operations && operations[j].profondeur == operation_actuelle->profondeur)
            {
                float diff = abs((temps_total + temps_operation + operations[j].temps_operation) - temps_cycle);

                if (diff <= meilleur_diff)
                {
                    meilleur_diff = diff;
                    meilleur_j = j;
                }

                j++;
            }

            if (meilleur_j != -1)
            {
                temps_suivant = 0;

                for (int k = i + 1; k <= meilleur_j; k++)
                {
                    temps_suivant += operations[k].temps_operation;
                }
                if (temps_total + temps_suivant <= temps_cycle)
                {
                    for (int k = i + 1; k <= meilleur_j; k++) {
                        Bloc * bloc_actuel = chaine_production->blocs[num_bloc];
                        bloc_actuel->operations[k] = operations[k];
                        // Marquer l'opération comme incluse
                        operation_incluse[k] = true;
                    }
                    i = meilleur_j;
                }
            }
            num_bloc++;
            temps_total = temps_operation;
        }
        else
        {
            temps_total += temps_operation;
        }

        Bloc * bloc_actuel = chaine_production->blocs[num_bloc];
        bloc_actuel->operations[i] = *operation_actuelle;
        // Marquer l'opération comme incluse
        operation_incluse[i] = true;
        i++;
    }

    free(operation_incluse);
}
