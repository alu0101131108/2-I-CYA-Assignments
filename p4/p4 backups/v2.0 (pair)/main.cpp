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

  vector<pair<int, bool>> aux_v(4, make_pair(-1, false));       // El valor booleano indica si es un caso especial.
  vector<vector<pair<int, bool>>> tabla_transicion(5, aux_v);   // Se diferencian dos casos en los que pasa de estadofinal a estadofinal.
                                                                // Y otros dos en los que pasa de final a nofinal. SLASH -> CPP || C

  // Se rellena la tabla de acuerdo a la funcionalidad del DFA.                                                                
  tabla_transicion[0] = {make_pair(SLASH, false), make_pair(NONE, false), make_pair(NONE, false), make_pair(NONE, false)};
  tabla_transicion[1] = {make_pair(CPP  , false), make_pair(C   , false), make_pair(NONE, false), make_pair(NONE, false)};
  tabla_transicion[2] = {make_pair(CPP  , false), make_pair(CPP , false), make_pair(NONE, false), make_pair(CPP , false)};
  tabla_transicion[3] = {make_pair(C    , false), make_pair(STAR, false), make_pair(C   , false), make_pair(C   , false)};
  tabla_transicion[4] = {make_pair(NONE , true) , make_pair(STAR, false), make_pair(C   , false), make_pair(C   , false)};

  Tabla tablaDetectorComentarios(caracteres, tabla_transicion);   //Inicio de análisis.
  DFA detectorComentarios({NONE, SLASH, CPP, C, STAR}, NONE, {CPP, C, STAR}, tablaDetectorComentarios);
  Analizador analizaComentarios(detectorComentarios);
  analizaComentarios.borrarComentarios(texto);                    // Fin de análisis.


  FileIO outFile(argv[2]);                // Inicio de escritura.
  ofstream out;
  out.open(outFile.getFilename());
  outFile.writeString(out, texto);
  out.close();                            // Fin de escritura.

  return 0;
}
