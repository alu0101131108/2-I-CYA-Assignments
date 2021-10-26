#include "ER2tree.hpp"
void ER2tree::infixToPostfix(string & result, string cadena)
{
  Stack.push('$');
  char x;
  for(int i = 0; i < cadena.size(); i++)
  {
    x = cadena[i];

    if(isOperand(x))  // Si x es un operador.
      result.push_back(x);

    else if(x == '(') // Si x es un paréntesis abierto.
      Stack.push(x);

    else if(x == ')') // Si x es un paréntesis cerrado. Se vacía la pila hasta encontrar un '('.
    {
      while(Stack.top() != '$' && Stack.top() != '(')
      {
        result.push_back(Stack.top());
        Stack.pop();
      }
      if(Stack.top() == '(')
      {
        Stack.pop();
      }
    }
    else              // Si x es un operador.
    {
      while(Stack.top() != '$' && precedencia(x, Stack.top()) < 1)  // Mientras la pila no esté vacia y la precedencia de x sea menor a la del Stack.top().
      {
        result.push_back(Stack.top());
        Stack.pop();
      }
      Stack.push(x);
    }
  }
  while(Stack.top() != '$')   // Se vacían los operadores que quedan en la pila.
  {
    result.push_back(Stack.top());
    Stack.pop();
  }
}

bool ER2tree::isOperand(char op)
{
  if((op >= 'a' && op <= 'z') || (op >= 'A' && op <= 'Z'))
    return true;
  else
    return false;
}

int ER2tree::precedencia(char a, char b)       // * > & > |
{
  if((a == '*' || a == '&' || a == '|') && (b == '*' || b == '&' || b == '|'))
  {
    if(a == b)
      return 0;
    else
    {
      if(a == '*')
        return 1;
      else if(a == '&')
      {
        if(b == '*')
          return -1;
        else
          return 1;
      }
      else
        return -1;
    }
  }
  else
    return 10;      // Cuando se compara con un paréntesis.
}

void ER2tree::makeTree(string postfix, Node & head)
{
  char x;
  Node aux_node('$');
  Node aux_node1('$');
  Node aux_node2('$');

  for (int i = 0; i < postfix.size(); i++)
  {
    x = postfix[i];
    if(isOperand(x))
    {
      aux_node.clear();
      aux_node.setData(x);
      StackT.push(aux_node);
    }
    else
    {
      if(x == '*')
      {
        aux_node.clear();
        aux_node1.clear();
        aux_node1 = StackT.top();
        StackT.pop();
        aux_node.setData(x);
        aux_node.setLeft(aux_node1);
        StackT.push(aux_node);
      }
      else
      {
        aux_node.clear();
        aux_node1.clear();
        aux_node2.clear();
        aux_node1 = StackT.top();
        StackT.pop();
        aux_node2 = StackT.top();
        StackT.pop();
        aux_node.setData(x);
        aux_node.setLeft(aux_node2);
        aux_node.setRight(aux_node1);
        StackT.push(aux_node);
      }
    }
  }

  head = StackT.top();
}

/*void Traductor::placeConcat(string & cadena)
{
  string aux;
  char x;
  aux.push_back(cadena[0]);
  for(int i = 1; i < cadena.size(); i++)
  {
    x = cadena[i];
    if(x = )
  }
}*/
