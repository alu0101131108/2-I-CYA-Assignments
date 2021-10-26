#include "lenguaje.hpp"

void Language::setLanguage(vector<string> lang_v)
{
  lang_vec.clear();                                     // Vacío los atributos.
  alphabet.clear();

  for(int i = 0; i < lang_v.size(); i++)                // Relleno lang_vec y creo un alfabeto aparti de su contenido.
  {
    lang_vec.push_back(lang_v[i]);
    for(int j = 0; j < lang_v[i].size(); j++)
    {
      if(alphabet.find(lang_v[i][j]) == alphabet.end())
        alphabet.insert(lang_v[i][j]);
    }
  }
}

void Language::print(ostream & os)                      // Imprime cada elemento del lenguaje.
{
  if(infinite)                                          // Si hay cadenas infinitas solo imprime las primeras 10.
  {
    os << "{";
    for(int i = 0; i < 10; i++)
    {
      os << lang_vec[i];
      if(i != 9)
        os << ", ";
    }
    os << " ..." << endl;
  }
  else
  {
    os << "{";
    for(int i = 0; i < lang_vec.size(); i++)
    {
      os << lang_vec[i];
      if(i != lang_vec.size()-1)
        os << ", ";
    }
    os << "}" << endl;
  }
}
