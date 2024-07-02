%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void); // Déclaration de yylex
void yyerror(char *s);
%}

%token INTEGER

%%
S: E { printf("\nRéduction S ----> E Fin!!!\n"); }
 ;

E: E '+' T { printf("\nRéduction E ----> E + T $1=%d\t$$=%d\n", $1, $$); }
 | T { printf("\nRéduction E ----> T $1=%d\t$$=%d\n", $1, $$); }
 ;

T: T '*' F { printf("\nRéduction T ----> T * F $1=%d\t$$=%d\n", $1, $$); }
 | F { printf("\nRéduction T ----> F $1=%d\t$$=%d\n", $1, $$); }
 ;

F: INTEGER { printf("\nRéduction F ----> int $1=%d\t$$=%d\n", $1, $$); }
 ;

%%

int main(void)
{
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "Erreur: %s\n", s);
}
