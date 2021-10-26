#include "fileIO.cpp"

int main(int argc, char** argv)
{
  enum estadosID {NONE, SLASH, CPP, C, STAR};           // Serán las filas de la tabla de transicion.
  vector<char> caracteres = {'/', '*', '\n'};           // Serán las columnas de la tabla, añadiendo el caso other.

  vector<vector<int>> tabla_transicion;
  tabla_transicion.resize(5);

  for(int i = 0; i < tabla_transicion.size(); i++)
    tabla_transicion[i].resize(4);

  tabla_transicion[0] = {SLASH, NONE, NONE, NONE};
  tabla_transicion[1] = {CPP  , C   , NONE, NONE};
  tabla_transicion[2] = {CPP  , CPP , NONE, CPP };
  tabla_transicion[3] = {C    , STAR, C   , C   };
  tabla_transicion[4] = {NONE , STAR, C   , C   };

  string aux_str;
  string texto;

  ifstream in;                            // Inicio de lectura.
  in.open(argv[1]);
  while(!in.eof())
  {
    getline(in, aux_str);
    texto = texto + aux_str + "\n";
  }
  in.close();                             // Fin de lectura.

// Recorrer texto y analizar con autómata. Usar getEstado() para almacenar el estado anterior y el actual.
// Dependiendo de esos dos estados, se borrará o no lo que se considere comentarios. El dfa ha de empezar y terminar en Qo. (el inicial).



  ofstream out;                           // Inicio de escritura.
  out.open(argv[2]);
  for(int i = 0; i < texto.size(); i++)
    out << texto[i];
  out.close();                            // Fin de escritura.

  return 0;
}
