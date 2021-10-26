#include "NFA.hpp"

void NFA::readFromFile(ifstream & ifs)
{
  string line, text;                          // Convierte el archivo de entrada en un string.
  while(!ifs.eof())                           // Ignora las lineas que correspondan a comentarios.
  {
    getline(ifs, line);
    if(line[0] != '/' && line[1] != '/')
      text = text + line + "\n";
  }

  stringstream in(text);                      // Se analiza el texto "descomentado".
  string aux, qi, sim, qf;
  int size;

  in >> aux;                                  // (1) Alfabeto.
  size = stoi(aux);
  in >> aux;                                  // Se lee la etiqueta para las ε-transiciones.
  epsilon_label = aux;
  Transition.setEpsLabel(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    for(int j = 0; j < aux.size(); j++)
      assert(aux[j] != ' ' && aux[j] != '\n');
    Alphabet.insert(aux);
  }
  //cout << "Alfabeto leido." << endl;

  in >> aux;                                  // (2) Estados.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    assert(syntaxOk(aux));
    Q.insert(aux);
  }
  //cout << "Estados leidos." << endl;

  in >> aux;                                  // (3) Estado inicial.
  assert(belong(aux, Q));
  Qo = aux;
  //cout << "Estado inicial leido." << endl;

  in >> aux;                                  // (4) Estados finales o de aceptación.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    assert(belong(aux, Q));
    F.insert(aux);
  }
  //cout << "Estados finales leidos." << endl;

  in >> aux;                                  // (5) Transiciones.
  size = stoi(aux);
  Transition.initializeEmpty(Q, Alphabet);
  for(int i = 0; i < size; i++)
  {
    in >> qi;
    in >> sim;
    in >> qf;
    assert(belong(qi, Q) && (belong(sim, Alphabet) || sim == epsilon_label) && belong(qf, Q));
    Transition.define(qi, sim, qf);
  }
  //cout << "Transiciones leidas." << endl;
}

bool NFA::belong(string element, set<string> container)
{
  return container.find(element) != container.end();
}

bool NFA::syntaxOk(string aux)
{
  bool ok = true;
  for(int j = 0; j < aux.size(); j++)
    if(!((aux[j] >= 'a' && aux[j] <= 'z') || (aux[j] >= 'A' && aux[j] <= 'Z') || (aux[j] >= '0' && aux[j] <= '9')))
      ok = false;
  return ok;
}

