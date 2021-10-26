#include "Grammar.hpp"

typedef vector<string> production;

void Grammar::importFromFile(string filename)
{
  ifstream ifs;
  string line, text;
  ifs.open(filename);                         // Convierte el archivo de entrada en un string.
  while(!ifs.eof())                           // Ignora las lineas que correspondan a comentarios.
  {
    getline(ifs, line);
    if (line[0] != '/' && line[1] != '/')
      text = text + line + "\n";
  }
  ifs.close();
                                              // Se analiza el texto "descomentado".
  stringstream in(text);
  string aux, main_nts_id, prod_label, prod_value;
  vector<string> splitted_prod_value;
  int size;

  in >> aux;                                                                    // (1) Símbolos terminales (Alfabeto).
  size = stoi(aux);
  for (int i = 0; i < size; i++)
  {
    in >> aux;
    assert(aux != " " && aux != "\n" && aux.size() == 1);
    alphabet.insert(aux);
  }
  //cout << "Alfabeto leido." << endl;

  in >> aux;                                                                    // (2) Símbolos no terminales.
  size = stoi(aux);
  for (int i = 0; i < size; i++)
  {
    in >> aux;
    for (int j = 0; j < aux.size(); j++)
      assert((aux[j] >= 'a' && aux[j] <= 'z') || (aux[j] >= 'A' && aux[j] <= 'Z') || (aux[j] >= '0' && aux[j] <= '9'));
    NTSymbols.push_back(NTSymbol(aux));
  }
  //cout << "Simbolos no terminales leidos." << endl;

  in >> aux;                                                                    // (3) Símbolo de arranque.
  assert(isNTSymbol(aux));
  init_NTSymbol_ID = aux;
  //cout << "Símbolo de arranque leido." << endl;

  in >> aux;                                                                    // (4) Producciones.
  size = stoi(aux);
  for (int i = 0; i < size; i++)
  {
    in >> main_nts_id;
    assert(isNTSymbol(main_nts_id));
    in >> prod_label;
    assert(prod_label == PROD_LABEL);
    in >> prod_value;
    // separa la parte derecha de una producción distinguiendo tsymbols de ntsymbols.
    splitted_prod_value = splitProduction(prod_value);
    // busca el ntsymbol en cuestion para añadirle su producción.
    for (int j = 0; j < NTSymbols.size(); j++)
      if (NTSymbols[j].getId() == main_nts_id)
        NTSymbols[j].defineProduction(splitted_prod_value);
    splitted_prod_value.clear();
  }
  // cout << "Producciones leidas." << endl;
}

void Grammar::setAlphabet(set<string> new_alphabet)
{
  for (auto elem : new_alphabet)
  assert(elem != " " && elem != "\n" && elem.size() == 1);
  alphabet = new_alphabet;
}

void Grammar::setNTSymbols(vector<NTSymbol> new_NTSymbols)
{
  string aux;
  for (int i = 0; i < new_NTSymbols.size(); i++)
  {
    aux = new_NTSymbols[i].getId();
    for (int j = 0; j < aux.size(); j++)
    assert((aux[j] >= 'a' && aux[j] <= 'z') || (aux[j] >= 'A' && aux[j] <= 'Z') || (aux[j] >= '0' && aux[j] <= '9'));
  }
  NTSymbols = new_NTSymbols;
}

void Grammar::setInitNTSymbolID(string new_initID)
{
  assert(isNTSymbol(new_initID));
  init_NTSymbol_ID = new_initID;
}

void Grammar::setVoidLabel(string new_void_label)
{
  void_label = new_void_label;
}

bool Grammar::isNTSymbol(string id)
{
  return isNTSymbolFrom(id, NTSymbols);
}

bool Grammar::isNTSymbolFrom(string id, vector<NTSymbol> container)
{
  bool result = false;
  for (int i = 0; i < container.size(); i++)
    if (container[i].getId() == id)
      result = true;
  return result;
}

bool Grammar::isTSymbol(string id)
{
  bool result = false;
  for (auto elem : alphabet)
    if (elem == id)
      result = true;
  return result;
}

