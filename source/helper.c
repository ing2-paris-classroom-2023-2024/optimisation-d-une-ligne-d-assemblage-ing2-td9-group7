#include <stdio.h>
#include <stdlib.h>
#include "../headers/helper.h"
#include "../headers/precedences.h"


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
            exit(1);
        }
    }

    return file;
}


/*
 * Affiche les opérations de la liste des opérations
 * @param operations Tableau d'opérations
 * @param nb_operations Nombre d'opérations
*/
void afficher_operations(Operation * operations, int nb_operations)
{
    for (int i = 0; i < nb_operations; i++) {
        printf("Operation %d : %s, %.1fs\n", i + 1, operations[i].nom_operation, operations[i].temps_operation);
    }
}


/*
 * Affiche les aretes de la liste des aretes
 * @param aretes Tableau d'aretes
 * @param taille Nombre d'aretes
*/
void afficher_aretes(Arete * aretes, int taille)
{
    for (int i = 0; i < taille; i++) {
        printf("Arete %d : %s -> %s\n", i + 1, aretes[i].op_depart, aretes[i].op_arrivee);
    }
}


/*
 * Initialise un bloc
 * @param nb_op_total Nombre d'opérations total
 * @param nb_op Nombre d'opérations du bloc
 * @return Bloc initialisé
*/
Bloc * init_bloc(int nb_op_total, int nb_op, int id) {
    Bloc * bloc = malloc(sizeof(Bloc));

    bloc->id_bloc = id;
    bloc->temps_bloc = 0;
    bloc->nb_operations = nb_op;
    bloc->operations = malloc(nb_op_total * sizeof(Operation));

    for (int i = 0; i < nb_op; i++) {
        bloc->operations[i].nom_operation = malloc(100 * sizeof(char));
        bloc->operations[i].nom_operation = "NULL";
        bloc->operations[i].temps_operation = 0;
    }

    return bloc;
}


/*
 * Retourne le temps d'un bloc
 * @param bloc Bloc
 * @return Temps du bloc
*/
int calculate_bloc_time(Bloc * bloc) {
    int temps_bloc = 0;

    for (int i = 0; i < bloc->nb_operations; i++) {
        temps_bloc += bloc->operations[i].temps_operation;
    }

    return temps_bloc;
}


/*
 * Initialise une chaine de production
 * @param nb_blocs Nombre de blocs
 * @param nb_op_total Nombre d'opérations total
 * @return Chaine de production initialisée
*/
Chaine_production * init_chaine_production(int nb_blocs, int nb_op_total) {
    Chaine_production * chaine_production = malloc(sizeof(Chaine_production));
    chaine_production->nb_blocs = nb_blocs;
    chaine_production->blocs = malloc(nb_blocs * sizeof(Bloc *));

    for (int i = 0; i < nb_blocs; i++) {
        chaine_production->blocs[i] = init_bloc(nb_op_total, nb_blocs, i + 1);
    }

    return chaine_production;
}


/*
 * Affiche un bloc d'opérations
 * @param blocs Tableau de blocs
 * @param taille Nombre de blocs
*/
void afficher_bloc(Bloc * bloc)
{
    printf("\nBloc %d :\n", bloc->id_bloc);

    for (int i = 0; i < bloc->nb_operations; i++) {
        printf("Operation %d : %s, %.1f secondes\n", i + 1, bloc->operations[i].nom_operation, bloc->operations[i].temps_operation);
        bloc->temps_bloc += bloc->operations[i].temps_operation;
    }

    printf("Temps d'execution : %d secondes\n", bloc->temps_bloc);
}


/*
 * Affiche les blocs de la chaine de production
 * @param chaine_production Chaine de production
*/
void afficher_chaine_production(Chaine_production * chaine_production)
{
    printf("\nAffichage de la chaine de production :\n");

    for (int i = 0; i < chaine_production->nb_blocs; i++) {
        afficher_bloc(chaine_production->blocs[i]);
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
Operation * get_operations(char * file_path, int * nb_operations)
{
    printf("\nLecture du fichier %s...\n", file_path);
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            *nb_operations += 1;
        }
    }
    printf("Il y a %d operations :\n", * nb_operations);

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Operation * operations = malloc(*nb_operations * sizeof(Operation));

    // remplissage du tableau d'operations
    for (int i = 0; i < *nb_operations; i++) {
        operations[i].nom_operation = malloc(100 * sizeof(char)); // Allouer suffisamment d'espace pour stocker le nom de l'opération
        fscanf(fichier, "%99s %f\n", operations[i].nom_operation, &operations[i].temps_operation);
    }

    afficher_operations(operations, *nb_operations);

    fclose(fichier);
    return operations;
}
