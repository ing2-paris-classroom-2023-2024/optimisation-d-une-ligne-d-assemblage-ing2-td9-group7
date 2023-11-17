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
    printf("Hello World!\n");

    int temps_cycle = get_temps_cycle("data/temps_cycle.txt");
    Operation * operations = get_operations("data/operations.txt");

    return 0;
}