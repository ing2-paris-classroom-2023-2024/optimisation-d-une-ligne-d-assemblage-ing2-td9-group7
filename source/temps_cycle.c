#include <stdio.h>
#include "../headers/helper.h"
#include "../headers/temps_cycle.h"

void test_temps_cycle()
{
    printf("Test temps cycle\n");
}

/*
 * Retourne le temps max d'un cycle lu dans le fichier texte
 * @param file_path Chemin vers le fichier
 * @return Temps max d'un cycle
*/
int get_temps_cycle(char * file_path)
{
    printf("\nLecture du fichier %s...\n", file_path);
    int temps_cycle = 0;
    FILE * fichier = file_loader(file_path, "r");

    fscanf(fichier, "%d", &temps_cycle);
    fclose(fichier);

    printf("Temps max : %d secondes\n", temps_cycle);
    return temps_cycle;
}