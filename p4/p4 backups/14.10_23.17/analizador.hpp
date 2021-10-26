#include "dfa.cpp"

using namespace std;

class Analizador
{
  private:

    DFA dfa;
    string text;

  public:

    Analizador(DFA dfa_, string text_):
    dfa(dfa_), text(text_)
    {}

    void borrarComentarios(string & aux_str);
};
