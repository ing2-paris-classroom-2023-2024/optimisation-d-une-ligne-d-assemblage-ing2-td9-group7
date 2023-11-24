#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <string.h>
#include "precedences.h"

// Structures

typedef struct {
    float temps_operation;
    int id_operation;
    int profondeur;
} Operation;

typedef struct {
    int id_bloc;
    float temps_bloc;
    int nb_operations;
    Operation * operations;
} Bloc;


typedef struct {
    int nb_blocs;
    Bloc ** blocs;
} Chaine_production;

// Prototypes de fonctions

FILE * file_loader(const char * filepath, const char * mode);
void afficher_operations(Operation * operations, int nb_operations);
void afficher_aretes(Arete * aretes, int taille);
void afficher_bloc(Bloc * bloc);
void afficher_chaine_production(Chaine_production * chaine_production);
int get_temps_cycle(char * file_path);
Operation * get_operations(char * file_path, int * nb_operations);

#endif // HELPER_H
