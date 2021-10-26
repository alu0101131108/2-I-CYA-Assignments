#include "analizador.hpp"

bool Analizador::checkSyntax(string aux_str)
{
  int estadoInicial = dfa.getEstado();
  for(int i = 0; i < aux_str.size(); i++)
    dfa.evento(aux_str[i]);
  return estadoInicial == dfa.getEstado();
}

void Analizador::borrarComentarios(string & aux_str)
{
  if(checkSyntax(aux_str))
  {
    bool preEventoAceptacion, preEventoEspecial;
    int estadoPreEvento;

    for(int i = 0; i < aux_str.size(); i++)
    {
      preEventoAceptacion = dfa.estadoAceptacion();         // Si el anterior estado es de aceptacion.
      preEventoEspecial = dfa.casoEspecial(aux_str[i]);     // Si la última transicion es un caso especial.

      dfa.evento(aux_str[i]);

      if(dfa.estadoAceptacion() == true)                    // Si el dfa está en un estado de aceptacion.
      {
        if(preEventoAceptacion == false)                    // Si el anterior estado no es de aceptación.
        {
          aux_str.replace(i, 1, 1, ' ');                                 // Borra la segunda barra o asterisco (/*) del comentario.
          aux_str.replace(i - 1, 1, 1, ' ');                             // Borra la primera barra del comentario.
        }
        else
          aux_str.replace(i, 1, 1, ' ');                                 // Dentro de un comentario.
      }
      else if(preEventoEspecial)
        aux_str.replace(i, 1, 1, ' ');                                   // Caso especial. Sale de comentario de STAR a NONE pero borra la última "/".
    }
  }
  else
    cout << endl << "Sintaxis incorrecta" << endl;
}
