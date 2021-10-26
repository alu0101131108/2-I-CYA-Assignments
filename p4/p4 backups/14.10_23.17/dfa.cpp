#include "dfa.hpp"

void DFA::evento(char in)
{
  Qo = transicion.asociado(Qo, in);         // devuelve int (estado_id), asociado al estado Qo y char in.
}

boolean DFA::esEstadoAceptacion()
{
  if(F.find(Qo) == set::end)
    return false;
  else
    return true;
}