void NFA::displayInfo(ostream & out)
{
  out << "Σ:";
  for(auto it=Alphabet.begin(); it != Alphabet.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Q:";
  for(auto it=Q.begin(); it != Q.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Qo: " + Qo + "." << endl;

  out << "F:";
  for(auto it=F.begin(); it != F.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Tabla de transición:" << endl;
  Transition.print(out);
}

string NFA::finalStatesToString()
{
  string aux, result;
  for(auto elem : F)
  {
    aux = elem;
    aux = "\"" + aux + "\"";
    result += aux + " ";
  }
  return result;
}

void NFA::generateDotFile(ofstream & ofs)
{
  ofs << "digraph DFA {\n  rankdir = LR;\n  size = \"10, 4\";\n  d2tstyleonly = true;\n";
  ofs << "  node [shape = none]; \" \";\n";
  //ofs << "  node [shape = Mcircle]; " + deadStatesToString() + ";\n";
  ofs << "  node [shape = doublecircle]; " + finalStatesToString() + ";\n";
  ofs << "  node [shape = circle];\n";
  ofs << "  \" \" -> \"" + Qo + "\"\n";
  ofs << Transition.transitionsToString() + "}";
}

string NFA::deadStatesToString()
{
	vector<string> deadStates = Transition.findDeadStates();
	string result;
	for(int i = 0; i < deadStates.size(); i++)
		result = result + "\"" + deadStates[i] + "\" ";
	return result;
}

set<string> NFA::eclausura(set<string> T)
{
  set<string> result, aux;
  stack<string> Stack;
  string p;
  if(T.empty())
    return result;
  else
  {
    for(auto elem : T)
      Stack.push(elem);
    result = T;
    while(!Stack.empty())
    {
      p = Stack.top();
      Stack.pop();
      aux = Transition.singleVoidReachableFrom(p);
      for(auto u : aux)
        if(result.find(u) == result.end())
        {
          result.insert(u);
          Stack.push(u);
        }
    }
    return result;
  }
}

set<string> NFA::move(set<string> S, string a)
{
  set<string> result, aux;
  stack<string> Stack;
  string p;
  if(S.empty())
    return result;
  else
  {
    for(auto elem : S)
      Stack.push(elem);

    while(!Stack.empty())
    {
      p = Stack.top();
      Stack.pop();
      aux = Transition.singleReachableFrom(p, a);

      for(auto u : aux)
          result.insert(u);
    }
    return result;
  }
}

void NFA::generateDFAfromSubsetAlgorithm(ofstream & ofs)
{
  int                 state_num = 0;            // Contador de estados del nuevo DFA.
  set<set<string>>    state_set;                // Contendrá los estados del nuevo DFA.
  set<set<string>>    unmarked_states;          // Contendrá los estados no marcados.
  set<string>         aux_state;                // Se utilizará en el cálculo de estados.
  vector<set<string>> trans_qi;                 //
  vector<string>      trans_symbol;             // Representarán transiciones de la forma f(qi, symbol) = qf.
  vector<set<string>> trans_qf;                 //

  aux_state = eclausura({Qo});                  // Estado inicial con Qo.
  unmarked_states.insert(aux_state);
  state_set.insert(aux_state);
  state_num++;
  while(!unmarked_states.empty())               // Cálculo del resto de estados apartir del inicial.
  {
    for(auto unmarkedstate : unmarked_states)
    {
      unmarked_states.erase(unmarkedstate);
      for(auto symbol : Alphabet)
      {
        aux_state = eclausura(move(unmarkedstate, symbol));
        if(state_set.find(aux_state) == state_set.end())      //Si el estado hallado es nuevo.
        {
          unmarked_states.insert(aux_state);
          state_set.insert(aux_state);
          state_num++;
        }
        trans_qi.push_back(unmarkedstate);                    //La transición hallada será:
        trans_symbol.push_back(symbol);
        trans_qf.push_back(aux_state);
      }
    }
  }
  // En este punto ya están calculados los estados del DFA y sus transiciones se guardan en
  // tres vectores: trans_qi, trans_symbol y trans_qf. Y  representan f(qi, symbol) = qf.

  vector<string> named_qi = nameVectorElements(state_set, trans_qi);    // Aquí sustituyo los elementos set<string> que representan
  vector<string> named_qf = nameVectorElements(state_set, trans_qf);    // estados, por un identificador de tipo string.

  set<set<string>> final_states_set;         // Contendrá los estados finales sin nombrar.
  for(auto elem : state_set)
    for(auto state : elem)
      if(F.find(state) != F.end())           // Si alguno de los estados que forman un nuevo estado del DFA es de aceptación,
        final_states_set.insert(elem);       // el nuevo estado del DFA también lo será.

  vector<set<string>> aux(final_states_set.begin(), final_states_set.end());
  vector<string> named_final_states = nameVectorElements(state_set, aux); // Contendrá los estados finales nombrados.

  // Generación del archivo que contendrá la especificación del DFA.
  ofs << Alphabet.size() << endl;                                   // Número de símbolos del alfabeto.
  for(auto elem : Alphabet)                                         // Cada símbolo.
    ofs << elem << endl;
  ofs << state_num << endl;                                         // Número de estados.
  for(int i = 0; i < state_num; i++)                                // Cada estado.
    ofs << i << endl;
  ofs << "0" << endl;                                               // Estado inicial.
  ofs << named_final_states.size() << endl;                         // Número de estados finales.
  for(int i = 0; i < named_final_states.size(); i++)                // Cada estado final.
    ofs << named_final_states[i] << endl;
  ofs << named_qi.size() << endl;                                   // Número de transiciones.
  for(int i = 0; i < named_qi.size(); i++)
    ofs << named_qi[i] + " " + trans_symbol[i] + " " + named_qf[i] << endl;     // Transiciones del modo "id_estado_inicial símbolo id_estado_final".
}

string NFA::setToString(set<string> container)
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

vector<string> NFA::nameVectorElements(set<set<string>> elements, vector<set<string>> & unnamed_vector)
{
  int aux_name = 0;
  vector<string> named_vector(unnamed_vector.size(), "-1");
  for(auto elem : elements)
  {
    for(int i = 0; i < unnamed_vector.size(); i++)
      if(unnamed_vector[i] == elem)
        named_vector[i] = to_string(aux_name);
    aux_name++;
  }
  return named_vector;
}
