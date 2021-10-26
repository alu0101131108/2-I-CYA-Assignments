#include "NTSymbol.hpp"
void NTSymbol::defineProduction(set<string> in_symbols, string final_ntsID = "$")
{
    productions.insert(make_pair(in_symbols, final_ntsID));
}

void NTSymbol::print(ostream & os)
{
  os << "ID: " + id + "." << endl;
  os << "Productions:" << endl;
  for(auto elem : productions)
    os << "  " + setToString(elem.first) +  " -> " + elem.second << endl;
}

string NTSymbol::setToString(set<string> container)
{
  string result, aux;
  if(!container.empty())
  {
    result = "{";
    for(auto elem : container)
      aux = aux + elem + ", ";
    aux.pop_back();
    aux.pop_back();
    result = result + aux + "}";
  }
  else
    result = "{}";
  return result;
}
