using namespace std;
#include <vector>
#include <set>
#include <iostream>

class Language
{
  private:
    vector<string> lang_vec;
    set<char> alphabet;
    bool infinite = false;

  public:
    Language(vector<string> lang_v, vector<char> alpha): lang_vec(lang_v)
  {
    for(int i = 0; i < alpha.size(); i++)
      alphabet.insert(alpha[i]);
  }
    Language(vector<string> lang_v): lang_vec(lang_v)
  {
    for(int i = 0; i < lang_vec.size(); i++)
      for(int j = 0; j < lang_vec[i].size(); j++)   //Crea un alfabeto apartir del conjunto de cadenas que forman el lenguaje.
      {
        if(alphabet.find(lang_vec[i][j]) == alphabet.end())
          alphabet.insert(lang_vec[i][j]);
      }
  }
    Language()
    {}

    vector<string> getv()
    {
      return lang_vec;
    }
    void setInfinite()
    {
      infinite = true;
    }
    bool isInfinite()
    {
      return infinite;
    }

    void setLanguage(vector<string> lang_v);  // Modifica los atributos del lenguaje.
    void print(ostream & os);                 // Imprime por pantalla las cadenas válidas del lenguaje.

};
