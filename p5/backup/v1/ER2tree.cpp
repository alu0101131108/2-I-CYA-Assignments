#include "ER2tree.hpp"
void ER2tree::infixToPostfix(string & result, string cadena)
{
  placeConcat(cadena);
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

int ER2tree::precedencia(char a, char b)    // * > & > |
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

void ER2tree::makeTree(string postfix, vector<Node> & v)
{
  char x;
  Node* node_pointer;
  vector<Node*> vp(postfix.size(), node_pointer);
/*este es el puto problema coño.
  char x;
  v.resize(postfix.size());
  Node* node_pointer;
  vector<Node*> vp(postfix.size(), node_pointer);
*/
  for (int i = 0; i < postfix.size(); i++)
  {
    x = postfix[i];
    if(isOperand(x))
    {
      v[i].setData(x);
      vp[i] = & v[i];
      StackT.push(vp[i]);
      //cout << "Arbol iteración " << i << ":" << endl;
      //v[i].print(cout);
      //cout << endl;
    }
    else
    {
      if(x == '*')
      {
        v[i].setData(x);
        v[i].setLeft(StackT.top());
        StackT.pop();
        vp[i] = & v[i];
        StackT.push(vp[i]);
        //cout << "Arbol iteración " << i << ":" << endl;
        //v[i].print(cout);
        //cout << endl;
      }
      else
      {
        v[i].setData(x);
        v[i].setRight(StackT.top());
        StackT.pop();
        v[i].setLeft(StackT.top());
        StackT.pop();
        vp[i] = & v[i];
        StackT.push(vp[i]);
        //cout << "Arbol iteración " << i << ":" << endl;
        //v[i].print(cout);
        //cout << endl;
      }
    }
  }
  StackT.pop();
}

void ER2tree::placeConcat(string & cadena)
{
  string aux;
  char x;
  aux.push_back(cadena[0]);
  for(int i = 1; i < cadena.size(); i++)
  {
    x = cadena[i];
    aux.push_back(x);
    if(x == '*' && i != cadena.size() - 1 && (cadena[i + 1] == '(' || isOperand(cadena[i + 1])))
    {
      aux.push_back('&');
    }
    else if((isOperand(cadena[i - 1]) && isOperand(x)) || (cadena[i - 1] == ')' && x == '('))
    {
      aux.pop_back();
      aux.push_back('&');
      aux.push_back(x);
    }
  }
  cadena = aux;
}
