#include "DFA.cpp"
#include <string.h>

int main(int argc, char** argv)
{
  if(argc == 1)
		cout << "Pruebe './DFA2dot --help' para más información." << endl;
	else if(argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		cout << "DFA2dot lee la especificación de un autómata finito determinista, desde un archivo de entrada con extensión '.dfa'.\nA continuación genera un archivo de salida con extensión '.gv', donde se encontrará el código correspondiente al diagrama de transiciones del DFA especificado.\nEl modo de uso de este comando será:\n./DFA2dot 'nombre_entrada.dfa' 'nombre_salida.gv'" << endl; 
	}
	else
	{
		ifstream ifs;
 	  ifs.open(argv[1]);
	  DFA dfa1;
 	  dfa1.readFromFile(ifs);
 	  ifs.close();

    //dfa1.displayInfo(cout);

    ofstream ofs;
    ofs.open(argv[2]);
    dfa1.generateDotFile(ofs);
    ofs.close();
	}
  return 0;
}
