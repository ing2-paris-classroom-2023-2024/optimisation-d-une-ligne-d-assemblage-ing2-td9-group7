// temps_cycle.h

#ifndef TEMPS_CYCLE_H
#define TEMPS_CYCLE_H

#include "helper.h"
#include <stdlib.h>

// Fonction de tri des opérations par profondeur croissante et temps décroissant
Operation * tri_operations_temps_decroissant(Operation * operations, int taille);

// Fonction de répartition des opérations entre les stations
void repartir_operations(Chaine_production *chaine_production, Operation *operations, int nb_operations, Arete *aretes, int taille_aretes, int temps_cycle);

#endif // TEMPS_CYCLE_H
