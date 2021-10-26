#include "FunctionNFA.hpp"

void FunctionNFA::initializeEmpty(set<string> horizontal, set<string> vertical)
{
  x = vector<string>(horizontal.begin(), horizontal.end());
  y = vector<string>(vertical.begin(), vertical.end());
  z.resize(x.size());
  for(int i = 0; i < x.size(); i++)
    z[i].resize(y.size() + 1);
}

void FunctionNFA::define(string x_element, string y_element, string z_element)
{
  int x_it = -1, y_it = -1;
  for(int i = 0; i < x.size(); i++)
    if(x[i] == x_element)
      x_it = i;
  if(y_element == epsilon_label)
    y_it = y.size();
  else
  {
    for(int i = 0; i < y.size(); i++)
      if(y[i] == y_element)
        y_it = i;
    assert(x_it != -1 && x_it != -1);
  }
  z[x_it][y_it].insert(z_element);
}

void FunctionNFA::print(ostream & out)
{
  out << "Y \\ X" + width("Y \\ X", TEXT_WIDTH);
  for(int i = 0; i < x.size(); i++)
    out << x[i] + width(x[i], TEXT_WIDTH);
  out << endl;
  for(int j = 0; j <= y.size(); j++)
  {
    if(j == y.size())
      out << epsilon_label + ":" + width(epsilon_label + ":", TEXT_WIDTH);
    else
      out << y[j] + ":" + width(y[j] + ":", TEXT_WIDTH);
    for(int i = 0; i < x.size(); i++)
      out << setToString(z[i][j]) + width(setToString(z[i][j]), TEXT_WIDTH);
    out << endl;
  }
}

string FunctionNFA::width(string data, int width)
{
  int realwidth = width - data.size();
  string aux(realwidth, ' ');
  return aux;
}

string FunctionNFA::transitionsToString()
{
  string result;
  for(int j = 0; j <= y.size(); j++)
    for(int i = 0; i < x.size(); i++)
      if(!z[i][j].empty())
        for(auto elem : z[i][j])
          if(j != y.size())
            result += "  \"" + x[i] + "\"" + width(x[i], TEXT_WIDTH) + "->  \"" + elem + "\"" + width(elem, TEXT_WIDTH) + "[label = \"" + y[j] + "\"];\n";
          else
            result += "  \"" + x[i] + "\"" + width(x[i], TEXT_WIDTH) + "->  \"" + elem + "\"" + width(elem, TEXT_WIDTH) + "[label = \"" + epsilon_label + "\"];\n";
  return result;
}

vector<string> FunctionNFA::findDeadStates()
{
	vector<string> result;
	bool isDead;
	for(int i = 0; i < x.size(); i++)
	{
		isDead = true;
		for(int j = 0; j <= y.size(); j++)
		{
			if(!z[i][j].empty())
				isDead = false;
		}
		if(isDead == true)
		  result.push_back(x[i]);
	}
	return result;

}

string FunctionNFA::setToString(set<string> container)
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

set<string> FunctionNFA::singleVoidReachableFrom(string state)
{
  int x_it = -1;
  for(int i = 0; i < x.size(); i++)
    if(x[i] == state)
      x_it = i;
  assert(x_it != -1);
  return z[x_it][y.size()];
}

set<string> FunctionNFA::singleReachableFrom(string state, string symbol)
{
  int x_it = -1, y_it = -1;
  for(int i = 0; i < x.size(); i++)
    if(x[i] == state)
      x_it = i;
  for(int j = 0; j < y.size(); j++)
    if(y[j] == symbol)
      y_it = j;
  assert(x_it != -1 && y_it != -1);
  return z[x_it][y_it];
}
