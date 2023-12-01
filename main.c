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
    int size;
    Operation * operations_exclusions = init_graphe(&ordre, &size);
    Operation * operations_triees = triDecroissantDegre( operations_exclusions, &ordre, &size);

    printf("\nFINITO\n");
    return 0;
}