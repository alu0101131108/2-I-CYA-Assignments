#include "dfa.hpp"

void DFA::evento(char in)                           // Establece Qo al int (estado_id), asociado al estado actual con entrada char in.
{
  Qo = get<0>(transicion.asociado(Qo, in));
}

bool DFA::estadoAceptacion()                     // Devuelve un booleano que indica si el dfa se encuentra en un estado de aceptacion.
{
  if(F.find(Qo) == F.end())
    return false;
  else
    return true;
}

bool DFA::casoEspecial(char in)                  // Devuelve un booleano que indica si el .evento(in) será un caso especial.
{
  return get<1>(transicion.asociado(Qo, in));
}
