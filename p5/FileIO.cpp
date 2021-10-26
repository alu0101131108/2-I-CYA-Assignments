#include "FileIO.hpp"

void FileIO::getLineVector(vector<string> & str_v, ifstream & in)
{
  string aux_str;
  while(!in.eof())
  {
    in >> aux_str;
    str_v.push_back(aux_str);
  }
  str_v.pop_back();               // Corrige un error que añade un elemento de más al vector.
}

void FileIO::writeLineVector(const vector<string>  str_v, ofstream & out)
{
  for(int i = 0; i < str_v.size(); i++)
  {
    out << str_v[i] << endl;
  }
}
