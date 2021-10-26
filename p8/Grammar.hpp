#include "Nfa.cpp"
#include "NTSymbol.cpp"

using namespace std;

/** Servirá para representar Gramáticas.
* Una Gramática G puede representarse de la forma G ≡ (V, Σ, S, P). Donde
* V es el conjunto de símbolos no terminales, Σ es el conjunto de símbolos
* terminales, S es el símbolo de arranque y P es el conjunto de producciones.
* Esta clase contendrá los tres primeros elementos de la tupla como atributos
* y el conjunto de producciones será almacenado por los mismos símbolos no
* terminales, donde cada uno almacenará las producciones asociadas a sí mismo.
*/
class Grammar
{
  private:
    set<string> alphabet;          /**< Conjunto de símbolos terminales Σ. */
    vector<NTSymbol> NTSymbols;    /**< Conjunto de símbolos no terminales V. */
    string init_NTSymbol_ID;       /**< Símbolo de arranque S. */
    string void_label = "~";       /**< Etiqueta para representar las ε-transiciones. */

    bool belong(string id, vector<NTSymbol> container);   /**< Método auxiliar para saber si el NTSymbol con identificador id, pertenece al vector de NTSymbols */
    string setToString(set<string> container);            /**< Método auxiliar que traduce un conjunto en un string con los elementos que lo conforman. */
    int getIndex(string id, vector<State> container);     /**< Devuelve el índice en el vector de simbolos no terminales que corresponde al NTSymbol cuyo identificador coincide con el string pasado por parámetro. */


  public:
    Grammar()
    {}
    Grammar(string filename)  /**< Constructor apartir de un archivo de texto donde figura la especificación de una gramática. */
    {
      importFromFile(filename);
    }

    /** Construye un NFA M apartir de la gramática invocante donde L(M) = L(gramatica invocante).
    * El algoritmo de construcción del NFA sigue los siguientes pasos:
    * - El alfabeto será equivalente al conjunto de simbolos terminales.
    * - El estado inicial será equivalente al simbolo no terminal de arranque.
    * Se inicia creando tantos estados como símbolos no temrinales tenga la gramática.
    * A continuación, se analizará cada una de las producciones de cada símbolo no terminal.
    * - Por cada produccion se crearán una serie de estados nuevos auxiliares.
    * Si en la producción solo hay símbolos terminales, se crearán n estados auxiliares donde n es el numero de simbolos terminales de la producción.
    *   Las transiciones irán desde el estado asociado al simbolo inicial de la producción hasta el primer estado auxiliar, con el primer simbolo terminal de la producción.
    *   Al último estado de esta serie de estados auxiliares se transitará con el último símbolo terminal de la producción, y este estado será incluido a los estados de aceptación.
    * Si en la producción hay un simbolo terminal y un no terminal, no se crearán estados auxiliares.
    *   Se añadirá la transición desde el estado asociado al simbolo no terminal inicial al estado asociado al simbolo no terminal final, al recibir el símbolo terminal de la producción.
    * Si en la producción hay una cadena de simbolos terminales seguidos de un simbolo no terminal, se crearán n-1 estados auxiliares, donde n es el número de simbolos terminales en la producción.
    *   El proceso será parecido al primer caso con la diferencia de que la última transición apuntará al estado asociado al simbolo no terminal final de la producción y este no será de aceptación.
    */
    Nfa convertToNFA();
    void importFromFile(string filename); /**< Da valor a los atributos apartir del archivo de nombre filename donde figura la especificación de una gramática. */
    void print(ostream & os);  /**< Muestra por consola la información relacionada con la gramática */

};
