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

using namespace std;

class Token
{
  private:
    string lexema_;
    int type_;

  public:
    Token(): lexema_(" "), type_(0)
    {}

    Token(string lexema): lexema_(lexema), type_(0)
    {}

    Token(string lexema, int type): lexema_(lexema), type_(type)
    {}

    void setLexema(string lexema)
    {
      lexema_ = lexema;
    }

    void setType(int type)
    {
      type_ = type;
    }

    string getLexema()
    {
      return lexema_;
    }

    int getType()
    {
      return type_;
    }

    void read(ifstream & in);     // Lee una palabra de un fichero y la asigna al token invocante.
    void clasify();               // Clasifica un token, dandole valor a su atributo type.
    void write(ofstream & out);   // Escribe el token en un fichero según su clasificación.

};
