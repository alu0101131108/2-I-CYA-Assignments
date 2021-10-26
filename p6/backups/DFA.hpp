#include "Function.cpp"

using namespace std;

class DFA
{
  private:

    set<string>     Alphabet;         // Alfabeto Σ.
    set<string>     Q;                // Conjunto de estados.
    string          Qo;               // Estado inicial.
    set<string>     F;                // Estados finales o de aceptación.
    Function        Transition;       // Describirá δ.

    bool belong(string element, set<string> container);
    bool syntaxOk(string aux);

  public:

    DFA()
    {}

    void readFromFile(ifstream & in);
    void displayInfo(ostream & out);
};
