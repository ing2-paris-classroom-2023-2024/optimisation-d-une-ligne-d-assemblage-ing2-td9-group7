#include <stdio.h>
#include <stdlib.h>
#include "../headers/helper.h"
#include "../headers/temps_cycle.h"
#include "../headers/exclusions.h"
#include "../headers/precedences.h"


Operation * tri_operations_couleur(Operation * operations, int nombre_operations)
{
    Operation * operations_triees = malloc(nombre_operations * sizeof(Operation));
    memcpy(operations_triees, operations, nombre_operations * sizeof(Operation));

    for (int i = 0; i < nombre_operations - 1; i++)
    {
        for (int j = 0; j < nombre_operations - i - 1; j++)
        {
            if (operations_triees[j].color > operations_triees[j + 1].color && operations_triees[j].profondeur == operations_triees[j + 1].profondeur)
            {
                Operation temp = operations_triees[j];
                operations_triees[j] = operations_triees[j + 1];
                operations_triees[j + 1] = temp;
            }
        }
    }

    return operations_triees;
}


void repartir_operations_multi_contraintes(Operation * operations, Arete * aretes_precedences, Arete * aretes_exclusions, int nombre_operations, int taille_precedences, int taille_exclusions, int temps_cycle)
{
    // On trie les opérations par ordre décroissant de degré
    int * visite = (int *)malloc(nombre_operations * sizeof(int));

    if (visite == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nombre_operations; i++)
    {
        visite[i] = 0;
    }

    // Choisir un sommet de départ
    int sommetDepart = 1;

    // Effectuer le parcours en profondeur
    parcoursProfondeur(sommetDepart, aretes_precedences, visite, operations, 0, taille_precedences);

    free(visite);
    // Obtient la liste triée
    operations = tri_operations_profondeur (operations , nombre_operations);

    operations = tri_operations_degre_decroissant(operations, nombre_operations, taille_exclusions);
    welsh_powell_coloration(operations, aretes_exclusions, nombre_operations, taille_exclusions);

    // il faut trier les oeprations par ordre croissant de couleur
    operations = tri_operations_couleur(operations, nombre_operations);

    // On initialise la chaine de production
    Chaine_production * chaine_production = chaine_precedences(nombre_operations, taille_exclusions, operations, aretes_precedences);

    // repartir les operations dans les blocs. si la couelur est la meme, on ajoute l'operation dans le bloc actuel. sinon, on increment l'id du bloc
    int id_bloc = 0;
    int couleur_precedente = 1;
    int temps_tot = 0;
    Bloc * bloc_actuel = chaine_production->blocs[0];

    for (int i = 0; i < nombre_operations; i++)
    {
        // repartir les operations dans les stations en fonction de leur couleur
        int couleur = operations[i].color;
        int station = couleur - 1;

        // placer l'operation dans la station
        if (couleur == couleur_precedente && temps_tot + operations[i].temps_operation <= temps_cycle)
        {
            // ajouter l'operation dans le bloc
            bloc_actuel->operations[i] = operations[i];

            temps_tot += operations[i].temps_operation;
            bloc_actuel->temps_bloc = temps_tot;
        }
        else
        {
            // on change de bloc
            id_bloc++;
            bloc_actuel = chaine_production->blocs[id_bloc];

            bloc_actuel->operations[i] = operations[i];

            temps_tot = operations[i].temps_operation;
            bloc_actuel->temps_bloc = 0;
            bloc_actuel->temps_bloc = temps_tot;
        }

        couleur_precedente = couleur;
    }

    // Afficher la chaîne de production
    afficher_chaine_production(chaine_production);
}


/*
 * Reparti les opérations en fonction de toutes les contraintes

*/
void multi_contraintes()
{
    int taille_exclusions = 1;
    int taille_precedences = 1;
    int nombre_operations = 1;

    // On récupère les opérations et les arêtes d'exclusion et de précédence
    int temps_cycle = get_temps_cycle("data/temps_cycle.txt");

    Arete * aretes_exclusions = get_exclusions("data/exclusions.txt", &taille_exclusions);
    Arete * aretes_precedences = get_precedences("data/precedences.txt", &taille_precedences);
    Operation * operations = get_operations("data/operations.txt", &nombre_operations);

    repartir_operations_multi_contraintes(operations, aretes_precedences, aretes_exclusions, nombre_operations, taille_precedences, taille_exclusions, temps_cycle);
}