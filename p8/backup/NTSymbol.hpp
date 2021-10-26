#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

const string PROD_LABEL = "->";

class NTSymbol
{
  typedef pair<set<string>, string> production;

  private:
    string           id;           /**< Identificador del símbolo no terminal. */
    set<production>  productions;  /**< Conjunto de producciones asociadas al símbolo no terminal. */

    string setToString(set<string> container);

    /*bool isFinal(production prod)
    {
      if(prod.second != "$")
        return false;
      else
        return true;
    }*/

  public:
    NTSymbol()
    {}
    NTSymbol(string name): id(name)
    {}

    string getId()
    {
      return id;
    }
    void setId(string name)
    {
      id = name;
    }
    set<production> getProductions()
    {
      return productions;
    }

    void defineProduction(set<string> in_symbols, string final_ntsID);
    void print(ostream & os);

    bool operator<(const NTSymbol & a) const
    {
      return (this -> id)[0] < a.id[0];
    }
    bool operator==(const NTSymbol & a) const
    {
      return this -> id == a.id;
    }



};
