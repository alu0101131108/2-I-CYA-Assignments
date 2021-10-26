#include "DFA.cpp"

int main(int argc, char** argv)
{
  ifstream in;
  in.open(argv[1]);
  DFA dfa1;
  dfa1.readFromFile(in);
  in.close();

  dfa1.displayInfo(cout);

  return 0;
}
