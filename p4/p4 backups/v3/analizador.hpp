#include "dfa.cpp"

using namespace std;

class Analizador
{
  private:

    DFA dfa;

  public:

    Analizador(DFA dfa_):
    dfa(dfa_)
    {}

    bool checkSyntax(string aux_str);               // Revisa que no haya un comentario no cerrado, o algún caso no contemplado.
    void borrarComentarios(string & aux_str);       // Edita el string pasado por parametros, eliminando los comentarios.
};
