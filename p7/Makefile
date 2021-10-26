output: NFA2DFA.o
	g++ NFA2DFA.o -o NFA2DFA
NFA2DFA.o: NFA2DFA.cpp DFA.cpp DFA.hpp NFA.cpp NFA.hpp FunctionDFA.cpp FunctionDFA.hpp FunctionNFA.cpp FunctionNFA.hpp
	g++ -c NFA2DFA.cpp
clean:
	rm NFA2DFA.o NFA2DFA
