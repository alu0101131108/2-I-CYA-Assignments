#include "Node.hpp"
int Node::nodeCount()
{
  if(getLeft() == NULL && getRight() == NULL)       // Si es una hoja, devuelve 1.
    return 1;

  else if(getLeft() != NULL && getRight() == NULL)  // Si es un nodo unario, devuelve 1 + el numero de nodos por debajo de este, buscando solo por left.
    return getLeft() -> nodeCount() + 1;

  else if(getLeft() != NULL && getRight() != NULL)  // Si es un nodo binario, devuelve 1 + numero de nodos por debajo, buscando por left y right.
    return getLeft() -> nodeCount() + getRight() -> nodeCount() + 1;

  else                                              // Devuelve un error si un nodo tiene puntero right sin tener puntero left.
    cout << endl << "Node with right pointer and without left pointer." << endl;
}

void Node::print(ostream & os)
{
  if(getLeft() == NULL && getRight() == NULL)
  {
    os << data << endl;
  }
  else if(getLeft() != NULL && getRight() == NULL)
  {
    os << data << endl;
    os << "rama unaria:" << endl;
    getLeft() -> print(os);
    os << "fin rama unaria." << endl;
  }
  else if(getLeft() != NULL && getRight() != NULL)
  {
    os << data << endl;
    os << "rama izquierda:" << endl;
    getLeft() -> print(os);
    os << "fin rama izquierda." << endl;
    os << "rama derecha:" << endl;
    getRight() -> print(os);
    os << "fin rama derecha." << endl;
  }
}

void Node::getPrefix(string & result)
{
  if(getLeft() == NULL && getRight() == NULL)
  {
    result.push_back(data);
  }
  else if(getLeft() != NULL && getRight() == NULL)
  {
    result.push_back(data);
    getLeft() -> getPrefix(result);
  }
  else if(getLeft() != NULL && getRight() != NULL)
  {
    result.push_back(data);
    getLeft() -> getPrefix(result);
    getRight() -> getPrefix(result);
  }
}

/*
vector<string> infix = {"(a|b)*xz*", "a|b", "a|bc", "(a|b)(c|d)"};

ER2tree translator;
int ER_num = infix.size();                                            // Representa el número de expresiones regulares a analizar.

vector<string> prefix, postfix;                                       // Estos vectores contendrán las ER en notacion prefija y postfija.
postfix.resize(ER_num);
prefix.resize(ER_num);
vector<int> nodesOnTree;                                              // Este vector contendrá el número de nodos que conforman el arbol asociado a cada ER.
nodesOnTree.resize(ER_num);
vector<vector<Node>> treeNodes;                                       // Cada vector de nodos se utilizará para la creación del arbol asociado a cada ER.
treeNodes.resize(ER_num);                                             // El último elemento (nodo) de cada vector de nodos, representará al nodo padre del arbol asociado a cada ER.

for(int i = 0; i < ER_num; i++)                                       // Al final de este bucle se habrán rellenado los tres vectores recién creados.
{
  translator.infixToPostfix(postfix[i], infix[i]);                    // postfix[i] se rellena con infix[i] en notacion postfija.
  treeNodes[i].resize(postfix[i].size());                             // Se utiliza un vector de nodos, del mismo tamaño que postfix[i]. Este se reorganizará para
  translator.makeTree(postfix[i], treeNodes[i]);                      // formar el arbol asociado a postfix[i]. treeNodes[i][postfix[i].size()-1] será el nodo padre.
  nodesOnTree[i] = treeNodes[i][postfix[i].size() - 1].nodeCount();   // Se realiza el conteo de nodos que contiene el arbol asociado a postfix[i].
  treeNodes[i][postfix[i].size() - 1].getPrefix(prefix[i]);           // Apartir del arbol asociado a postfix[i], se obtiene la expresion en notacion prefija.
}
*/
