#include <stdio.h>
#include <stdlib.h>
#include "../headers/helper.h"
#include "../headers/precedences.h"


/*
 * Retourne les aretes lues dans le fichier texte
 * @param file_path Chemin vers le fichier
 * @return Tableau d'aretes
 */
Arete * get_precedences(char * file_path)
{
    printf("\nLecture du fichier %s...\n", file_path);
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    int taille = 1;
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            taille++;
        }
    }
    printf("Il y a %d aretes :\n", taille);

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Arete * aretes = malloc(taille * sizeof(Arete));

    // remplissage du tableau d'operations
    for (int i = 0; i < taille; i++) {
        aretes[i].op_depart = malloc(100 * sizeof(char)); // Allouer suffisamment d'espace pour stocker le nom de l'opération
        aretes[i].op_arrivee = malloc(100 * sizeof(char)); // Allouer suffisamment d'espace pour stocker le nom de l'opération
        fscanf(fichier, "%s %s", aretes[i].op_depart, aretes[i].op_arrivee);
    }

    afficher_aretes(aretes, taille);

    fclose(fichier);
    return aretes;
}


/*
 * Retourne la chaine de production lue dans les fichiers textes
 * @return Tableau de blocs
 */
//! Attention : Si une operation ne figure pas dans les precedences, elle peut etre n'importe ou
//& faire une grosse liste d'opération en suivant les precedences
//& puis la découper en blocs avec la contrainte de temps de cycle
Chaine_production * chaine_precedences()
{
    int nombre_operations = 1;

    // On récupère les opérations et les arêtes
    Operation * operations = get_operations("data/operations.txt", &nombre_operations);
    Arete * aretes = get_precedences("data/precedences.txt");

    printf("Nombre d'operations : %d\n", nombre_operations);

    int nombre_blocs = nombre_operations;

    // On crée la chaine
    Chaine_production * chaine_production = init_chaine_production(nombre_blocs, nombre_operations);
    afficher_chaine_production(chaine_production);
}