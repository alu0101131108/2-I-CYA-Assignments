#include "analizador.cpp"

using namespace std;

class FileIO
{
  private:

    string filename;

  public:

    FileIO(string name):
    filename(name)
    {}

    string getFilename()
    {
      return filename;
    }

    string getTextAsString(ifstream & in);              // Devuelve un solo string que contiene todo el fichero de entrada.
    void writeString(ofstream & out, string texto);     // Escribe un string en un fichero de texto de salida.
};
