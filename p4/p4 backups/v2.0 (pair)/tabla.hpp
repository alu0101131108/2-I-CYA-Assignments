//aqui van todos los includes de STL.
#include <set>
#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

class Tabla
{
  private:

    vector<char> caracteres;
    vector<vector<pair<int, bool>>> asociados;

  public:

    Tabla(vector<char> caracteres_, vector<vector<pair<int, bool>>> asociados_):
    caracteres(caracteres_), asociados(asociados_)
    {}

    pair<int, bool> asociado(int estado, char caracter);      // Devuelve el id del estado asociado a los parámetros estado y caracter.

};
