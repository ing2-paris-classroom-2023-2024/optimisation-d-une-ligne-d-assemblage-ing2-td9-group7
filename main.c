#include <stdio.h>
#include <stdlib.h>
#include "utils/helper.h"
#include "contraintes/exclusions.h"
#include "contraintes/precedences.h"
#include "contraintes/temps_cycle.h"


int main()
{
    printf("Hello World!\n");

    int temps_cycle = get_temps_cycle("data/temps_cycle.txt");

    Operation * operations = get_operations("data/operations.txt");
    
    return 0;
}