#include "Function.hpp"

void Function::initializeEmpty(set<string> horizontal, set<string> vertical)
{
  x = vector<string>(horizontal.begin(), horizontal.end());
  y = vector<string>(vertical.begin(), vertical.end());
  z.resize(x.size());
  for(int i = 0; i < x.size(); i++)
    for(int j = 0; j < y.size(); j++)
      z[i].push_back("$");
}

void Function::define(string x_element, string y_element, string z_element)
{
  int x_it = -1, y_it = -1;
  for(int i = 0; i < x.size(); i++)
    if(x[i] == x_element)
      x_it = i;
  for(int i = 0; i < y.size(); i++)
    if(y[i] == y_element)
      y_it = i;
  assert(x_it != -1 && x_it != -1);
  z[x_it][y_it] = z_element;
}

void Function::print(ostream & out)
{
  out << "Y \\ X" + width("Y \\ X", TEXT_WIDTH);
  for(int i = 0; i < x.size(); i++)
    out << x[i] + width(x[i], TEXT_WIDTH);
  out << endl;
  for(int i = 0; i < y.size(); i++)
  {
    out << y[i] + ":" + width(y[i] + ":", TEXT_WIDTH);
    for(int j = 0; j < x.size(); j++)
      out << z[j][i] + width(z[j][i], TEXT_WIDTH);
    out << endl;
  }
}

string Function::width(string data, int width)                                      // Se utiliza para alinear la tabla de resultados en el outfile.
{
  int realwidth = width - data.size();
  string aux(realwidth, ' ');
  return aux;
}
