BUILD=build
BIN=bin

CXX = g++
CXXFLAGS = -g --std=c++20 

sic: lexer parser graph
	$(CXX) $(CXXFLAGS) -c parser.tab.cpp -o $(BUILD)/parser.o
	gcc -g -c lex.yy.c -o $(BUILD)/lex.o
	$(CXX) $(CXXFLAGS) $(BUILD)/lex.o $(BUILD)/parser.o ast.cpp main.cpp -o $(BIN)/sic

lexer: lexer.l
	flex lexer.l

parser: parser.ypp
	bison -d parser.ypp 

graph: parser.ypp
	bison -d parser.ypp --graph -o $(BUILD)/parser.gv
	dot -Tsvg $(BUILD)/parser.gv -o states.svg
	rm $(BUILD)/parser.gv

clean:
	rm -f sic lex.yy.c parser.tab.cpp parser.tab.hpp

open_graph: 
	open file:///./states.svg &
