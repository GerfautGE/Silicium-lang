BUILD=build
BIN=bin

sic: lexer parser graph
	gcc -g -c parser.tab.c -o $(BUILD)/parser.o
	gcc -g -c lex.yy.c -o $(BUILD)/lex.o
	g++ -g $(BUILD)/lex.o $(BUILD)/parser.o main.cpp -o $(BIN)/sic

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d parser.y 

graph: parser.y
	bison -d parser.y --graph -o $(BUILD)/parser.gv
	dot -Tsvg $(BUILD)/parser.gv -o states.svg
	rm $(BUILD)/parser.gv

clean:
	rm -f sic lex.yy.c parser.tab.c parser.tab.h

open_graph: 
	chromium file:///home/gerfaut/Documents/Projets/Silicium-lang/states.svg &
