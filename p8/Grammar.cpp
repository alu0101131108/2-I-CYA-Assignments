#include "Grammar.hpp"

typedef pair<vector<string>, string> production;

void Grammar::importFromFile(string filename)
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
  vector<string> in_ts;
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
    NTSymbols.push_back(NTSymbol(aux));
  }
  //cout << "Simbolos no terminales leidos." << endl;

  in >> aux;                                                                    // (3) Símbolo de arranque.
  assert(belong(aux, NTSymbols));
  init_NTSymbol_ID = aux;
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
        in_ts.push_back(string(1, prod_value[j]));
    }
    else
    {
      for(int j = 0; j < prod_value.size(); j++)
        in_ts.push_back(string(1, prod_value[j]));
      final_ntsID = "$";
    }
    for(int j = 0; j < NTSymbols.size(); j++)
      if(NTSymbols[j].getId() == init_ntsID)
        NTSymbols[j].defineProduction(in_ts, final_ntsID);
    in_ts.clear();
  }
  // cout << "Producciones leidas." << endl;
}

bool Grammar::belong(string id, vector<NTSymbol> container)
{
  bool result = false;
  for(int i = 0; i < container.size(); i++)
    if(container[i].getId() == id)
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
  for(int i = 0; i < NTSymbols.size(); i++)
    NTSymbols[i].print(os);
  os << "Simbolo de arranque: " + init_NTSymbol_ID << endl;
}

Nfa Grammar::convertToNFA()
{
  Nfa output;
  output.setAlphabet(alphabet);
  output.setInitStateId(init_NTSymbol_ID);
  output.setVoidLabel(void_label);

  vector<production> productions;
  vector<State> nfa_states, aux_new_states;
  set<string> final_state_IDs;

  for(int i = 0; i < NTSymbols.size(); i++)
    nfa_states.push_back(State(NTSymbols[i].getId()));

  for(int i = 0; i < NTSymbols.size(); i++)
  {
    productions = NTSymbols[i].getProductions();
    for(int j = 0; j < productions.size(); j++)
    {
      if(productions[j].second == "$")    // Si en la producción solo hay símbolos terminales.
      {
        // aux_new_states - Crear tantos estados como productions[j].first.size() de nombre aux-i-j-k, el último aux-final-i-j-k.
        for(int k = 0; k < productions[j].first.size(); k++)          // Crear tantos estados auxiliares como símbolos terminales tenga la producción.
          aux_new_states.push_back(State("aux" + to_string(i) + to_string(j) + to_string(k)));   // Su identificador será aux-i-j-k.
        nfa_states[getIndex(NTSymbols[i].getId(), nfa_states)].addTransition(productions[j].first[0], aux_new_states[0].getId()); // Primera transicion del simbolo no terminal en cuestión al primer estado auxiliar creado.
        for(int k = 0; k < aux_new_states.size() - 1; k++)
          aux_new_states[k].addTransition(productions[j].first[k + 1], aux_new_states[k + 1].getId());    // Resto de transiciones de un estado auxiliar al siguiente.
        final_state_IDs.insert(aux_new_states[aux_new_states.size() - 1].getId());      // add aux_new_states[aux_new_states.size() - 1] a final states.
      }
      else if(productions[j].first.size() == 1)         // Si en la producción hay un símbolo no terminal y solo un simbolo terminal.
      {
        nfa_states[getIndex(NTSymbols[i].getId(), nfa_states)].addTransition(productions[j].first[0], productions[j].second); // Se añade la transición desde el simbolo no terminal en cuestion al simbolo no terminal de su producción.
      }
      else              // Si en la producción hay un símbolo no terminal y más de un simbolo terminal.
      {
        for(int k = 0; k < productions[j].first.size() - 1; k++)          // Crear n-1 estados auxiliares, donde la producción tiene n simbolos terminales.
          aux_new_states.push_back(State("aux" + to_string(i) + to_string(j) + to_string(k)));   // Su identificador será aux-i-j-k.
        nfa_states[getIndex(NTSymbols[i].getId(), nfa_states)].addTransition(productions[j].first[0], aux_new_states[0].getId()); // Primera transicion de estado snt en cuestion al primer estado auxiliar con el primer terminal de la produccion.
        for(int k = 0; k < aux_new_states.size() - 1; k++)
          aux_new_states[k].addTransition(productions[j].first[k + 1], aux_new_states[k + 1].getId());    // Resto de transiciones de un estado auxiliar al siguiente.
        aux_new_states[aux_new_states.size() - 1].addTransition(productions[j].first[productions[j].first.size() - 1], productions[j].second);  // Ultima transicion del ultimo estado aux al simbolo no terminal de la produccion con el ultimo terminal de la producción.
      }
      for(int k = 0; k < aux_new_states.size(); k++)          // Añado los estados auxiliares a los del nuevo nfa.
        nfa_states.push_back(aux_new_states[k]);
      aux_new_states.clear();
    }

  }

  output.addStates(nfa_states);

  for(auto elem : final_state_IDs)
    output.addFinalState(elem);

  return output;
}

int Grammar::getIndex(string id, vector<State> container)
{
  int index = -1;
  for(int i = 0; i < container.size(); i++)
    if(container[i].getId() == id)
      index = i;
  return index;
}
