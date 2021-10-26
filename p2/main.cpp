// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 2 CyA - Analizador de textos
// Autor: Sebastián Daniel Tamayo Guzmán
// Correo: alu0101131108@ull.edu.es
// Fecha: 2/10/2019
// Enunciado de la práctica:
// https://campusvirtual.ull.es/1920/pluginfile.php/147981/mod_assign/introattachment/0/CYA_1920_Practica_2.pdf?forcedownload=1

#include "analiza.cpp"

int main(int argc, char** argv)
{
  if(argc == 1)
    cout << "El ejecutable ha de abrirse de la forma: \n./Analiza 'nombre_entrada.txt' 'nombre_salida.txt'.\n";

  else
  {
    ifstream in;
    ofstream out;

    Token aux_token;
    vector<Token> token_vector;

    in.open(argv[1]);
    out.open(argv[2]);
    assert(in.is_open() && out.is_open());

    while(!in.eof())                              // Leo todas las palabras del archivo en formato token
    {                                             // y estos los almaceno en un vector de tokens.
      aux_token.read(in);
      token_vector.push_back(aux_token);
    }
    // Elimino útimo elemento del vector para
    token_vector.pop_back();                      // evitar duplicación de la última palabra.

    for(int i = 0; i < token_vector.size(); i++)  // Recorro el vector clasificando y escribiendo cada token.
    {
      token_vector[i].clasify();
      token_vector[i].write(out);
    }

    in.close();
    out.close();
  }
  
  return 0;
}
