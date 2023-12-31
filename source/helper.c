#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
    printf("\nOperations :\n");

    Color(14, 0);
    printf("OPERATION         TEMPS               PROFONDEUR         DEGRE          COULEUR\n");
    Color(15, 0);

    for (int i = 0; i < nb_operations; i++) {
        printf("Operation : %d\t T %.2fs\t\t P %d\t\t D %d\t\t C %d\n", operations[i].id_operation, operations[i].temps_operation, operations[i].profondeur, operations[i].deg, operations[i].color);
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
        printf("Arete %d : %d -> %d\n", i + 1, aretes[i].op_depart, aretes[i].op_arrivee);
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
        bloc->operations[i].id_operation = -1;
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
    int operations_vides = 0;

    for (int i = 0; i < bloc->nb_operations; i++)
    {
        if (bloc->operations[i].id_operation == -1)
        {
            operations_vides++;
        }
    }

    if (operations_vides == bloc->nb_operations)
    {
        return;
    }

    Color(11, 0);
    printf("\nBloc %d :\n", bloc->id_bloc);
    Color(14, 0);
    printf("OPERATION         TEMPS              PROFONDEUR         DEGRE          COULEUR\n");
    Color(15, 0);

    for (int i = 0; i < bloc->nb_operations; i++) {
        if (bloc->operations[i].id_operation != -1)
        {
            printf("Operation : %d\t T %.2fs\t\t P %d\t\t D %d\t\t C %d\n", bloc->operations[i].id_operation, bloc->operations[i].temps_operation,  bloc->operations[i].profondeur, bloc->operations[i].deg, bloc->operations[i].color);
        }
        bloc->temps_bloc += bloc->operations[i].temps_operation;
    }

    printf("Temps d'execution : %.2fs\n", bloc->temps_bloc);
}


/*
 * Affiche les blocs de la chaine de production
 * @param chaine_production Chaine de production
*/
void afficher_chaine_production(Chaine_production * chaine_production)
{
    Color(12, 0);
    printf("\nAffichage de la chaine de production :\n");
    Color(15, 0);

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
    int temps_cycle = 0;
    FILE * fichier = file_loader(file_path, "r");

    fscanf(fichier, "%d", &temps_cycle);
    fclose(fichier);

    Color(11, 0);
    printf("Temps max : %d secondes\n", temps_cycle);
    Color(15, 0);
    return temps_cycle;
}


/*
 * Retourne la liste des opérations lues dans le fichier texte
 * @param file_path Chemin vers le fichier
 * @return Tableau d'opérations
*/
Operation * get_operations(char * file_path, int * nb_operations)
{
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            *nb_operations += 1;
        }
    }

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Operation * operations = malloc(*nb_operations * sizeof(Operation));
    // remplissage du tableau d'operations
    for (int i = 0; i < *nb_operations; i++) { // Allouer suffisamment d'espace pour stocker le nom de l'opération
        fscanf(fichier, "%d %f\n", &operations[i].id_operation, &operations[i].temps_operation);
        operations[i].profondeur = 0;
    }

    fclose(fichier);
    return operations;
}


void Color(int couleur_texte, int couleur_fond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleur_fond * 16 + couleur_texte);
}