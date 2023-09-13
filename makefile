sic: lexer parser
	gcc -c parser.tab.c -o parser.o
	gcc -c lex.yy.c -o lex.o
	gcc lex.o parser.o -o sic

lexer: lexer.l
	flex  lexer.l

parser: parser.y
	bison -d parser.y

clean:
	rm -f sic lex.yy.c parser.tab.c parser.tab.h
