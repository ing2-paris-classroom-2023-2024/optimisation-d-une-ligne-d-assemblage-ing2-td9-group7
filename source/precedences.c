#include <stdio.h>
#include <stdlib.h>
#include "../headers/helper.h"
#include "../headers/precedences.h"


/*
 * Retourne les aretes lues dans le fichier texte
 * @param file_path : Chemin vers le fichier
 * @return aretes   :Tableau d'aretes
 */
Arete * get_precedences(char * file_path, int * taille)
{
    FILE * fichier = file_loader(file_path, "r");

    // recupere le nombre de ligne du fichier
    char c;
    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            (*taille)++;
        }
    }

    // retour au debut du fichier
    rewind(fichier);

    // creation du tableau d'operations
    Arete * aretes = malloc(*taille * sizeof(Arete));

    // remplissage du tableau d'operations
    for (int i = 0; i < *taille; i++) {
        fscanf(fichier, "%d %d", &aretes[i].op_depart, &aretes[i].op_arrivee);
    }

    fclose(fichier);
    return aretes;
}


/*
 * Assigne la profondeur de chaque opération en fonction du graphe de precedence
 * @param operation_actuelle : operation en cours de traitement
 * @param aretes             : tableau d'aretes
 * @param visite             : tableau des operations visites
 * @param operations         : liste des operations
 * @param profondeur_actuelle: profondeur actuelle
 * @param taille             : taille du tableau d'aretes
 */
void parcoursProfondeur(int operation_actuelle, Arete * aretes, int * visite, Operation * operations, int profondeur_actuelle, int taille) {
    // Marquer le sommet courant comme visité
    visite[operation_actuelle] = 1;

    // Parcourir tous les sommets adjacents au sommet courant
    for (int i = 0; i < taille; i++) {
        if (aretes[i].op_depart == operation_actuelle) {
            // Si le sommet n'a pas été visité, on l'explore
            if (visite[aretes[i].op_arrivee] == 0) {
                parcoursProfondeur(aretes[i].op_arrivee, aretes, visite, operations, profondeur_actuelle + 1, taille);
            }
        }
    }

    // Mettre à jour la profondeur de l'opération
    if (operations[operation_actuelle - 1].profondeur < profondeur_actuelle) {
        operations[operation_actuelle - 1].profondeur = profondeur_actuelle;
    }
}


/*
 * Trie les opérations par profondeur croissante
 * @param operations : Tableau d'opérations
 * @param taille     : Taille du tableau
 * @return operation_triees : Tableau d'opérations triées
 */
Operation * tri_operations_profondeur(Operation * operations, int taille)
{
    Operation * operations_triees = malloc(taille * sizeof(Operation));

    for (int i = 0; i < taille; i++) {
        operations_triees[i] = operations[i];
    }

    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille - 1; j++) {
            if (operations_triees[j].profondeur > operations_triees[j + 1].profondeur) {
                Operation temp = operations_triees[j];
                operations_triees[j] = operations_triees[j + 1];
                operations_triees[j + 1] = temp;
            }
        }
    }

    return operations_triees;
}


/*
 * Optimise le nombre de stations de travail en fonction du graphe de precedence
 * @return chaine_production : Tableau de station
 */
//! Attention : Si une operation ne figure pas dans les precedences, elle peut etre n'importe ou
//& faire une grosse liste d'opération en suivant les precedences
//& puis la découper en blocs avec la contrainte de temps de cycle
Chaine_production * chaine_precedences(int nombre_operations, int taille, Operation * operations, Arete * aretes)
{
    int nombre_blocs = nombre_operations;

    // On crée la chaine
    Chaine_production * chaine_production = init_chaine_production(nombre_blocs, nombre_operations);
    //afficher_chaine_production(chaine_production);

    return chaine_production;
}