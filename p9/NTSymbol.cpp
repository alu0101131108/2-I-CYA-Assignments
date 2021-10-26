#include "NTSymbol.hpp"

typedef vector<string> production;

string NTSymbol::getId()
{
  return id;
}

void NTSymbol::setId(string name)
{
  id = name;
}

vector<production> NTSymbol::getProductions()
{
  return productions;
}

void NTSymbol::setProductionAt(vector<string> newprod, int index)
{
  productions[index] = newprod;
}

void NTSymbol::setDualProductionAt(string symb1, string symb2, int index)
{
  vector<string> newprod;
  newprod.push_back(symb1);
  newprod.push_back(symb2);
  setProductionAt(newprod, index);
}

void NTSymbol::defineProduction(vector<string> symbols)
{
  productions.push_back(symbols);
}

void NTSymbol::defineDualProduction(string symb1, string symb2)
{
  vector<string> newprod;
  newprod.push_back(symb1);
  newprod.push_back(symb2);
  defineProduction(newprod);
}

void NTSymbol::print(ostream & os)
{
  os << "ID: " + id << endl;
  for (int i = 0; i < productions.size(); i++)
    os << "        " + PROD_LABEL + " " + vectorToString(productions[i]) << endl;
}

string NTSymbol::vectorToString(vector<string> container)
{
  string result, aux;
  if (!container.empty())
  {
    result = "(";
    for (int i = 0; i < container.size(); i++)
      aux = aux + container[i] + ", ";
    aux.pop_back();
    aux.pop_back();
    result = result + aux + ")";
  }
  else
    result = "()";
  return result;
}

void NTSymbol::prodSymbolReplace(string old_symbol, string new_symbol)
{
  for (int i = 0; i < productions.size(); i++)
    if (productions[i].size() >= 2)
      for (int j = 0; j < productions[i].size(); j++)
        if (productions[i][j] == old_symbol)
          productions[i][j] = new_symbol;
}

int NTSymbol::countProductions()
{
  return productions.size();
}
