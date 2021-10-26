#include "FileIO.cpp"
#include "ER2tree.cpp"

int main(int argc, char** argv)
{

/* ESTO COMPRUEBA placeConcat().
  ER2tree trad;
  string str = "(a|b)(a|c*)";
  trad.placeConcat(str);
  cout << str << endl;
*/

/* Esto genera infix prefix postfix y nodenum apartir de un vector creado infixRE y muestra la info por consola.
  vector<string> infixRE = {"(a|b)*xz*", "a|b", "a|bc", "(a|b)(c|d)"};

  ER2tree trad;

  int ER_num = infixRE.size();

  vector<string> postfixRE, prefixRE;
  postfixRE.resize(ER_num);
  prefixRE.resize(ER_num);
  vector<int> nodesOnTree;
  nodesOnTree.resize(ER_num);
  vector<vector<Node>> treeNodes;
  treeNodes.resize(ER_num);

  for(int i = 0; i < infixRE.size(); i++)
  {
    cout << "Cadena "<< i << ":"<< endl;

    trad.infixToPostfix(postfixRE[i], infixRE[i]);                      // postfix se rellena con las ER de infix en notacion postfija.

    treeNodes[i].resize(postfixRE[i].size());
    trad.makeTree(postfixRE[i], treeNodes[i]);

    nodesOnTree[i] = treeNodes[i][postfixRE[i].size() - 1].nodeCount();

    treeNodes[i][postfixRE[i].size() - 1].getPrefix(prefixRE[i]);

    cout << "Nodos: " << nodesOnTree[i] << endl;
    cout << "Infix: " << infixRE[i] << endl;
    cout << "Prefix: " << prefixRE[i] << endl;
    cout << "Postfix: " << postfixRE[i] << endl;

    cout << endl;
  }
// treeNodes[i][prefixRE[i].size()-1] es el nodo padre del arbol asociado a la cadena i.
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
