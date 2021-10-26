#include "analizador.hpp"

bool Analizador::checkSyntax(string aux_str)
{
  int estadoInicial = dfa.getEstado();
  for(int i = 0; i < aux_str.size(); i++)
    dfa.evento(aux_str[i]);
  return (estadoInicial == dfa.getEstado() || dfa.getEstado() == 1);
}

void Analizador::borrarComentarios(string & aux_str)
{
  if(checkSyntax(aux_str))
  {
    int init, preEvent, postEvent;
    for(int i = 0; i < aux_str.size(); i++)                       // Analizaré el estado anterior y posterior a cada evento(aux_str[i]).
    {
      preEvent = dfa.getEstado();
      dfa.evento(aux_str[i]);
      postEvent = dfa.getEstado();

      if(preEvent == 1 && postEvent != 0)                         // Si pasa de SLASH a CPP o C.
        init = i - 1;                                             // init guardará el indice del primer char de un comentario.
      else if(preEvent == 2 && postEvent == 0)                    // Si pasa de CPP a NONE.
        aux_str.replace(init, i - init, i - init, ' ');           // Los char del comentario serán espacios y se conservará el '\n' de cierre.
      else if(preEvent == 4 && postEvent == 0)                    // Si pasa de C a NONE.
        aux_str.replace(init, i - init + 1, i - init + 1, ' ');   // Los char del comentario serán espacios y no se conservará la '/' de cierre.
    }
  }
  else
    cout << endl << "Sintaxis incorrecta" << endl;                // En caso de que el texto finalice con un comentario no cerrado.
}
