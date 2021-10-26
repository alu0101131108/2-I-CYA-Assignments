#include "FunctionNFA.cpp"

using namespace std;

class NFA
{
  private:

    set<string>     Alphabet;         // Alfabeto Σ.
    set<string>     Q;                // Conjunto de estados.
    string          Qo;               // Estado inicial.
    set<string>     F;                // Estados finales o de aceptación.
    FunctionNFA     Transition;       // Describirá δ.
    string          epsilon_label;    // Etiqueta para representar las ε-transiciones.

    bool belong(string element, set<string> container);
    bool syntaxOk(string aux);
    string finalStatesToString();
    string deadStatesToString();
    vector<string> nameVectorElements(set<set<string>> elements, vector<set<string>> & unnamed_vector);

  public:

    NFA()
    {}

    void readFromFile(ifstream & ifs);
    void displayInfo(ostream & out);
    void generateDotFile(ofstream & ofs);
    set<string> eclausura(set<string> T);
    set<string> move(set<string> S, string a);
    void generateDFAfromSubsetAlgorithm(ofstream & ofs);
    string setToString(set<string> container);
};
