#include "State.cpp"

using namespace std;

class Nfa
{
  private:
    set<string>     alphabet;               /**< Alfabeto Σ. */
    set<State>      state_set;              /**< Conjunto de estados. */
    State           init_state;             /**< Estado inicial. */
    set<State>      final_state;            /**< Estados finales o de aceptación. */
    string          void_label = "~";    /**< Etiqueta para representar las ε-transiciones. */

  public:
    Nfa()
    {}


};
