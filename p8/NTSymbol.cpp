#include "NTSymbol.hpp"

typedef pair<vector<string>, string> production;

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

void NTSymbol::defineProduction(vector<string> in_symbols, string final_ntsID = "$")
{
    productions.push_back(make_pair(in_symbols, final_ntsID));
}

void NTSymbol::print(ostream & os)
{
  os << "ID: " + id + "." << endl;
  for(int i = 0; i < productions.size(); i++)
    os << "  " + vectorToString(productions[i].first) +  " -> " + productions[i].second << endl;
}

string NTSymbol::vectorToString(vector<string> container)
{
  string result, aux;
  if(!container.empty())
  {
    result = "(";
    for(int i = 0; i < container.size(); i++)
      aux = aux + container[i] + ", ";
    aux.pop_back();
    aux.pop_back();
    result = result + aux + ")";
  }
  else
    result = "()";
  return result;
}
