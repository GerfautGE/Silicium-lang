sic: lexer.l parser.y
	flex lexer.l
	bison -d parser.y
	g++ -o sic lex.yy.c parser.tab.c -lfl

clean:
	rm -f sic lex.yy.c parser.tab.c parser.tab.h
