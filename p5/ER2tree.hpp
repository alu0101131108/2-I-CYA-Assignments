#include "Node.cpp"

using namespace std;

class ER2tree
{
  private:

    stack<char> Stack;
    stack<Node*> StackT;

    bool isOperand(char op);                              // Devuelve un bool que ndica si op es un operando.
    int precedencia(char a, char b);                      // Devuelve -1 si a < b, 0 si a = b, y 1 si a > b.

  public:

    ER2tree()
    {}

    void infixToPostfix(string & result, string cadena);  // Traduce cadena (expresion regular notacion infija)
                                                          // a notacion postfija y lo almacena en result.
    void makeTree(string postfix, vector<Node> & v);      // Crea el arbol asociado a la ER postfix. Los nodos se
                                                          // almacenarán en v y el nodo padre será el último elemento.
    void placeConcat(string & cadena);                    // Detecta las concatenaciones implícitas de una ER e
                                                          // inserta el simbolo '&'.

};
