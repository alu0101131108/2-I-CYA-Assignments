output: G2CNF.o
	g++ G2CNF.o -o G2CNF
G2CNF.o: G2CNF.cpp Grammar.hpp Grammar.cpp NTSymbol.hpp NTSymbol.cpp
	g++ -c G2CNF.cpp
clean:
	rm G2CNF.o G2CNF
