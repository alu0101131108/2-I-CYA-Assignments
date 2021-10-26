#include "FileIO.cpp"
#include "ER2tree.cpp"

string width(string data, int width)                                      // Se utiliza para alinear la tabla de resultados en el outfile.
{
  int realwidth = width - data.size();
  string aux(realwidth, ' ');
  return aux;
}

int main(int argc, char** argv)
{
  if(argc != 3)                                                           // Texto de ayuda.
    cout << "El ejecutable se usa de la forma ./ER2Tree 'nombre_entrada.txt' 'nombre_salida.txt'" << endl;

  else
  {
    const int TEXT_WIDTH = 20;

    ifstream in;                                                          // Comienzo de lectura.
    FileIO inFile(argv[1]);
    in.open(inFile.getFilename());
    vector<string> infix;
    inFile.getLineVector(infix, in);
    in.close();                                                           // Fin de lectura.


    ER2tree translator;                                                   // Comienza el proceso de información.
    int ER_num = infix.size();                                            // Representa el número de expresiones regulares a analizar.

    vector<string> prefix, postfix;                                       // Estos vectores contendrán las ER en notacion prefija y postfija.
    postfix.resize(ER_num);
    prefix.resize(ER_num);
    vector<int> nodesOnTree;                                              // Este vector contendrá el número de nodos que conforman el arbol asociado a cada ER.
    nodesOnTree.resize(ER_num);
    vector<vector<Node>> treeNodes;                                       // Cada vector de nodos se utilizará para la creación del arbol asociado a cada ER.
    treeNodes.resize(ER_num);                                             // El último elemento (nodo) de cada vector de nodos, representará al nodo padre del arbol asociado a cada ER.

    for(int i = 0; i < ER_num; i++)                                       // Al final de este bucle se habrán rellenado los tres vectores recién creados.
    {
      translator.infixToPostfix(postfix[i], infix[i]);                    // postfix[i] se rellena con infix[i] en notacion postfija.
      treeNodes[i].resize(postfix[i].size());                             // Se utiliza un vector de nodos, del mismo tamaño que postfix[i]. Este se reorganizará para
      translator.makeTree(postfix[i], treeNodes[i]);                      // formar el arbol asociado a postfix[i]. treeNodes[i][postfix[i].size()-1] será el nodo padre.
      nodesOnTree[i] = treeNodes[i][postfix[i].size() - 1].nodeCount();   // Se realiza el conteo de nodos que contiene el arbol asociado a postfix[i].
      treeNodes[i][postfix[i].size() - 1].getPrefix(prefix[i]);           // Apartir del arbol asociado a postfix[i], se obtiene la expresion en notacion prefija.
    }                                                                     // Fin del proceso de información.


    ofstream out;                                                         // Comienza la escritura.
    FileIO outFile(argv[2]);
    out.open(outFile.getFilename());
    vector<string> out_text;                                              // Cada elemento estará formado por infix[i], prefix[i], postfix[i] y nodesOnTree[i].
                                                                          // Y cada elemento representará la linea i del outfile.
    for(int i = 0; i < ER_num; i++)
      out_text.push_back(infix[i] + width(infix[i], TEXT_WIDTH) + postfix[i] + width(postfix[i], TEXT_WIDTH) + prefix[i] + width(prefix[i], TEXT_WIDTH) +  to_string(nodesOnTree[i]));

    outFile.writeLineVector(out_text, out);
    out.close();                                                          // Fin de la escritura.
  }
  return 0;
}
