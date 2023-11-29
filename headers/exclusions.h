#include <stdio.h>


Arete * get_arete(char * file_path, int * taille);
void afficher_operation(Operation * operations, int nb_operations);
Operation * get_operation(char * file_path, int * ordre);
Operation* triDecroissant(Operation*  operations , int* ordre);
Operation* get_degre(char * file_path, Operation* operations, int taille, int ordre);