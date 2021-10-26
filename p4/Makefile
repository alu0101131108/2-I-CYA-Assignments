output: main.o
	g++ main.o -o exe
main.o: main.cpp fileIO.cpp fileIO.hpp analizador.cpp analizador.hpp dfa.cpp dfa.hpp tabla.cpp tabla.hpp
	g++ -c main.cpp
clean:
	rm main.o exe
