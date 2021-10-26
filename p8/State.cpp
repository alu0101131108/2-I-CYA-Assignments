#include "State.hpp"

typedef pair<string, string> transition;

vector<transition> State::getTransitions()
{
  return transitions;
}

string State::getId()
{
  return id;
}

void State::addTransition(string in_symbol, string next_state)
{
  transitions.push_back(make_pair(in_symbol, next_state));
}

void State::print(ostream & os)
{
  os << id + ":" << endl;
  for(int i = 0; i < transitions.size(); i++)
    os << transitions[i].first + " -> " + transitions[i].second << endl;
}
