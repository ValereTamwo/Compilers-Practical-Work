%{
#include "parser.tab.h" 
%}

%%

[0-9]+  { yylval = atoi(yytext); return INTEGER; }
[ \t\n] { /* Ignorer les espaces blancs */ }
.       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
