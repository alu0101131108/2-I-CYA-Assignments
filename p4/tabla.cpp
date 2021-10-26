#include "tabla.hpp"

int Tabla::asociado(int estado, char caracter)
{
  int char_id = -1;

  for(int i = 0; i < caracteres.size(); i++)    // Si encuentra el caracter, lo asocia a su índice en la tabla.
    if(caracteres[i] == caracter)
      char_id = i;

  if(char_id == -1)                             // Si no lo encuentra, se toma como other (última columna).
    char_id = caracteres.size();

  return asociados[estado][char_id];
}
