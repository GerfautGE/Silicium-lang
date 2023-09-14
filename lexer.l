
%{
#include "parser.tab.h"
%}

%option noyywrap

%%

[[:space:]]                 {/* remove blanks */}

"fn"                        { return FN; }
"->"                        { return ARROW; }
"ret"                       { return RET; }

"("                         { return LPAREN; }
")"                         { return RPAREN; }
","                         { return COMMA; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }
";"                         { return SEMICOLON; }


[[:alpha:]_][[:alnum:]_]*    {yylval.string = strdup(yytext); return IDENTIFIER;}
[0-9]+                      { yylval.integer = atoi(yytext); return NUMBER; 
}
.                           { /* handle error */ }

%%