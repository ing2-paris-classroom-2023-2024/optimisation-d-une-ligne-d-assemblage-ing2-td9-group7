#include <stdio.h>
#include <stdlib.h>
#include "utils/helper.h"
#include "contraintes/exclusions.h"
#include "contraintes/precedences.h"
#include "contraintes/temps_cycle.h"


int main()
{
    printf("Hello World!\n");
    test_exclusions();
    test_precedences();
    test_temps_cycle();
    test_helper();
    return 0;
}