#include "Grammar.cpp"

int main(int argc, char** argv)
{
  if (argc == 1)
  {
    cout << "Modo de empleo: ./G2CNF input.gra output.gra" << endl;
    cout << "Pruebe ‘G2CNF --help’ para más información." << endl;
  }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    cout << "G2CNF lee un fichero de texto en el que figura la especificación de una Gramática Independiente del Contexto " << endl;
    cout << "y genera otro fichero de texto en el que se especifica una gramática equivalente [L(Gin) = L(Gout)] a la de " << endl;
    cout << "entrada, escrita en Forma Normal de Chomsky." << endl;
    cout << "Cabe destacar que la gramática de entrada no debe contener símbolos ni producciones inutiles, unitarias ni vacías." << endl;
  }
  else if (argc == 3)
  {
    Grammar graCFG(argv[1]);
    // graCFG.print(cout);
    Grammar graCNF = graCFG.saveAsCNF();
    //graCNF.print(cout);
    graCNF.exportToFile(argv[2]);
  }
  else
  {
    cout << "El número de parámetros excede el permitido." << endl;
  }

  return 0;
}
