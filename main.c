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
    int ordre = 1;
    int taille = 1;
    Arete * aretes = get_exclusions("data/exclusions.txt", &taille);
    Operation * operations = get_operations("data/operations.txt", &ordre);

    init_degres(operations, aretes, &ordre, &taille);
    operations = assigner_couleurs(operations, aretes, &ordre, &taille);

    printf("\nFINITO\n");
    return 0;
}