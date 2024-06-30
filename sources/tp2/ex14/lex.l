%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Inclure ctype.h pour utiliser isdigit()

#define MAX_STACK_SIZE 100

// Définition des états de l'automate à pile
typedef enum {
    Q0, Q1, Q2, Q3, Q4
} State;

State transition(State current_state, char input, char *stack, int *top) {
    switch (current_state) {
        case Q0:
            if (input == 'i') {
                stack[(*top)++] = 'i'; // Empile 'i'
                return Q1;
            } else if (input == '(') {
                stack[(*top)++] = '('; // Empile '('
                return Q2;
            } else if (isdigit(input)) { // Utilisation de isdigit() pour vérifier si input est un chiffre
                stack[(*top)++] = input; // Empile le nombre
                return Q4;
            }
            break;
        case Q1:
            if (input == '+') {
                return Q0; // Retour à Q0 après avoir rencontré '+'
            } else if (input == '*') {
                return Q0; // Retour à Q0 après avoir rencontré '*'
            } else if (input == '$' && (*top == 0)) {
                return Q3; // Acceptation
            }
            break;
        case Q2:
            if (input == 'i') {
                stack[(*top)++] = 'i'; // Empile 'i'
                return Q1;
            } else if (input == '(') {
                stack[(*top)++] = '('; // Empile '('
                return Q2;
            } else if (isdigit(input)) { // Utilisation de isdigit() pour vérifier si input est un chiffre
                stack[(*top)++] = input; // Empile le nombre
                return Q4;
            }
            break;
        case Q3:
            if (input == '$' && (*top == 0)) {
                return Q3; // Acceptation
            }
            break;
        case Q4:
            if (input == '+') {
                return Q0; // Retour à Q0 après avoir rencontré '+'
            } else if (input == '*') {
                return Q0; // Retour à Q0 après avoir rencontré '*'
            } else if (input == '$' && (*top == 0)) {
                return Q3; // Acceptation
            }
            break;
    }
    return Q3; // État final d'acceptation ou rejet
}
%}

%option noyywrap

%%
[0-9]+ {
    printf("Nombre : %s\n", yytext);
}

int {
    printf("Mot-clé 'int'\n");
}

"+" {
    printf("Opérateur '+'\n");
}

"*" {
    printf("Opérateur '*'\n");
}

"(" {
    printf("Parenthèse ouvrante '(' \n");
}

")" {
    printf("Parenthèse fermante ')' \n");
}

\$ {
    printf("Fin de l'expression\n");

    // Appel de l'automate à pile
    char stack[MAX_STACK_SIZE];
    int top = 0;
    State current_state = Q0;

    // Parcours des caractères de l'entrée Flex
    for (int i = 0; i < strlen(yytext); i++) {
        current_state = transition(current_state, yytext[i], stack, &top);
        if (current_state == Q3) {
            printf("Expression valide selon la grammaire.\n");
            return 0;
        }
    }

    printf("Expression invalide selon la grammaire.\n");
}

[ \t\n] {
    // Ignorer les espaces, tabulations et sauts de ligne
}

. {
    // Gestion des caractères non valides
    printf("Caractère non valide : %s\n", yytext);
}
%%

int main() {
    yylex();
    return 0;
}

/* Fonction d'erreur de Flex */
void yyerror(const char *s) {
    fprintf(stderr, "Erreur : %s\n", s);
}
