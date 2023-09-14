
%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern FILE* yyin;
void yyerror(char* s);

%}

%union {
    int integer; // Define YYSTYPE as an integer
    char* string;
}

%token FN;
%token IDENTIFIER;
%token ARROW;
%token RET

%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token COMMA
%token SEMICOLON

%token NUMBER
%type <integer> NUMBER
%type <string> IDENTIFIER


%%

program : FUNDEFS

FUNDEFS:        FUNDEF FUNDEFS
                | FUNDEF

FUNDEF:         FN IDENTIFIER LPAREN PARAMS RPAREN ARROW LBRACE instrs RBRACE {printf("fundef %s\n", $2);}

PARAMS:         PARAM 
                | PARAM COMMA PARAMS

PARAM:          %empty | IDENTIFIER

instrs:         instr | instr instrs

instr:          RET expr SEMICOLON
                | expr

expr:           NUMBER


    
%%

int parse(FILE* fd) {
    yyin = fd;
    yyparse();
    return 0;
}

void yyerror(char* s){
    fprintf(stderr, "Error %s\n", s);
}
