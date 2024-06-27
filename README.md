

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *fichier;
    char expression[1000]; // Taille maximale de l'expression

    // Ouvrir le fichier en mode lecture
    fichier = fopen("expression.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Lire l'expression depuis le fichier
    if (fgets(expression, sizeof(expression), fichier) == NULL) {
        perror("Erreur lors de la lecture de l'expression depuis le fichier");
        fclose(fichier);
        return 1;
    }

    // Fermer le fichier après lecture
    fclose(fichier);

    // Supprimer le saut de ligne final s'il existe
    expression[strcspn(expression, "\n")] = '\0';

    // Effectuer l'analyse lexicale de l'expression lue
    analyse_lexicale(expression);

    return 0;
}
