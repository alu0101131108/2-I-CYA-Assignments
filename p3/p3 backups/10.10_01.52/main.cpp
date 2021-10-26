#include "lector.cpp"
#include <stdlib.h>

int main(int argc, char** argv)
{
  ifstream in;                                                                  // Declaración de variables a usar.
  ofstream out;                                                                 //
  vector<Language> lectura_lan_vec;                                             //
  vector<Language> ans_lan_vec;                                                 //
  vector<bool> ans_bool_vec;                                                    //
  int code_int = atoi(argv[3]);                                                 //
                                                                                //
  FileIO inFile(argv[1]);                                                       // COMIENZA LA LECTURA.
  in.open(inFile.getFilename());                                                //
  inFile.getLangVec(lectura_lan_vec, in, ',', ' ', '{', '}');                   // Obtengo un vector de lenguajes apartir del fichero de entrada.
  in.close();                                                                   // FIN DE LA LECTURA.
                                                                                //
  Calculator calculadora(lectura_lan_vec, code_int);                            // COMIENZA EL CÁLCULO dependiendo del código.
  if(code_int == 8)                                                             // Si la operación es la de potencia, se necesita un exponente.
    calculadora.setExp(atoi(argv[4]));                                          //
  if(code_int >= 1 && code_int <= 10 && code_int != 5 && code_int != 6)         // Operaciones con un lenguaje por resultado.
    ans_lan_vec = calculadora.codeOperation();                                  //
  else if(code_int == 5 || code_int == 6)                                       // Operaciones con un valor booleano de resultado.
    ans_bool_vec = calculadora.codeOperation_bool();                            //
                                                                                // FIN DEL CÁLCULO.
                                                                                //
  FileIO outFile(argv[2]);                                                      // COMIENZA LA ESCRITURA.
  out.open(outFile.getFilename());                                              //
                                                                                //
  if(code_int >= 1 && code_int <= 10 && code_int != 5 && code_int != 6)         // Para operaciones con un lenguaje por resultado.
    outFile.writeLangVec(ans_lan_vec, out);                                     //
  else if(code_int == 5 || code_int == 6)                                       // Para operaciones con un valor booleano de resultado.
    outFile.writeBoolVec(ans_bool_vec, out);                                    //
                                                                                //
  out.close();                                                                  // FIN DE LA ESCRITURA.
                                                                                //
                                                                                // Falta comprobar que cadenas no llevan &
  return 0;                                                                     //
}
