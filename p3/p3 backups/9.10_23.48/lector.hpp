#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>

#include "calculadora.cpp"

using namespace std;

class Reader
{
  private:
    string filename;

  public:
    Reader(string name): filename(name)
    {}

    string getFilename()
    {
      return filename;
    }

    // Almacena las palabras leidas de un fichero en una matriz de string.
    void storeInMatrix(vector<vector<string>> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4);
    // Almacena las palabras leidas de un fichero en un vector de lenguajes, siendo un lenguaje independiente cada linea del fichero.
    void getLangVec(vector<Language> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4);
};
