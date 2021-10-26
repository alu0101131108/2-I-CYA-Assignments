#include <stack>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
  private:

    char data;
    Node* left;
    Node* right;

  public:

    Node(): left(NULL), right(NULL), data('$')
    {}
    Node(char data_): left(NULL), right(NULL), data(data_)
    {}
    Node(char data_, Node* unary): left(unary), right(NULL), data(data_)
    {}
    Node(char data_, Node* left_, Node* right_): left(left_), right(right_), data(data_)
    {}
    Node(char data_, Node unary): data(data_)
    {
      Node* aux1 = & unary;
      left = aux1;
      right = NULL;
    }
    Node(char data_, Node left_, Node right_): data(data_)
    {
      Node* aux1 = & left_;
      Node* aux2 = & right_;
      left = aux1;
      right = aux2;
    }
    char getData()
    {
      return data;
    }
    Node* getLeft()
    {
      return left;
    }
    Node* getRight()
    {
      return right;
    }
    void setData(char data_)
    {
      data = data_;
    }
    void setLeft(Node* left_)
    {
      left = left_;
    }
    void setRight(Node* right_)
    {
      right = right_;
    }
    void setLeft(Node left_)
    {
      Node* aux = & left_;
      left = aux;
    }
    void setRight(Node right_)
    {
      Node* aux = &  right_;
      right = aux;
    }
    void clear()
    {
      data = '$';
      left = NULL;
      right = NULL;
    }
    void copy(Node* copy)
    {
      data = copy -> getData();
      left = copy -> getLeft();
      right = copy -> getRight();
    }

    int nodeCount();          // Funcion recursiva. Recorre el arbol y devuelve su numero de nodos.
    void print(ostream & os); // Funcion recursiva. Recorre el arbol (DFS) e imprime una traza de este.
    void getPrefix(string & result);
};
