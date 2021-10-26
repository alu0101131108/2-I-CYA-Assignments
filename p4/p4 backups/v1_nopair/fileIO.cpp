#include "fileIO.hpp"

string FileIO::getTextAsString(ifstream & in)
{
  string aux_str;
  string texto;
  while(!in.eof())
  {
    getline(in, aux_str);
    texto = texto + aux_str + "\n";
  }
  return texto;
}

void FileIO::writeString(ofstream & out, string texto)
{
  for(int i = 0; i < texto.size(); i++)
    out << texto[i];
}
