#include "Grammar.hpp"

void Grammar::readFromFile(string filename)
{
  ifstream ifs;
  string line, text;
  ifs.open(filename);                         // Convierte el archivo de entrada en un string.
  while(!ifs.eof())                           // Ignora las lineas que correspondan a comentarios.
  {
    getline(ifs, line);
    if(line[0] != '/' && line[1] != '/')
      text = text + line + "\n";
  }
  ifs.close();
                                              // Se analiza el texto "descomentado".
  stringstream in(text);
  string aux, init_ntsID, prod_label, prod_value, final_ntsID;
  set<string> in_ts;
  int size;

  in >> aux;                                                                    // (1) Símbolos terminales (Alfabeto).
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    assert(aux != " " && aux != "\n" && aux.size() == 1);
    alphabet.insert(aux);
  }
  //cout << "Alfabeto leido." << endl;

  in >> aux;                                                                    // (2) Símbolos no terminales.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    for(int j = 0; j < aux.size(); j++)
      assert((aux[j] >= 'a' && aux[j] <= 'z') || (aux[j] >= 'A' && aux[j] <= 'Z') || (aux[j] >= '0' && aux[j] <= '9'));
    NTSymbols.insert(NTSymbol(aux));
  }
  //cout << "Simbolos no terminales leidos." << endl;

  in >> aux;                                                                    // (3) Símbolo de arranque.
  assert(belong(aux, NTSymbols));
  init_NTSymbol = NTSymbol(aux);
  //cout << "Símbolo de arranque leido." << endl;

  in >> aux;                                                                    // (4) Producciones.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> init_ntsID;
    assert(belong(init_ntsID, NTSymbols));
    in >> prod_label;
    assert(prod_label == PROD_LABEL);
    in >> prod_value;
    final_ntsID = string(1, prod_value[prod_value.size() - 1]);
    if(belong(final_ntsID, NTSymbols))
    {
      for(int j = 0; j < prod_value.size() - 1; j++)
        in_ts.insert(string(1, prod_value[j]));
    }
    else
    {
      for(int j = 0; j < prod_value.size(); j++)
        in_ts.insert(string(1, prod_value[j]));
      final_ntsID = "$";
    }
    for(auto nts : NTSymbols)
      if(nts.getId() == init_ntsID)
        nts.defineProduction(in_ts, final_ntsID);
  }
  //cout << "Producciones leidas." << endl;
}

bool Grammar::belong(string id, set<NTSymbol> container)
{
  bool result = false;
  for(auto elem : container)
    if(elem.getId() == id)
      result = true;
  return result;
}

string Grammar::setToString(set<string> container)
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

void Grammar::print(ostream & os)
{
  os << "Alfabeto: " + setToString(alphabet) << endl;
  os << "Simbolos no terminales: " << endl;
  for(auto elem : NTSymbols)
    elem.print(os);
  os << "Simbolo de arranque: " << endl;
  init_NTSymbol.print(os);
}
