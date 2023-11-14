#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

// Structures

typedef struct {
    float temps_exec;
    char * nom_operation;
} Operation;

// Prototypes de fonctions

FILE * file_loader(const char * filepath, const char * mode);
void afficher_operations(Operation * operations, int nb_operations);
int get_temps_cycle(char * file_path);
Operation * get_operations(char * file_path);

#endif // HELPER_H
