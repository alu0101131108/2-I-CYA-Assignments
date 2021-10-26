#include <fstream>
#include <iostream>
#include <vector>

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

    void getLineVector(vector<string> & str_v, ifstream & in);
    void writeLineVector(const vector<string>  str_v, ofstream & out);
};
