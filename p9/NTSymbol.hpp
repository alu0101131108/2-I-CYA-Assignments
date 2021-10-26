#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <cassert>
#include <sstream>
#include <string.h>

using namespace std;

const string PROD_LABEL = "->";

/** Servirá para representar los símbolos no terminales de una gramática.
* Contendrá un identificador de tipo string y un vector de producciones.
* Las producciones a su vez serán vectores de string que podrán contener un
* símbolo terminal ó el identificador de un símbolo no terminal.
*/
class NTSymbol
{
  typedef vector<string> production;

  private:
    string              id;                           /**< Identificador del símbolo no terminal. */
    vector<production>  productions;                  /**< Conjunto de producciones asociadas al símbolo no terminal. */

    string vectorToString(vector<string> container);  /**< Método auxiliar que permite traducir un vector en una cadena de texto que contiene los identificadores de los elementos del vector. */

  public:
    NTSymbol(string name): id(name)
    {}

    void prodSymbolReplace(string old_symbol, string new_symbol);
    string getId();                                                       /**< Devuelve el identificador del símbolo no terminal. */
    void setId(string name);                                              /**< Establece el identificador al string pasado por parámetro. */
    vector<production> getProductions();                                  /**< Devuelve el vector de producciones. */
    void defineProduction(vector<string> symbols);                        /**< Añade una producción al vector de producciones asociadas al símbolo no terminal. */
    void defineDualProduction(string symb1, string symb2);                        /**< Añade una producción al vector de producciones asociadas al símbolo no terminal. */
    void print(ostream & os);                                             /**< Muestra la información asociada al símbolo no terminal por consola. */
    void setProductionAt(vector<string> newprod, int index);
    void setDualProductionAt(string symb1, string symb2, int index);
    int countProductions();

};
