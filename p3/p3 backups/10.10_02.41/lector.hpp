#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>

#include "calculadora.cpp"

using namespace std;

class FileIO
{
  private:
    string filename;

  public:
    FileIO(string name): filename(name)
  {}

    string getFilename()
    {
      return filename;
    }

    // Almacena las palabras leidas de un fichero en una matriz de string.
    void storeInMatrix(vector<vector<string>> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4);
    // Almacena las palabras leidas de un fichero en un vector de lenguajes, siendo un lenguaje independiente cada linea del fichero.
    void getLangVec(vector<Language> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4);
    // Escribe un vector de lenguajes en un fichero de salida.
    void writeLangVec(vector<Language> v, ofstream & out);
    // Escribe un vector de bool resultante de las operaciones igualdad y sublenguaje en un fichero.
    void writeBoolVec(vector<bool> ans_vec, ofstream & out);
};
