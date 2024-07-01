%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h" // Inclure le fichier d'en-tête généré par Bison

void yyerror(const char *s);
int yylex(void);

int variables[256]; // Tableau pour stocker les valeurs des variables
%}

%token INTEGER VARIABLE PRINT

%left '+' '-'
%left '*' '/'

%%

S: Stmts { printf("\nProgramme exécuté avec succès\n"); }
 ;

Stmts: Stmt ';' Stmts
     | Stmt ';'
     | Stmt '\n' Stmts
     | Stmt '\n'
     ;

Stmt: VARIABLE '=' E { variables[$1] = $3; printf("Affectation: %c = %d\n", $1, $3); }
    | PRINT VARIABLE { printf("Valeur de %c: %d\n", $2, variables[$2]); }
    ;

E: E '+' T { $$ = $1 + $3; }
 | E '-' T { $$ = $1 - $3; }
 | T { $$ = $1; }
 ;

T: T '*' F { $$ = $1 * $3; }
 | T '/' F { $$ = $1 / $3; }
 | F { $$ = $1; }
 ;

F: INTEGER { $$ = $1; }
 | VARIABLE { $$ = variables[$1]; }
 ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "error: %s\n", s);
}

int main(void) {
    // Initialiser les variables prédéfinies à zéro
    for (int i = 0; i < 256; i++) {
        variables[i] = 0;
    }

    // Appeler l'analyseur
    yyparse();

    return 0;
}
