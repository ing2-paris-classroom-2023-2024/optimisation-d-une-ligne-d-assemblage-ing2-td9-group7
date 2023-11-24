#include <stdio.h>
#include "headers/helper.h"
#include "source/helper.c"
#include "headers/temps_cycle.h"
#include "source/temps_cycle.c"
#include "headers/exclusions.h"
#include "source/exclusions.c"
#include "headers/precedences.h"
#include "source/precedences.c"


int main()
{
    printf("Hello World!\n");
//! trier et afficher les opérations par profondeur
    int nombre_operations = 1;
    int taille = 1;

    // On récupère les opérations et les arêtes
    Operation * operations = get_operations("data/operations.txt", &nombre_operations);
    Arete * aretes = get_precedences("data/precedences.txt", &taille);
    int temps_cycle = get_temps_cycle("data/temps_cycle.txt");

    // Effectuer le parcours en profondeur
    int * visite = (int*)malloc(nombre_operations * sizeof(int));

    for (int i = 0; i < nombre_operations; i++) {
        visite[i] = 0; // Aucun sommet n'a été visité au début
    }

    // Choisir un sommet de départ (par exemple, le premier sommet de la liste)
    int sommetDepart = 1;

    // Effectuer le parcours en profondeur
    parcoursProfondeur(sommetDepart, aretes, visite, operations, 0, taille);

    free(visite);

    // Trier les opérations par profondeur
    operations = tri_operations_profondeur(operations, nombre_operations);
    operations = tri_operations_temps_decroissant(operations, nombre_operations);

    // Afficher les opérations
    afficher_operations(operations, nombre_operations);
//! fin trier et afficher les opérations par profondeur

    Chaine_production * chaine_production = chaine_precedences(nombre_operations, taille, operations, aretes);

    repartir_operations(chaine_production, operations, nombre_operations, aretes, taille, temps_cycle);

    afficher_chaine_production(chaine_production);

    return 0;
}