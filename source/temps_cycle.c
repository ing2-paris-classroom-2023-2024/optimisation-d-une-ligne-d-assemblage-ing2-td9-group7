#include "../headers/helper.h"


// Fonction de répartition des opérations entre les stations
void repartir_operations(Chaine_production * chaine_production, Operation * operations, int nb_operations, Arete * aretes, int taille_aretes, int temps_cycle) {

    printf("\nRepartition des operations entre les stations...\n");

    // parcourir la liste de blocs de la chaine de production
    float temps_total = 0;
    int num_bloc = 0;

    for (int i = 0; i < nb_operations; i++)
    {
        Operation * operation_actuelle = &operations[i];
        float temps_operation = operation_actuelle->temps_operation;

        if (temps_total + temps_operation > temps_cycle) {
            num_bloc++;
            temps_total = temps_operation;
        }
        else{
            temps_total += temps_operation;
        }

        printf("tps total : %.1f\n", temps_total);
        printf("ajouter l'operation %d au bloc %d\n", operation_actuelle->id_operation, num_bloc);

        // ajouter l'operation au bloc
        Bloc * bloc_actuel = chaine_production->blocs[num_bloc];
        if (bloc_actuel->operations[i].id_operation == -1)
        {
            printf("ajout\n");
            bloc_actuel->operations[i] = *operation_actuelle;
        }
    }
}


// Fonction de tri des opérations par profondeur et temps
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