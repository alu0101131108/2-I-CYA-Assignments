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
