#include "State.cpp"

using namespace std;

/** Servirá para representar un autómata finito no determinista (NFA).
* Un NFA M puede representarse a través de la tupla M ≡ (Q, Σ, δ, q0, F). Donde
* Q es el conjunto de estados, Σ es el alfabeto, δ es la función de transición,
* q0 es el estado inicial y F es el conjunto de estados finales. En este caso los
* NFAs tendrán un alfabeto, un conjunto de estados, un estado inicial y un conjunto
* de estados finales. La función de transición se reparte entre todos los estados,
* dado que cada uno almacena sus propias transiciones.
*/
class Nfa
{
  private:
    set<string>     alphabet;               /**< Alfabeto Σ. */
    vector<State>   states;                 /**< Conjunto de estados Q. */
    string          init_state_ID;          /**< Estado inicial q0. */
    set<string>     final_state_IDs;        /**< Estados finales o de aceptación F. */
    string          void_label = "~";       /**< Etiqueta para representar las ε-transiciones. */

    string setToString(set<string> container);  /**< Método auxiliar que traduce un conjunto en un string con los elementos que lo conforman. */


  public:
    Nfa()
    {}

    int getStateIndex(string id);                 /**< Devuelve el índice en el vector de estados que tiene el estado cuyo identificador coincide con el string pasado por parámetro. */
    void setInitStateId(string id);               /**< Establece el estado inicial al pasado por parámetro. */
    void setAlphabet(set<string> in_alphabet);    /**< Establece el alfabeto al pasado por parámetro */
    void setVoidLabel(string label);              /**< Establece la etiqueta para una ε-transicion a la pasada por parámetro. */
    void addNewState(string id);                  /**< Añade un nuevo estado al vector de estados. */
    void addStates(vector<State> input_states);   /**< Establece el vector de estados al pasado por parámetro. */
    void addFinalState(string id);                /**< Incluye el estado pasado por parámetro en el conjunto de estados finales */
    void print(ostream & os);                     /**< Muestra la información relacionada con el NFA por consola */

    /** Genera una especificación del NFA y la guarda en el archivo cuyo nombre se pasa por parámetro.
    * \param filename nombre del archivo.
    * La especificación sigue el formato propuesto en el pdf de la práctica 8. Se recomienda que el archivo tenga extensión '.nfa'.
    */
    void exportToFile(string filename);

};
