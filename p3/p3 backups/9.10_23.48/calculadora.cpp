#include "calculadora.hpp"

// lenguaje1.getv()[i] me da el valor de la i-ésima cadena que forma lenguaje1.
// lenguaje1.getv().size() me da el numero de cadenas que forman el lenguaje.

Language Calculator::op_concatenacion(Language a, Language b)
{
  if(a.getv().size() == 1 && a.getv()[0] == "&")
    return b;
  else if(b.getv().size() == 1 && a.getv()[0] == "&")
    return a;
  else
  {
    vector<string> aux_v;

    for(int i = 0; i < a.getv().size(); i++)        // Para cada elemento de a.v
      for(int j = 0; j < b.getv().size(); j++)      // Para cada elemento de b.v
        if(count(aux_v.begin(), aux_v.end(), a.getv()[i]+b.getv()[j]) == 0)   // Compruebo que el elemento no está ya en el vector.
          aux_v.push_back(a.getv()[i]+b.getv()[j]);   // Concateno a.v[i] con b.v[i] y lo meto en aux_v.

    Language aux_l(aux_v);
    return aux_l;
  }
}

Language Calculator::op_union(Language a, Language b)
{
  vector<string> aux_v;

  for(int i = 0; i < a.getv().size(); i++)                // Recorro a.v.
    if(count(aux_v.begin(), aux_v.end(), a.getv()[i])==0) // Si el elemento a.v[i] no se ha encontrado antes, se ingresa en aux_v.
      aux_v.push_back(a.getv()[i]);
  for(int i = 0; i < b.getv().size(); i++)
    if(count(aux_v.begin(), aux_v.end(), b.getv()[i])==0) // Hago lo mismo recorriendo b.v
      aux_v.push_back(b.getv()[i]);

  Language aux_l(aux_v);
  return aux_l;
}

Language Calculator::op_interseccion(Language a, Language b)
{
  vector<string> aux_v;
  vector<string> aux_v_b = b.getv();                // Soluciona error en count al acceder al vector de b.

  for(int i = 0; i < a.getv().size(); i++)                           // Recorro a.v.
    if(count(aux_v_b.begin(), aux_v_b.end(), a.getv()[i]) == 1)      // Si a.v[i] pertenece a b.v entonces a.v[i] -> aux_v.
      aux_v.push_back(a.getv()[i]);

  Language aux_l(aux_v);
  return aux_l;
}

Language Calculator::op_diferencia(Language a, Language b)
{
  vector<string> aux_v;
  vector<string> aux_v_b = b.getv();

  for(int i = 0; i < a.getv().size(); i++)
    if(count(aux_v_b.begin(), aux_v_b.end(), a.getv()[i]) == 0)    // Si no encuentro a.v[i] en b.v, meto esa cadena en aux_v.
      aux_v.push_back(a.getv()[i]);

  Language aux_l(aux_v);
  return aux_l;
}

bool Calculator::op_sublenguaje(Language a, Language b)
{
  bool is_subc = true;
  vector<string> aux_v_b = b.getv();

  for(int i = 0; i < a.getv().size(); i++)
    if(count(aux_v_b.begin(), aux_v_b.end(), a.getv()[i]) == 0)    // si a.v[i] no existe en b.v, entonces a no es subconjunto de b.
      is_subc = false;

  return is_subc;
}

bool Calculator::op_igualdad(Language a, Language b)
{
  return op_sublenguaje(a, b) * op_sublenguaje(b, a);
}

Language Calculator::op_inversa(Language a)
{
  vector<string> aux_v;
  string aux_str;

  for(int i = 0; i <  a.getv().size(); i++)         // Recorro el a.v.
  {
    for(int j = a.getv()[i].size() - 1; j >= 0; j--)     // Recorro el string i del vector, de delante hacia atrás.
      aux_str.push_back(a.getv()[i][j]);            // Meto el caracter j del string v, al final del string aux_str.

    aux_v.push_back(aux_str);                       // Ingreso el string invertido en el aux_v.
    aux_str.clear();                                // Limpio el aux_str para iniciar la siguiente iteración con el string vacío.
  }

  Language aux_l(aux_v);
  return aux_l;
}

Language Calculator::op_potencia(Language a, int exp)   // Función recursiva, definición de potencia.
{
  if(exp == 0 || (a.getv().size() == 1 && a.getv()[0] == "&"))                        // Caso base 1
  {
    vector<string> aux_v = {"&"};
    Language lcadvacia(aux_v);
    return lcadvacia;
  }
  else if(exp == 1)                  // Caso base 2
    return a;
  else
    return op_concatenacion(a, op_potencia(a, exp-1));  // Parte recursiva.
}

Language Calculator::op_cierre_pos(Language a)
{
  if(a.getv().size() == 0 || (a.getv().size() == 1 && a.getv()[0] == "&"))
    return a;
  else
  {
    Language aux_l;
    int i = 1;
    do{
        aux_l = op_union(aux_l, op_potencia(a, i));
        i++;

      } while(aux_l.getv().size() < 10);

    aux_l.setInfinite();                  //Indica que será infinito.
    return aux_l;
  }
}

Language Calculator::op_cierre_kleene(Language a)   // Es igual al cierre positivo pero la iteración de la potencia
{                                                   // empezará en 1.
  if(a.getv().size() == 0 || (a.getv().size() == 1 && a.getv()[0] == "&"))
    return op_potencia(a, 0);
  else
  {
    Language aux_l;
    int i = 0;
    do{
        aux_l = op_union(aux_l, op_potencia(a, i));
        i++;

      } while(aux_l.getv().size() < 10);
    aux_l.setInfinite();                        // Indica que será infinito.
    return aux_l;
  }
}

vector<Language> Calculator::codeOperation()        // Rellenará un vector de lenguajes con los resultados de la operacion code.
{
  vector<Language> aux_lv;
  switch (code)
  {
    case 1:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_lv.push_back(op_concatenacion(operand[i-1], operand[i]));
    break;

    case 2:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_lv.push_back(op_union(operand[i-1], operand[i]));
    break;

    case 3:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_lv.push_back(op_interseccion(operand[i-1], operand[i]));
    break;

    case 4:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_lv.push_back(op_diferencia(operand[i-1], operand[i]));
    break;

    case 7:
      for(int i = 0; i < operandCardinal; i++)    //Ahora se recorre el vector entero.
        aux_lv.push_back(op_inversa(operand[i]));
    break;

    case 8:
      for(int i = 0; i < operandCardinal; i++)    //Ahora se recorre el vector entero.
        aux_lv.push_back(op_potencia(operand[i], op_pot_exp));
    break;

    case 9:
      for(int i = 0; i < operandCardinal; i++)    //Ahora se recorre el vector entero.
        aux_lv.push_back(op_cierre_pos(operand[i]));
    break;

    case 10:
      for(int i = 0; i < operandCardinal; i++)    //Ahora se recorre el vector entero.
        aux_lv.push_back(op_cierre_kleene(operand[i]));
    break;
  }
  return aux_lv;
}

vector<bool> Calculator::codeOperation_bool()       // Rellenará un vector de bool para las operaciones sublenguaje e igualdad.
{
  vector<bool> aux_bv;

  switch (code)
    {
    case 5:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_bv.push_back(op_sublenguaje(operand[i-1], operand[i]));
    break;

    case 6:
      if(operandCardinal%2 != 0)      // Si el numero de lenguajes es impar, no se operará con el último.
        operandCardinal--;
      for(int i = 1; i < operandCardinal; i = i+2)
        aux_bv.push_back(op_igualdad(operand[i-1], operand[i]));
    break;
  }
  return aux_bv;
}
