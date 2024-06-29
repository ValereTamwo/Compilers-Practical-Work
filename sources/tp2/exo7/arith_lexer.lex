%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(EXIT_FAILURE);
}
%}

digit [0-9]
entier {digit}{digit}+
operateur \+|\*

%%
{entier}    { printf("<int:%s>", yytext); }
{operateur} { printf("<operateur:%s>", yytext); }
.           { yyerror("Invalid character"); }
\n          { /* Ignore new lines */ }
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Unable to open file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    printf("\n");
    return 0;
}
