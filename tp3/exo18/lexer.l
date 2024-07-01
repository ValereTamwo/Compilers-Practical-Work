%{
#include <stdlib.h>
#include "parser.tab.h"

%}

%%
[0-9]+       { yylval = atoi(yytext); return INTEGER; }
[a-dA-D]     { yylval = yytext[0]; return VARIABLE; }
"print"      { return PRINT; }
"+"          { return '+'; }
"*"          { return '*'; }
"="          { return '='; }
"/"          { return '/'; }
";"          { return ';'; }
[ \t]        { /* Ignorer les espaces blancs */ }
\n           { /* Ignorer les nouvelles lignes */ }
.            { fprintf(stderr, "Caractère inattendu: %s\n", yytext); exit(1); }
%%

int yywrap(void) {
    return 1;
}
