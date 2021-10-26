// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia (CyA)
// Curso: 2º
// Práctica 2 CyA - Analizador de textos
// Autor: Sebastián Daniel Tamayo Guzmán
// Correo: alu0101131108@ull.edu.es
// Fecha: 2/10/2019
// Enunciado de la práctica:
// https://campusvirtual.ull.es/1920/pluginfile.php/147981/mod_assign/introattachment/0/CYA_1920_Practica_2.pdf?forcedownload=1

#include <iostream>
#include <fstream>
#include <set>
#include <cassert>
#include <ctype.h>
#include <vector>

#include "analiza.hpp"

set<string> especiales = {"abstract", "assert", "boolean", "break", "byte", "case", "catch", "char", "class", "const", "continue", "default", "do", "double", "else", "enum", "extends", "final", "finally", "float", "for", "goto", "if", "implements", "import", "instanceof", "int", "interface", "long", "native", "new", "package", "private", "protected", "public", "return", "short", "static", "strictfp", "super", "switch", "synchronized", "this", "throw", "throws", "transient", "try", "void", "volatile", "while"};
set<string> operadores = {"+", "-", "*", "/", "=", "<", ">", "<=", ">=", "!="};
set<string> signos = {"(", ")", "[", "]", ".", "{", "}", ";", ","};

void Token::clasify()
{
  if(especiales.find(lexema_) != especiales.end())        // Verifica si el lexema es una palabra especial.
    setType(1);

  else if(operadores.find(lexema_) != operadores.end())   // Verifica si el lexema es un operador. (OP)
    setType(5);

  else if(signos.find(lexema_) != signos.end())           // Verifica si el lexema es un signo. (SIG)
    setType(6);

  else if(isdigit(lexema_[0]) != 0 && isdigit(lexema_[lexema_.size()-1]) != 0)  // Verifica que el primer y ultimo
  {                                                                             // caracter del lexema sean dígitos.
    int digits = 0;
    int dotchars = 0;
    for(int i = 0; i < lexema_.size(); i++)               // Cuento cuantos dígitos y cuantos char '.' tiene el lexema.
    {
      if(isdigit(lexema_[i]) != 0)
        digits++;
      if(lexema_[i] == '.')
        dotchars++;
    }
    if(dotchars == 1 && digits == lexema_.size() - 1)     // Verifica que haya solo un '.' y el resto sean dígitos. (FLOT)
      setType(4);
    if(digits == lexema_.size())                          // Verifica que todos los caracteres sean dígitos. (INT)
      setType(3);
  }

  else if(isalpha(lexema_[0]) != 0)                       // Verifica que el primer caracter sea alfabético
  {                                                       // y que el resto de caracteres sean alfanuméricos.
    bool is_pal = true;
    for(int i = 1; i < lexema_.size(); i++)
    {
      if(isalnum(lexema_[i]) == 0)
        is_pal = false;
    }
    if(is_pal)
      setType(2);
  }
  else
    setType(0);                                           // (DESCONOCIDA)
}

void Token::write(ofstream & out)
{
  switch(type_)
  {
    case 0:                                     // Palabras desconocidas.
      out << "DESCONOCIDA " << lexema_ << endl;
      break;

    case 1:                                     // Palabras especiales.
      out << lexema_ << endl;
      break;

    case 2:                                     // Palabras no especiales.
      out << "PAL " << lexema_ << endl;
      break;

    case 3:                                     // Números enteros.
      out << "INT " << lexema_ << endl;
      break;

    case 4:                                     // Números en punto flotante.
      out << "FLOT " << lexema_ << endl;
      break;

    case 5:                                     // Operadores.
      out << "OP " << lexema_ << endl;
      break;

    case 6:                                     // Signos.
      out << "SIG " << lexema_ << endl;
      break;
  }
}

void Token::read(ifstream & in)                 // Asigna una palabra leida del fichero
{                                               // al atributo lexema_ del token invocante.
  string aux_str;
  in >> aux_str;
  setLexema(aux_str);
}
