#include "dfa.hpp"
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

};
