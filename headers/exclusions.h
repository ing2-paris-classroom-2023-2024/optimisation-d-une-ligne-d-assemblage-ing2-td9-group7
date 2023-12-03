#ifndef EXCLUSIONS_H
#define EXCLUSIONS_H

#include <stdio.h>


int voisins(Operation * operation_1, Operation * operation_2, Arete * aretes, int taille);
void welsh_powell_coloration(Operation * operations, Arete * aretes, int ordre, int taille);
void afficher_couleurs(Operation * operations, int ordre);
void init_degres(Operation * operations, Arete * aretes, int * ordre, int * taille);
Arete * get_exclusions(char * file_path, int * taille);
Operation * tri_operations_degre_decroissant(Operation * operations, int ordre, int taille);
Operation * assigner_couleurs(Operation * operations, Arete * aretes, int * ordre, int * taille);

#endif // EXCLUSIONS_H