#include "lector.cpp"
#include <stdlib.h>
//#include "calculadora.cpp"

int main(int argc, char** argv)
{
  ifstream in;
  vector<Language> v;
  FileIO inFile(argv[1]);

  in.open(inFile.getFilename());

  inFile.getLangVec(v, in, ',', ' ', '{', '}');

  /*//EE ESTO ESCRIBE EL VECTOR DE LENGUAJES.
  cout << "Tus lenguajes son: " << endl;
  for(int i = 0; i < v.size(); i++)
    v[i].print(cout);
  cout << endl;*/


  int code_int = atoi(argv[3]);         // Convierte char* a  int.
  Calculator calculadora(v, code_int);

  if(code_int == 8)
  calculadora.setExp(atoi(argv[4]));


// calculadora.op_concatenacion(v[0], v[1]).print(cout);
// calculadora.op_potencia(v[5], 10).print(cout);
// calculadora.op_union(v[0], v[1]).print(cout);
// calculadora.op_interseccion(v[0], v[1]).print(cout);
// cout << calculadora.op_sublenguaje(v[5], v[4]) << " " << calculadora.op_sublenguaje(v[4], v[5]) << endl;
// cout << calculadora.op_igualdad(v[5], v[5]) << " " << calculadora.op_igualdad(v[5], v[4]) << endl;
// calculadora.op_diferencia(v[0], v[1]).print(cout);
// calculadora.op_inversa(v[0]).print(cout);
// calculadora.op_cierre_pos(v[3]).print(cout);
// calculadora.op_cierre_kleene(v[3]).print(cout);

/*for(int i=0; i<6; i++)
  calculadora.op_cierre_pos(v[i]).print(cout);
cout << endl;*/
/*for(int i=0; i<6; i++)
  calculadora.op_cierre_kleene(v[i]).print(cout);
*/
  vector<Language> lv;
  vector<bool> bool_v;

  if(code_int >= 1 && code_int <= 10 && code_int != 5 && code_int != 6)
  {
    lv = calculadora.codeOperation();

    for(int i=0; i<lv.size(); i++)
      lv[i].print(cout);
  }

  else if(code_int == 5 || code_int == 6)
  {
    bool_v = calculadora.codeOperation_bool();

    for(int i=0; i<bool_v.size(); i++)
      cout << bool_v[i] << endl;
  }

  in.close();

  ofstream out;
  FileIO outFile(argv[2]);
  out.open(outFile.getFilename());

  outFile.writeLangVec(lv, out);

  out.close();

// y conseguir volcar el vector de soluciones ya sea de lenguaje o bool en un fichero de salida.
// comprobar que cadenas no llevan &
  return 0;
}
