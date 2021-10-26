//#include "analizador.cpp"
#include "dfa.cpp"

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

    string getTextAsString(ifstream & in);
    void writeString(ofstream & out, string texto);
};
