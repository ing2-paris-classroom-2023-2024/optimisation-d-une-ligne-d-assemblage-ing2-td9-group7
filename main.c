#include <stdio.h>
#include <stdlib.h>
#include "headers/helper.h"
#include "source/helper.c"
#include "headers/temps_cycle.h"
#include "source/temps_cycle.c"
#include "headers/exclusions.h"
#include "source/exclusions.c"
#include "headers/precedences.h"
#include "source/precedences.c"
#include "headers/multi_contraintes.h"
#include "source/multi_contraintes.c"

int menu()
{ // menu principal

    Color(10, 0);
    int choix = 0;
    printf("\n~~~~~~ ! MENU PRINCIPAL ! ~~~~~~\n\n");
    Color(15, 0);
    printf("Choisissez une option : \n\n");
    printf("1. Contrainte d'exclusion \n");
    printf("2. Contrainte de temps de cycle et precedence \n");
    printf("3. Multi-contrainte \n\n");
    printf("4. Quitter \n\n");
    printf("Votre choix : ");

    do
    {
        scanf("%d", &choix);
    } while (choix < 1 || choix > 4);

    return choix;
}

int main()
{
    int choix = menu();

    do
    {
        if (choix == 1)
        {
            Color(12, 0);
            printf("Contrainte d'exclusion\n");
            Color(15, 0);
            contrainte_exclusion();
        }
        else if (choix == 2)
        {
            Color(12, 0);
            printf("Contrainte de temps de cycle et precedence\n");
            Color(15, 0);

            // Initialisation des variables
            int nombre_operations = 1;
            int taille = 1;

            // On récupère les opérations et les arêtes
            Operation *operations = get_operations("data/operations.txt", &nombre_operations);
            Arete *aretes = get_precedences("data/precedences.txt", &taille);
            int temps_cycle = get_temps_cycle("data/temps_cycle.txt");

            // Effectuer le parcours en profondeur
            int *visite = (int *)malloc(nombre_operations * sizeof(int));

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
            parcoursProfondeur(sommetDepart, aretes, visite, operations, 0, taille);

            free(visite);
            // Obtient la liste triée
            operations = tri_operations_profondeur(operations, nombre_operations);
            operations = tri_operations_temps_decroissant(operations, nombre_operations);

            // Créer la chaîne de production
            Chaine_production *chaine_production = chaine_precedences(nombre_operations, taille, operations, aretes);

            // Répartir les opérations entre les stations
            repartir_operations_optimise(chaine_production, operations, nombre_operations, aretes, taille, temps_cycle);

            // Afficher la chaîne de production
            afficher_chaine_production(chaine_production);

            // Libérer la mémoire allouée
            free(chaine_production);
            free(operations);
            free(aretes);
        }
        else if (choix == 3)
        {
            Color(12, 0);
            printf("Multi contraintes\n");
            Color(15, 0);

            multi_contraintes();
        }

        choix = menu();

    } while (choix != 4);

    printf("\n~~~~~~ ! FIN DU PROGRAMME ! ~~~~~~\n\n");

    return 0;
}
