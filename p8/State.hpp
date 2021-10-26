#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <sstream>
#include <cassert>
#include <string.h>

using namespace std;

/** Servirá para representar los estados de un NFA.
* Contendrá un identificador de tipo string y un vector de transiciones.
* Las transiciones son pares tipo <string, string>, donde el segundo elemento
* representa el identificador del estado al que transita el NFA al recibir
* el simbolo almacenado en el primer elemento.
*/

class State
{
  typedef pair<string, string> transition;

  private:
    string              id;           /**< Identificador o nombre del estado. */
    vector<transition>  transitions;  /**< Conjunto de transiciones asociadas al estado. */

  public:
    State(string name): id(name)
    {}

    vector<transition> getTransitions();                      /**< Devuelve el vector de transiciones asociadas al estado. */
    string getId();                                           /**< Devuelve el identificador asociado al estado. */

    /** Añade una transición al estado.
    * Se crea el par<string, string> con el símbolo de entrada y con el identificador del estado al que transita.
    * Una vez creado, se añade al vector de transiciones asociadas al estado.
    */
    void addTransition(string in_symbol, string next_state);
    
    /** Permite visualizar por consola la información del estado.
    * Se mostrará el identificador seguido de todas sus transiciones de la forma simbolo_entrada -> estado_final.
    */
    void print(ostream & os);

};
