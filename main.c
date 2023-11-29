#include <stdio.h>
#include "headers/helper.h"
#include "source/helper.c"
#include "headers/temps_cycle.h"
#include "source/temps_cycle.c"
#include "headers/exclusions.h"
#include "source/exclusions.c"
#include "headers/precedences.h"
#include "source/precedences.c"

int main()
{
    /*int taille = 1;
    int ordre = 1;

    Arete* aretes_exclusions;
    Operation* operations_excluisons;
    Operation * test;

    aretes_exclusions = get_arete("./data/exclusions.txt",&taille);
    operations_excluisons =get_operation("./data/operations.txt", &ordre);
    test = get_degre("./data/exclusions.txt", operations_excluisons, taille, ordre);*/
    int ordre = 1;
    Operation* operations_excluisons = init_graphe(&ordre);
    Operation* operations_triees = triDecroissant( operations_excluisons, &ordre);

    return 0;
}