#include "analizador.hpp"

bool Analizador::checkSyntax(string aux_str)
{
  int estadoInicial = dfa.getEstado();
  for(int i = 0; i < aux_str.size(); i++)
    dfa.evento(aux_str[i]);
  return (estadoInicial == dfa.getEstado() || dfa.getEstado() == 1);          // Comprueba que tras analizar el texto, el últmo estado sea NONE o SLASH.
}

void Analizador::borrarComentarios(string & aux_str)
{
  enum estadosID {NONE, SLASH, CPP, C, STAR};
  if(checkSyntax(aux_str))
  {
    int preEvent;
    string buffer;
    for(int i = 0; i < aux_str.size(); i++)
    {
      preEvent = dfa.getEstado();       // Estado anterior.
      dfa.evento(aux_str[i]);
      switch (dfa.getEstado())          // Estado posterior.
      {
        case NONE:
          if(preEvent == NONE || preEvent == SLASH || preEvent == CPP)        // Se copian los char[i] al buffer puesto que no son parte de un comentario.
            buffer.push_back(aux_str[i]);
        break;

        case SLASH:
          buffer.push_back(aux_str[i]);                                       // Se copia una '/'. Si forma parte de un comentario será borrada.*
        break;

        case CPP:
          if(preEvent == SLASH)                                               // *Borra la primera '/' del comentario.
            buffer.pop_back();
        break;

        case C:
          if(preEvent == SLASH)                                               // *Borra la primera '/' del comentario.
            buffer.pop_back();
        break;
      }
    }
    aux_str = buffer;                                                         // Vuelco el buffer en el string original.
  }
  else
    cout << endl << "Sintaxis incorrecta" << endl;                // En caso de que el texto finalice con un comentario no cerrado.
}
