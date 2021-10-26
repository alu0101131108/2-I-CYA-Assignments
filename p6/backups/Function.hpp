#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cassert>
#include <string>

using namespace std;

const int TEXT_WIDTH = 10;

class Function
{
  private:

    vector<string> x;           // Visto como una tabla, representan los índices horizontales.
    vector<string> y;           // Visto como una tabla, representan los índices verticales.
    vector<vector<string>> z;   // Visto como una tabla, representa el valor de f(x,y). Si f(x,y) = "$", esa relación no está definida.

    string width(string data, int width);

  public:

    Function()
    {}

    void initializeEmpty(set<string> horizontal, set<string> vertical);         // Asocia los elementos de dos set con 'x' e 'y' respectivamente. ∀(x,y): f(x,y) = "$".
    void define(string x_element, string y_element, string z_element);          // Define la relación: f(x_element, y_element) = z_element.
    void print(ostream & out);
};
