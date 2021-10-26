#include "fileIO.cpp"

int main(int argc, char** argv)
{

  FileIO inFile(argv[1]);                 // Comienzo de la lectura.
  ifstream in;
  in.open(inFile.getFilename());
  string texto = inFile.getTextAsString(in);
  in.close();                             // Fin de lectura.

  enum estadosID {NONE, SLASH, CPP, C, STAR};           // Corresponde a las filas de la tabla de transicion.
  vector<char> caracteres = {'/', '*', '\n'};           // Corresponde a las columnas de la tabla, añadiendo el caso other.

  vector<int> aux_v(4, -1);
  vector<vector<int>> tabla_transicion(5, aux_v);
  tabla_transicion[0] = {SLASH, NONE, NONE, NONE};
  tabla_transicion[1] = {CPP  , C   , NONE, NONE};
  tabla_transicion[2] = {CPP  , CPP , NONE, CPP };
  tabla_transicion[3] = {C    , STAR, C   , C   };
  tabla_transicion[4] = {NONE , STAR, C   , C   };

  Tabla tablaDetectorComentarios(caracteres, tabla_transicion);   //Inicio de análisis.
  DFA detectorComentarios({NONE, SLASH, CPP, C, STAR}, NONE, {NONE}, tablaDetectorComentarios);
  Analizador analizaComentarios(detectorComentarios);
  analizaComentarios.borrarComentarios(texto);                    // Fin de análisis.


  FileIO outFile(argv[2]);                // Inicio de escritura.
  ofstream out;
  out.open(outFile.getFilename());
  outFile.writeString(out, texto);
  out.close();                            // Fin de escritura.

  return 0;
}
