#include "Grammar.cpp"

int main(int argc, char** argv)
{
  if(argc == 1)
  {
    cout << "Modo de empleo: ./G2NFA input.gra output.nfa" << endl;
    cout << "Pruebe ‘G2NFA --help’ para más información." << endl;
  }
  else if(argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    cout << "G2NFA lee un fichero de texto en el que figura la especificacion de una Gramática Regular lineal por" << endl;
    cout << "la derecha, G y genera un fichero .nfa con la especificacion de un NFA M, tal que L(G) = L(M)." << endl;
  }
  else if(argc == 3)
  {
    Grammar gramatica1(argv[1]);
    Nfa nfa1 = gramatica1.convertToNFA();
    nfa1.exportToFile(argv[2]);
  }
  else
  {
    cout << "El número de parámetros excede el permitido." << endl;
  }

  return 0;
}
