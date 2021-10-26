#include "lector.cpp"
#include <stdlib.h>

int main(int argc, char** argv)
{
  if(argc == 1)                                                                  // Texto de ayuda.
  {
    cout << "Este ejecutable se usa de la forma: ./exe 'nombre_";
    cout << "archivo_entrada.txt' 'nombre_archivo_salida.txt' 'código'\n\n";
    cout << "Operación asociada al código:" << endl;
    cout << "[1] :  Concatenación." << endl;
    cout << "[2] :  Unión." << endl;
    cout << "[3] :  Intersección." << endl;
    cout << "[4] :  Diferencia." << endl;
    cout << "[5] :  Sublenguajes." << endl;
    cout << "[6] :  Igualdad de lenguajes." << endl;
    cout << "[7] :  Inversa." << endl;
    cout << "[8] :  Potencia. (El exponente se indicará con un cuarto parámetro)" << endl;
    cout << "[9] :  Cierre Positivo." << endl;
    cout << "[10]:  Cierre de Kleene." << endl;
  }
  else
  {
    ifstream in;                                                                // Declaración de variables a usar.
    ofstream out;                                                               //
    vector<Language> lectura_lan_vec;                                           //
    vector<Language> ans_lan_vec;                                               //
    vector<bool> ans_bool_vec;                                                  //
    int code_int = atoi(argv[3]);                                               //
                                                                                //
    FileIO inFile(argv[1]);                                                     // COMIENZA LA LECTURA.
    in.open(inFile.getFilename());                                              //
    inFile.getLangVec(lectura_lan_vec, in, ',', ' ', '{', '}');                 // Obtengo un vector de lenguajes apartir del fichero de entrada.
    in.close();                                                                 // FIN DE LA LECTURA.
                                                                                //
    Calculator calculadora(lectura_lan_vec, code_int);                          // COMIENZA EL CÁLCULO dependiendo del código.
    if(code_int == 8)                                                           // Si la operación es la de potencia, se necesita un exponente.
      calculadora.setExp(atoi(argv[4]));                                        //
    if(code_int >= 1 && code_int <= 10 && code_int != 5 && code_int != 6)       // Operaciones con un lenguaje por resultado.
      ans_lan_vec = calculadora.codeOperation();                                //
    else if(code_int == 5 || code_int == 6)                                     // Operaciones con un valor booleano de resultado.
      ans_bool_vec = calculadora.codeOperation_bool();                          //
                                                                                // FIN DEL CÁLCULO.
                                                                                //
    FileIO outFile(argv[2]);                                                    // COMIENZA LA ESCRITURA.
    out.open(outFile.getFilename());                                            //
                                                                                //
    if(code_int >= 1 && code_int <= 10 && code_int != 5 && code_int != 6)       // Para operaciones con un lenguaje por resultado.
      outFile.writeLangVec(ans_lan_vec, out);                                   //
    else if(code_int == 5 || code_int == 6)                                     // Para operaciones con un valor booleano de resultado.
      outFile.writeBoolVec(ans_bool_vec, out);                                  //
                                                                                //
    out.close();                                                                // FIN DE LA ESCRITURA.
  }                                                                             //
  return 0;                                                                     //
}
