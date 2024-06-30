#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Fonction pour vérifier si un caractère est un opérateur (+, *, (, ))
int est_operateur(char c) {
    return (c == '+' || c == '*' || c == '(' || c == ')');
}

// Fonction pour effectuer l'analyse lexicale d'une expression
void analyse_lexicale(char *expression) {
    int i = 0;
    int len = strlen(expression);
    int entier;

    while (i < len) {
        if (isdigit(expression[i])) { // Si le caractère est un chiffre
            if (sscanf(&expression[i], "%d", &entier) == 1) { // Lecture d'un entier de taille quelconque
                printf("<int:%d>", entier);
                // Trouver la longueur de l'entier dans la chaîne et avancer de cette longueur
                while (i < len && isdigit(expression[i])) {
                    i++;
                }
            } else {
                printf("Erreur de syntaxe : entier mal formé\n");
                return;
            }
        } else if (est_operateur(expression[i])) { // Si le caractère est un opérateur ou une parenthèse
            printf("<operateur:%c>", expression[i]); // Affichage de l'opérateur
            i++;
        } else if (isspace(expression[i])) { // Ignorer les espaces
            i++;
        } else { // Caractère non valide
            printf("Erreur de syntaxe : caractère non valide '%c'\n", expression[i]);
            return;
        }
    }

    printf("\nAnalyse lexicale réussie.\n");
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fichier;
    char expression[1000]; // Taille maximale de l'expression

    char *fichierr=argv[1];
    // Ouvrir le fichier en mode lecture
    fichier = fopen(fichierr, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Lire et analyser chaque ligne du fichier
    while (fgets(expression, sizeof(expression), fichier) != NULL) {
        // Supprimer le saut de ligne final s'il existe
        expression[strcspn(expression, "\n")] = '\0';

        // Effectuer l'analyse lexicale de l'expression lue
        analyse_lexicale(expression);
    }

    // Fermer le fichier après lecture
    fclose(fichier);

    return 0;
}
