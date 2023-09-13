
%{
#include <stdio.h>
extern int yylex();
void yyerror(char* s);

%}

%union {
    int integer; // Define YYSTYPE as an integer
}

%token ADD SUB MUL DIV LPAREN RPAREN NUMBER
%left ADD SUB
%left MUL DIV

%type <integer> expression term factor program NUMBER

%%

program : expression { fprintf(stdout, "%d\n", $1); }
        ;

expression : term { $$ = $1; }
           | expression ADD term { $$ = $1 + $3; }
           | expression SUB term { $$ = $1 - $3; }
           ;

term : factor { $$ = $1; }
     | term MUL factor { $$ = $1 * $3; }
     | term DIV factor { $$ = $1 / $3; }
     ;

factor : NUMBER { $$ = $1; }
       | LPAREN expression RPAREN { $$ = $2; }
       ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(char* s){
    fprintf(stderr, "Error %s\n", s);
}