#include "dfa.hpp"

void DFA::evento(char in)                           // Establece Qo al int (estado_id), asociado al estado actual con entrada char in.
{
  Qo = transicion.asociado(Qo, in);
}

bool DFA::estadoAceptacion()                        // Devuelve un booleano que indica si el dfa se encuentra en un estado de aceptacion.
{
  if(F.find(Qo) == F.end())
    return false;
  else
    return true;
}
