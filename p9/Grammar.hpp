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
    string init_NTSymbol_ID;       /**< ID del símbolo de arranque S. */
    string void_label = "~";       /**< Etiqueta para representar las ε-transiciones. */

    bool isNTSymbol(string id);                           /**< Método auxiliar para saber si el NTSymbol con identificador id, pertenece al vector de NTSymbols */
    bool isNTSymbolFrom(string id, vector<NTSymbol> container);
    bool isTSymbol(string id);                            /**< Método auxiliar para saber si el string id pertenece al conjunto de simbolos terminales */
    string setToString(set<string> container);            /**< Método auxiliar que traduce un conjunto en un string con los elementos que lo conforman. */
    vector<string> splitProduction(string mixed_prod);    /**< Método auxiliar que separa la parte derecha de una producción distinguiendo tsymbols de ntsymbols. */


  public:
    Grammar()
    {}
    Grammar(string filename)                            /**< Constructor apartir de un archivo de texto donde figura la especificación de una gramática. */
    {
      importFromFile(filename);
    }

    int countProductions();
    void setAlphabet(set<string> new_alphabet);
    void setNTSymbols(vector<NTSymbol> new_NTSymbols);
    void setInitNTSymbolID(string new_initID);
    void setVoidLabel(string new_void_label);
    void importFromFile(string filename);               /**< Da valor a los atributos apartir del archivo de nombre filename donde figura la especificación de una gramática. */
    void print(ostream & os);                           /**< Muestra por consola la información relacionada con la gramática. */
    Grammar saveAsCNF();                                /**< Devuelve una gramática equivalente pero expresada en la Forma Normal de Chomsky. */
    void exportToFile(string filename);                 /**< Vuelca la especificación de la gramática en un archivo de texto de salida. */
};
