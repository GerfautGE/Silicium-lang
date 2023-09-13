
%{
#include "parser.tab.h"
%}

%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"("     { return LPAREN; }
")"     { return RPAREN; }
[0-9]+  { yylval.integer = atoi(yytext); return NUMBER; }
[ \t\n] { /* ignore whitespace and newline */ }
.       { /* handle error */ }

%%

int yywrap(void) {
    return 1;
}
