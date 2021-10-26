#include "DFA.hpp"

void DFA::readFromFile(ifstream & ifs)
{
  string line, text;                          // Convierte el archivo de entrada en un string.
  while(!ifs.eof())                           // Ignora las lineas que correspondan a comentarios.
  {
    getline(ifs, line);
    if(line[0] != '/' && line[1] != '/')
      text = text + line + "\n";
  }

  stringstream in(text);                      // Se analiza el text "descomentado".
  string aux, qi, sim, qf;
  int size;

  in >> aux;                                  // (1) Alfabeto.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    for(int j = 0; j < aux.size(); j++)
      assert(aux[j] != ' ' && aux[j] != '\n');
    Alphabet.insert(aux);
  }
  //cout << "Alfabeto leido." << endl;

  in >> aux;                                  // (2) Estados.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    assert(syntaxOk(aux));
    Q.insert(aux);
  }
  //cout << "Estados leidos." << endl;

  in >> aux;                                  // (3) Estado inicial.
  assert(belong(aux, Q));
  Qo = aux;
  //cout << "Estado inicial leido." << endl;

  in >> aux;                                  // (4) Estados finales o de aceptación.
  size = stoi(aux);
  for(int i = 0; i < size; i++)
  {
    in >> aux;
    assert(belong(aux, Q));
    F.insert(aux);
  }
  //cout << "Estados finales leidos." << endl;

  in >> aux;                                  // (5) Transiciones.
  size = stoi(aux);
  Transition.initializeEmpty(Q, Alphabet);
  for(int i = 0; i < size; i++)
  {
    in >> qi;
    in >> sim;
    in >> qf;
    assert(belong(qi, Q) && belong(sim, Alphabet) && belong(qf, Q));
    Transition.define(qi, sim, qf);
  }
  //cout << "Transiciones leidas." << endl;
}

bool DFA::belong(string element, set<string> container)
{
  return container.find(element) != container.end();
}

bool DFA::syntaxOk(string aux)
{
  bool ok = true;
  for(int j = 0; j < aux.size(); j++)
    if(!((aux[j] >= 'a' && aux[j] <= 'z') || (aux[j] >= 'A' && aux[j] <= 'Z') || (aux[j] >= '0' && aux[j] <= '9')))
      ok = false;
  return ok;
}

void DFA::displayInfo(ostream & out)
{
  out << "Σ:";
  for(auto it=Alphabet.begin(); it != Alphabet.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Q:";
  for(auto it=Q.begin(); it != Q.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Qo: " + Qo + "." << endl;

  out << "F:";
  for(auto it=F.begin(); it != F.end(); ++it)
    out << ' ' << *it;
  out << "." << endl;

  out << "Tabla de transición:" << endl;
  Transition.print(out);
}

void DFA::generateDotFile(ofstream & ofs)
{
  ofs << "digraph DFA {\n  rankdir = LR;\n  size = \"10, 4\";\n  d2tstyleonly = true;\n";
  ofs << "  node [shape = none]; \" \";\n";
  //ofs << "  node [shape = Mcircle]; " + deadStatesToString() + ";\n";
  ofs << "  node [shape = doublecircle]; " + finalStatesToString() + ";\n";
  ofs << "  node [shape = circle];\n";
  ofs << "  \" \" -> \"" + Qo + "\"\n";
  ofs << Transition.transitionsToString() + "}";
}

string DFA::finalStatesToString()
{
  string aux, result;
  for(auto elem : F)
  {
    aux = elem;
    aux = "\"" + aux + "\"";
    result += aux + " ";
  }
  return result;
}

string DFA::deadStatesToString()
{
	vector<string> deadStates = Transition.findDeadStates();
	string result;
	for(int i = 0; i < deadStates.size(); i++)
	{
		result = result + "\"" + deadStates[i] + "\" ";
	}
	return result;
}

void DFA::generateEspecification(ofstream & ofs)
{
  ofs << Alphabet.size() << endl;       // Número de símbolos del alfabeto.
  for(auto elem : Alphabet)             // Cada símbolo.
    ofs << elem << endl;
  ofs << Q.size() << endl;              // Número de estados.
  for(auto elem : Q)                    // Cada estado.
    ofs << elem << endl;
  ofs << Qo << endl;                    // Estado inicial.
  ofs << F.size() << endl;              // Número de estados finales.
  for(auto elem : F)                    // Cada estado final.
    ofs << elem << endl;
  vector<string> transitions = Transition.getTransitionVector();
  ofs << transitions.size() << endl;
  for(int i = 0; i < transitions.size(); i++)
    ofs << transitions[i] << endl;
}
