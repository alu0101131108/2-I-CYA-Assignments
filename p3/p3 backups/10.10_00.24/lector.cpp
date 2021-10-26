#include "lector.hpp"

void FileIO::storeInMatrix(vector<vector<string>> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4)
{
  string line, aux_str;
  vector<string> str_vec;

  while(!in.eof())
  {
    str_vec.clear();
    getline(in, line);     // example_line = "{ l, dk, fft ,sac, dsff, sadb,asdb ,asg}"

    for(int i = 0; i < line.size(); i++)  // Recorro line y si line[i] es un separador, reemplazarlo por un espacio.
      if(line[i] == sep1 || line[i] == sep2 || line[i] == sep3 || line[i] == sep4)
        line.replace(i, 1, 1, ' ');       // example_line = " l  dk  fft  sac  dsff  sadb asdb  asg"

    istringstream iss(line);

    if(line == "  ")             // Si hay un lenguaje vacío lo añade.
      v.push_back(str_vec);

    while(!iss.eof())
    {
      iss >> aux_str;
      str_vec.push_back(aux_str);
    }

    str_vec.pop_back();                         // Evita duplicado de último elemento.
    v.push_back(str_vec);
  }
  v.pop_back();                                 // Evita duplicado de último elemento.
}

void FileIO::getLangVec(vector<Language> & v, ifstream & in, char sep1, char sep2, char sep3, char sep4)
{
  v.clear();
  vector<vector<string>> aux_str_matrix;
  Language aux_lang;
  storeInMatrix(aux_str_matrix, in, sep1, sep2, sep3, sep4);  // Obtengo una matriz de string apartir del fichero.

  for(int i = 0; i < aux_str_matrix.size(); i++)              // Cada aux_str_matrix[i] será un vector de string, que será un lenguaje.
  {
    aux_lang.setLanguage(aux_str_matrix[i]);
    v.push_back(aux_lang);
  }
}

void FileIO::writeLangVec(vector<Language> v, ofstream & out)
{
  for(int i = 0; i < v.size(); i++)     // Recorro v y cada v[i] será un lenguaje.
  {
    if(!v[i].isInfinite())
    {
      out << "{";
      for(int j = 0; j < v[i].getv().size(); j++) // Recorro cada lenguaje. v[i].getv()[j] será la cadena j del lenguaje i.
      {
        out << v[i].getv()[j];
        if(j != v[i].getv().size() - 1)
          out << ", ";
      }
      out << "}\n";
    }
    else
    {
      out << "{";
      for(int j = 0; j < 10; j++)
      {
        out << v[i].getv()[j];
        if(j != 9)
          out << ", ";
      }
      out << " ..." << endl;
    }
  }
}
