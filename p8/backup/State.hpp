#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <utility>
#include <sstream>
#include <cassert>

using namespace std;

class State
{
  typedef pair<string, State> transition;

  private:
    string           id;           /**< Identificador o nombre del estado. */
    set<transition>  transitions;  /**< Conjunto de transiciones asociadas al estado. */

  public:
    State()
    {}
    State(string name): id(name)
    {}

    set<transition> getTransitions()
    {
      return transitions;
    }


};
