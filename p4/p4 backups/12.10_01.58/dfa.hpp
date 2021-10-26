#include "tabla.cpp"

using namespace std;

class DFA
{
  private:
                                  // El alfabeto Σ serán todos los char aceptados por c++.
    set<int>    Q;                // Conjunto de estados.
    int         Qo;               // Estado inicial. Tambien servirá para almacenar el estado en el que se encuentre el dfa.
    set<int>    F;                // Estados finales o de aceptación.
    Tabla       transicion;       // Describirá δ. Tabla[i][j] será el estado al que cambiará
                                  // el dfa si se encuentra en el estado [i] y recibe el caracter [j].
  public:

    DFA(set<int> Q_, int Qo_, set<int> F_, Tabla transicion_):
    Q(Q_), Qo(Qo_), F(F_), transicion(transicion_)
    {
      assert(!Q.empty() && !F.empty());
    }

    int getEstado()
    {
      return Qo;
    }

    void evento(char in);
};
