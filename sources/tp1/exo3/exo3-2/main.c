#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/init.h"

int main(int argc, char *argv[])
{

    printf("_-__-SERIE 1 : Travaux Pratiques Theories des langages et compilations _-__-");
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <mot> <fichier>\n", argv[0]);
        return 1;
    }

    char *mot = argv[1];
    char *fichier = argv[2];

    int occurences = compterOccurrences(mot, fichier);
    // int occurences = 9;

    if (occurences >= 0)
    {
        printf("\n Le mot \"%s\" apparait %d fois dans le fichier \"%s\".\n", mot, occurences, fichier);
    }

    return 0;
}
    