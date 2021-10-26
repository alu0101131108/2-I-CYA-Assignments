#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

using namespace std;


const string PROD_LABEL = "->";

/** Servirá para representar los símbolos no terminales de una gramática.
* Contendrá un identificador de tipo string y un vector de producciones.
* Las producciones son pares tipo <vector<string>, string>, donde al recibir
* cualquier simbolo terminal que forme parte del primer elemento, se producirá
* un salto al símbolo no terminal cuyo identificador está en el segundo
* elemento del par.
*/
class NTSymbol
{
  typedef pair<vector<string>, string> production;

  private:
    string              id;                           /**< Identificador del símbolo no terminal. */
    vector<production>  productions;                  /**< Conjunto de producciones asociadas al símbolo no terminal. */

    string vectorToString(vector<string> container);  /**< Método auxiliar que permite traducir un vector en una cadena de texto que contiene los identificadores de los elementos del vector. */

  public:
    NTSymbol(string name): id(name)
    {}

    string getId();                                                       /**< Devuelve el identificador del símbolo no terminal. */
    void setId(string name);                                              /**< Establece el identificador al string pasado por parámetro. */
    vector<production> getProductions();                                  /**< Devuelve el vector de producciones. */
    void defineProduction(vector<string> in_symbols, string final_ntsID); /**< Añade una producción al vector de producciones asociadas al símbolo no terminal. */
    void print(ostream & os);                                             /**< Muestra la información asociada al símbolo no terminal por consola. */



};
