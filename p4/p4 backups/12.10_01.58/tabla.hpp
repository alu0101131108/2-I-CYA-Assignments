//aqui van todos los includes de STL.
#include <set>
#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Tabla
{
  private:

    vector<char> caracteres;
    vector<vector<int>> asociados;

  public:

    Tabla(vector<int> estados, vector<char> caracteres_, vector<vector<int>> asociados_):
    caracteres(caracteres_), asociados(asociados_)
    {
      assert(estados.size() * caracteres.size() + 1 == asociados.size());
    }

    int asociado(int estado, char caracter);      // Devuelve el id del estado asociado a los parámetros estado y caracter.


};
