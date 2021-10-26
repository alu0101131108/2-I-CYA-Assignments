#include "analizador.hpp"

void Analizador::borrarComentarios(string & aux_str)
{
  //Acceso a mi dfa -> .evento(char in), .getEstado();
  //Acceso a string aux_string.

  int estadoPreEvento, estadoPostEvento;
  for(int i = 0; i < aux_str.size(); i++)
  {
    estadoPreEvento = dfa.getEstado();
    dfa.evento(aux_str[i]);

    if(!dfa.esEstadoAceptacion() && F.find(estadoPreEvento != set::end)
    {
      aux_str[i] = " ";
      if(estadoPreEvento == 1)
    }
  }

}
