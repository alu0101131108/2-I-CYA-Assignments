#include "FileIO.cpp"
#include "ER2tree.cpp"

int main(int argc, char** argv)
{

  ER2tree trad;
  string str = "ab|*x&z*&";
  Node aux_node('$');
  //cout << aux_node.nodeCount() << endl;
  trad.makeTree(str, aux_node);
  //cout << aux_node.nodeCount() << endl;
  aux_node.print(cout);



/* ESTO COMPRUEBA QUE LA CLASE NODE Y NODECOUNT FUNCIONAN BIEN.
  Node node1('a'), node2('a'), node3('a');
  Node* n1 = & node1;
  Node* n2 = & node2;
  Node node4('a', n1, n2);
  Node* n3 = & node3;
  Node node5('a', n3);
  Node* n4 = & node4;
  Node* n5 = & node5;
  Node node6('a', n4, n5);

  node6.print(cout);
  int n = node6.nodeCount();
  cout << "Numero de nodos: " << n << endl;
*/

/* ESTO TRADUCE UN STRING DE INFIX A POSTFIX
stack<char> stak1;
string s = "(a|b)*&x&z*";
string r;
ER2tree trad(stak1);
trad.infixToPostfix(r, s);
cout << s << "      " << r << endl;
*/

/* ESTO LEE EL FICHERO ENTRADA LO GUARDA COMO VECTOR DE STRING Y LO ESCRIBE TAL CUAL EN FICHERO SALIDA.
  vector<string> string_vector;

  ifstream in;
  FileIO inFile(argv[1]);
  in.open(inFile.getFilename());
  inFile.getLineVector(string_vector, in);
  in.close();

  ofstream out;
  FileIO outFile(argv[2]);
  out.open(outFile.getFilename());
  outFile.writeLineVector(string_vector, out);
  out.close();
*/

  return 0;
}
