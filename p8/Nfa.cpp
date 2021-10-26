#include "Nfa.hpp"

typedef pair<string, string> transition;

void Nfa::addNewState(string id)
{
  for(int i = 0; i < states.size(); i++)
    assert(states[i].getId() != id);
  states.push_back(State(id));
}

void Nfa::addStates(vector<State> input_states)
{
  for(int i = 0; i < input_states.size(); i++)
    states.push_back(input_states[i]);
}

int Nfa::getStateIndex(string id)
{
  int index = -1;
  for(int i = 0; i < states.size(); i++)
    if(states[i].getId() == id)
      index = i;
  return index;
}

void Nfa::addFinalState(string id)
{
  assert(getStateIndex(id) >= 0);
  final_state_IDs.insert(id);
}

void Nfa::setVoidLabel(string label)
{
  void_label = label;
}

void Nfa::setAlphabet(set<string> in_alphabet)
{
  alphabet = in_alphabet;
}

void Nfa::setInitStateId(string id)
{
  init_state_ID = id;
}

void Nfa::print(ostream & os)
{
  os << "Alfabeto: " + setToString(alphabet) << endl;
  for(int i = 0; i < states.size(); i++)
    states[i].print(os);
  os << "Estado inicial: " + init_state_ID << endl;
  os << "Estados finales: " + setToString(final_state_IDs) << endl;
}

string Nfa::setToString(set<string> container)
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

void Nfa::exportToFile(string filename)
{
  ofstream ofs;
  ofs.open(filename);

  ofs << alphabet.size() << endl;                           // Número de símbolos del alfabeto.
  ofs << void_label << endl;                                // Etiqueta para transición vacía.
  for(auto elem : alphabet)                                 // Cada símbolo del alfabeto.
    ofs << elem << endl;
  ofs << states.size() << endl;                             // Número de estados.
  for(int i = 0; i < states.size(); i++)                    // Cada estado.
    ofs << states[i].getId() << endl;
  ofs << init_state_ID << endl;                             // Estado inicial.
  ofs << final_state_IDs.size() << endl;                    // Número de estados finales.
  for(auto elem : final_state_IDs)                          // Cada estado final.
    ofs << elem << endl;
  for(int i = 0; i < states.size(); i++)                    // Cada transición.
  {
    vector<transition> transitions = states[i].getTransitions();
    for(int j = 0; j < transitions.size(); j++)
      ofs << states[i].getId() + " " + transitions[j].first + " " + transitions[j].second << endl;
  }
  ofs.close();
}
