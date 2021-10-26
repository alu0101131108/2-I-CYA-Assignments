output: main.o
	g++ DFA2dot.o -o DFA2dot
main.o: DFA2dot.cpp DFA.cpp DFA.hpp Function.cpp Function.hpp
	g++ -c DFA2dot.cpp
clean:
	rm DFA2dot.o DFA2dot
