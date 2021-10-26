#include "Node.cpp"

using namespace std;

class ER2tree
{
  private:

    stack<char> Stack;
    stack<Node> StackT;

    bool isOperand(char op);
    int precedencia(char a, char b);                            // Devuelve -1 si a < b, 0 si a = b, y 1 si a > b.

  public:

    ER2tree()
    {}

    void infixToPostfix(string & result, string cadena);
    void makeTree(string postfix, Node & head);
    //void placeConcat(string & cadena);

};