string Grammar::setToString(set<string> container)
{
  string result, aux;
  if (!container.empty())
  {
    result = "{";
    for (auto elem : container)
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
  os << "----------------------------------------------------" << endl;
  os << "Alfabeto: " + setToString(alphabet) << endl;
  os << "Simbolos no terminales: " << endl;
  for (int i = 0; i < NTSymbols.size(); i++)
    NTSymbols[i].print(os);
  os << "Simbolo de arranque: " + init_NTSymbol_ID << endl;
  os << "----------------------------------------------------" << endl;
}

int Grammar::countProductions()
{
  int result = 0;
  for(int i = 0; i < NTSymbols.size(); i++)
    result += NTSymbols[i].countProductions();
  return result;
}

vector<string> Grammar::splitProduction(string mixed_prod)
{
  vector<string> result;
  string aux;
  for (int i = 0; i < mixed_prod.size(); i++)
  {
    aux = string(1, mixed_prod[i]);
    assert(isNTSymbol(aux) || isTSymbol(aux));
    result.push_back(aux);
  }
  return result;
}

Grammar Grammar::saveAsCNF()
{
  Grammar result;
  result.setAlphabet(alphabet);
  result.setVoidLabel(void_label);
  vector<NTSymbol> new_NTSymbols = NTSymbols, aux_nts_vector;
  vector<vector<string>> nts_productions;
  vector<string> prod;
  string symbol;
  for (int i = 0; i < new_NTSymbols.size(); i++)
  {
    nts_productions = new_NTSymbols[i].getProductions();
    for (int j = 0; j < nts_productions.size(); j++)
    {
      prod = nts_productions[j];
      if (prod.size() >= 2)
        for (int k = 0; k < prod.size(); k++)
        {
          symbol = prod[k];
          if (isTSymbol(symbol) && !isNTSymbolFrom("C" + symbol, new_NTSymbols))
          {
            NTSymbol aux_nts("C" + symbol);
            aux_nts.defineProduction(vector<string>(1, symbol));
            for (int l = 0; l < new_NTSymbols.size(); l++)
              new_NTSymbols[l].prodSymbolReplace(symbol, "C" + symbol);
            new_NTSymbols.push_back(aux_nts);
          }
        }
    }
  }
  for (int i = 0; i < new_NTSymbols.size(); i++)
  {
    nts_productions = new_NTSymbols[i].getProductions();
    for (int j = 0; j < nts_productions.size(); j++)
    {
      prod = nts_productions[j];
      if (prod.size() >= 3)    // se crean prod.size()-2 NTSymbols auxiliares "D<i>".
      {
        for (int k = 0; k < prod.size() - 2; k++)
          aux_nts_vector.push_back(NTSymbol("D" + to_string(i) + to_string(j) + to_string(k)));
        new_NTSymbols[i].setDualProductionAt(prod[0], aux_nts_vector[0].getId(), j);
        for (int k = 0; k < aux_nts_vector.size(); k++)
        {
          if (k < aux_nts_vector.size() - 1)
            aux_nts_vector[k].defineDualProduction(prod[k + 1], aux_nts_vector[k + 1].getId());
          else
            aux_nts_vector[k].defineDualProduction(prod[k + 1], prod[k + 2]);
          new_NTSymbols.push_back(aux_nts_vector[k]);
        }
        aux_nts_vector.clear();
      }
    }
  }
  result.setNTSymbols(new_NTSymbols);
  result.setInitNTSymbolID(init_NTSymbol_ID);
  return result;
}

void Grammar::exportToFile(string filename)
{
  vector<vector<string>> productions;
  vector<string> prod;

  ofstream ofs;
  ofs.open(filename);
  ofs << alphabet.size() << endl;
  for (auto elem : alphabet)
    ofs << elem << endl;
  ofs << NTSymbols.size() << endl;
  for (int i = 0; i < NTSymbols.size(); i++)
    ofs << NTSymbols[i].getId() << endl;
  ofs << init_NTSymbol_ID << endl;
  ofs << countProductions() << endl;
  for (int i = 0; i < NTSymbols.size(); i++)
  {
    productions = NTSymbols[i].getProductions();
    for (int j = 0; j < productions.size(); j++)
    {
      ofs << NTSymbols[i].getId() + " " + PROD_LABEL + " ";
      prod = productions[j];
      for (int k = 0; k < prod.size(); k++)
        ofs << prod[k];
      ofs << endl;
    }
  }

  ofs.close();
}



















// jaja
