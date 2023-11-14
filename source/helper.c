#include <stdio.h>
#include "../headers/helper.h"


/*
 * Charge un fichier et retourne un pointeur vers ce fichier
 * @param filepath Chemin vers le fichier
 * @param mode Mode d'ouverture du fichier
 * @return Pointeur vers le fichier
*/
FILE * file_loader(const char * filepath, const char * mode)
{
    FILE * file = fopen(filepath, mode);
    if (!file) {
        char clion_filepath[100];
        strcpy(clion_filepath, "../");
        strcat(clion_filepath, filepath);
        file = fopen(clion_filepath, mode);

        if (!file) {
            printf("Erreur lors de l'ouverture du fichier : %s\n", filepath);
            return -1;
        }
    }

    return file;
}


/*
 * Affiche les opérations de la liste des opérations
 * @param operations Tableau d'opérations
 * @param nb_operations Nombre d'opérations
*/
void afficher_operations(Operation *operations, int nb_operations)
{
    for (int i = 0; i < nb_operations; i++) {
        printf("Operation %d : %s, %.1f secondes\n", i + 1, operations[i].nom_operation, operations[i].temps_exec);
    }
}


/*
 * Retourne le temps max d'un cycle lu dans le fichier texte
 * @param file_path Chemin vers le fichier
 * @return Temps max d'un cycle
*/
int get_temps_cycle(char * file_path)
{
    printf("\nLecture du fichier %s...\n", file_path);
    int temps_cycle = 0;
    FILE * fichier = file_loader(file_path, "r");

    fscanf(fichier, "%d", &temps_cycle);
    fclose(fichier);

    printf("Temps max : %d secondes\n", temps_cycle);
    return temps_cycle;
}


/*
 * Retourne la liste des opérations lues dans le fichier texte
 * @param file_path Chemin vers le fichier
 * @return Tableau d'opérations
*/
Operation * get_operations(char * file_path)
{
    printf("\nLecture du fichier %s...\n", file_path);
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    int nb_operations = 1;
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nb_operations++;
        }
    }
    printf("Il y a %d operations :\n", nb_operations);

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Operation * operations = malloc(nb_operations * sizeof(Operation));

    // remplissage du tableau d'operations
    for (int i = 0; i < nb_operations; i++) {
        operations[i].nom_operation = malloc(100 * sizeof(char)); // Allouer suffisamment d'espace pour stocker le nom de l'opération
        fscanf(fichier, "%99s %f\n", operations[i].nom_operation, &operations[i].temps_exec);
    }

    afficher_operations(operations, nb_operations);

    fclose(fichier);
    return operations;
}
