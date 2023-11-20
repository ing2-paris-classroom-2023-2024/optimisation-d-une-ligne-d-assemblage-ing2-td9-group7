#ifndef PRECEDENCES_H
#define PRECEDENCES_H

#include <stdio.h>
// Structures
typedef struct {
    char * op_depart;
    char * op_arrivee;
} Arete;


Arete * get_precedences(char * filename);

#endif // PRECEDENCES_H