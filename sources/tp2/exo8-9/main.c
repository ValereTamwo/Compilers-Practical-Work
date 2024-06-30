#include <stdio.h>
#include "utilitaire.h"


// fonction pour lire le fichier et évaluer les expressions
void readFileAndEvaluate(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", filename);
        return;
    }

    char expression[256];
    while (fgets(expression, sizeof(expression), file))
    {
        printf("Expression: %s\n", expression);
        exp_post_fixe_sans_prio(expression);
        
        exp_post_fixe_avec_prio(expression);
    }

    fclose(file);
}

//fonction principale
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    readFileAndEvaluate(argv[1]);
    return 0;
}
