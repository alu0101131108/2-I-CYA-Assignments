output: G2NFA.o
	g++ G2NFA.o -o G2NFA
NFA2DFA.o: G2NFA.cpp Grammar.hpp Grammar.cpp NTSymbol.hpp NTSymbol.cpp NFA.hpp NFA.cpp State.hpp State.cpp
	g++ -c G2NFA.cpp
clean:
	rm G2NFA.o G2NFA
