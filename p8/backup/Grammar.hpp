#include "Nfa.cpp"
#include "NTSymbol.cpp"

using namespace std;

class Grammar
{
  private:
    set<string> alphabet;
    set<NTSymbol> NTSymbols;
    NTSymbol init_NTSymbol;
    string void_label = "~";

    bool belong(string id, set<NTSymbol> container);
    string setToString(set<string> container);

  public:
    Grammar()
    {}
    Grammar(string filename)
    {
      readFromFile(filename);
    }

    Nfa convertToNFA();
    void readFromFile(string filename);
    void print(ostream & os);
    
};
