#ifndef PRECEDENCES_H
#define PRECEDENCES_H

#include <stdio.h>
// Structures
typedef struct {
    int op_depart;
    int op_arrivee;
} Arete;


Arete * get_precedences(char * filename, int * taille);

#endif // PRECEDENCES_H