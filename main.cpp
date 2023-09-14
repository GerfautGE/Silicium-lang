#include <iostream>
#include <stdio.h>

extern "C" int parse(FILE* fd);

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

    parse(fd);

    return 0;
}
