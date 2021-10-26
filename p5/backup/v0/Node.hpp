#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class Node
{
  private:

    char data;
    Node* left;
    Node* right;

  public:

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

    int nodeCount();  // Funcion recursiva. Devuelve el numero de nodos que tiene por debajo el nodo invocante.
    void print(ostream & os);
};
