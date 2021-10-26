output: main.o
	g++ main.o -o exe
main.o: main.cpp calculadora.cpp calculadora.hpp lector.cpp lector.hpp lenguaje.cpp lenguaje.hpp
	g++ -c main.cpp
clean:
	rm main.o exe
