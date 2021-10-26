#include "lenguaje.cpp"
#include <algorithm>

using namespace std;

class Calculator
{
  private:
    vector<Language> operand;
    int operandCardinal;
    int code;
    int op_pot_exp;

  public:
    Calculator()
    {}
    Calculator(vector<Language> lang_vec, int code_): operand(lang_vec), code(code_), operandCardinal(lang_vec.size())
    {}

    void setExp(int exp)
    {
      op_pot_exp = exp;
    }

    Language op_concatenacion(Language a, Language b);    // CODE: 1
    Language op_union(Language a, Language b);            // CODE: 2
    Language op_interseccion(Language a, Language b);     // CODE: 3
    Language op_diferencia(Language a, Language b);       // CODE: 4
    bool     op_sublenguaje(Language a, Language b);      // CODE: 5
    bool     op_igualdad(Language a, Language b);         // CODE: 6
    Language op_inversa(Language a);                      // CODE: 7
    Language op_potencia(Language a, int exp);            // CODE: 8 (exp from argv)
    Language op_cierre_pos(Language a);                   // CODE: 9
    Language op_cierre_kleene(Language a);                // CODE: 10

    vector<Language> codeOperation();         // Rellenará un vector de lenguajes con los resultados de la operacion code.
    vector<bool> codeOperation_bool();        // Rellenará un vector de bool para las operaciones sublenguaje e igualdad.
};
