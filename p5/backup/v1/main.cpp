#include "FileIO.cpp"
#include "ER2tree.cpp"

int main(int argc, char** argv)
{
  /*ifstream in;                        // Comienzo de lectura.
  FileIO inFile(argv[1]);
  in.open(inFile.getFilename());
  vector<string> infixRE;             // El vector infixRE contendrá cada ER a traducir.
  inFile.getLineVector(infixRE, in);
  in.close();                         // Fin de lectura.

  ER2tree translator;                                     // Comienzo del proceso.

  vector<string> postfixRE;                               // postfixRE contendrá los elementos de infixRE en notacion postfija.
  postfixRE.resize(infixRE.size());
  vector<string> prefixRE;                                // prefixRE contendrá los elementos de infixRE en notacion prefija.
  prefixRE.resize(infixRE.size());
  vector<int> nodesOnTree;                                // nodesOnTree contendrá el número de nodos que contiene el arbol asociado a cada elemento de infixRE.
  nodesOnTree.resize(infixRE.size());
  vector<vector<Node>> treeNodes;                         // treeNodes[i] será un vector de nodos, del mismo tamaño que postfixRE[i].
                                                          // Estos se reorganizarán luego para la construcción de cada arbol.
  for(int i = 0; i < infixRE.size(); i++)
  {
    translator.infixToPostfix(postfixRE[i], infixRE[i]);
    translator.makeTree(postfixRE[i], treeNodes[i]);
    nodesOnTree[i] = treeNodes[i][postfixRE[i].size() - 1].nodeCount();  // treeNodes[i][postfixRE[i].size() - 1] es el nodo padre del arbol asociado a postfixRE[i].
    treeNodes[i][postfixRE[i].size() - 1].getPrefix(prefixRE[i]);

  }
*/



/* ESTO COMPRUEBA placeConcat().
  ER2tree trad;
  string str = "(a|b)(a|c*)";
  trad.placeConcat(str);
  cout << str << endl;
*/

/* ESTO COMPRUEBA LA CREACION DEL ARBOL Y EL PASO A PREFIX.
  ER2tree trad;
  string str = "ab|*x&z*&", prefix;
  Node aux_node('$');
  vector<Node> node_vector(str.size(), aux_node);
  trad.makeTree(str, node_vector);
  cout << node_vector[str.size() - 1].nodeCount() << endl;
  node_vector[str.size() - 1].print(cout);
  cout << endl << "forma infija: ";
  node_vector[str.size() - 1].getPrefix(prefix);
  cout << prefix << endl;
*/

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

/* ESTO TRADUCE UN STRING DE INFIX A POSTFIX con placeConcat y todo.
string s = "(a|b)*xz*";
string r;
ER2tree trad;
trad.infixToPostfix(r, s);
cout << s << "      " << r << endl;
*/

/* essto es un copiasion
char x;
// Node* node_pointer;
v.resize(postfix.size());
vector<Node*> vp;
vp.resize(postfix.size());
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
