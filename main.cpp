#include <iostream>
#include <stdio.h>
#include "parser.tab.hpp"
#include "ast.hpp"

static void usage(const char * progname){
    std::cerr << "Usage: " << progname << " <filename>" << std::endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char ** argv){
    if (argc < 2) {
        usage(argv[0]);
    }

    FILE* fd = fopen(argv[1], "r"); // filename is the first argument

    if (fd == NULL) {
        std::cerr << "Error: cannot open file '" << argv[1] << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set the file as yyin
    yyin = fd;
    yyparse();

    ASTNode* res = buildAST();
    dotAST(res, 0);

    return 0;
}
