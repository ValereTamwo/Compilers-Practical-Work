#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef enum {
    Q0, Q1, Q2
} State;

State transition(State current_state, char input, char *stack, int *top) {
    switch (current_state) {
        case Q0:
            if (input == 'a') {
                stack[(*top)++] = 'a'; // Empile 'a'
                return Q1;
            } else if (input == '$' && (*top == 0)) {
                return Q2; // Acceptation
            }
            break;
        case Q1:
            if (input == 'a') {
                stack[(*top)++] = 'a'; // Empile 'a'
                return Q1;
            } else if (input == 'b' && (*top > 0 && stack[*top - 1] == 'a')) {
                (*top)--; // Dépile 'a'
                return Q1;
            } else if (input == '$' && (*top == 0)) {
                return Q2; // Acceptation
            }
            break;
    }
    return Q2; // État final d'acceptation ou rejet
}

int main() {
    char input[MAX_STACK_SIZE]; // Pour stocker l'entrée provenant de Flex
    char stack[MAX_STACK_SIZE];
    int top = 0;
    State current_state = Q0;

    // Lecture de l'entrée depuis Flex
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Erreur lors de la lecture de l'entrée\n");
        return 1;
    }

    // Suppression du caractère de nouvelle ligne de l'entrée si présent
    input[strcspn(input, "\n")] = '\0';

    // Parcours des caractères de l'entrée
    for (int i = 0; i < strlen(input); i++) {
        current_state = transition(current_state, input[i], stack, &top);
        if (current_state == Q2) {
            printf("Mot valide\n");
            return 0;
        }
    }

    printf("Mot invalide\n");
    return 0;
}
