#include "rational.cpp"

void ratVecPrint(vector < rational > &rational_vector)  //Imprime un vector de racionales.
{
    for (int i = 0; i < rational_vector.size(); i++) {
        rational_vector[i].WriteConsole(cout);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        cout <<
            "Ha de abrir el ejecutable de la forma: \n./rational 'nombre_entrada.txt' 'nombre_salida.txt'."
            << endl;
    } else {
        ifstream ifs, ifs2;     //Variables que voy a usar.
        ofstream ofs;
        int n = 0, aux, operator_size = 9;
        bool aux_bool;
        rational r1;
        vector < rational > rational_vector;
        char operator_id[operator_size] =
            { '+', '-', '*', '/', '>', '<', '=', 'm', 'M' };
        char titulo[90];

        ifs2.open(argv[1]);     //Se utiliza ifs2 != ifs para evitar errores
        assert(ifs2.is_open()); //con el streampos. Esta lectura solo servirá
        n = r1.RationalCount(ifs2);     //para el conteo de racionales.
        ifs2.close();

        assert(n % 2 == 0);     //Se comprueba que el numero de racionales es par.

        ifs.open(argv[1]);      //En esta lectura se leerán y almacenarán
        assert(ifs.is_open());  //los racionales en un vector.
        r1.ReadFile(rational_vector, ifs, n);
        ifs.close();

//      ratVecPrint(rational_vector);                   //Imprimo el vector de los racionales leidos
        //del fichero de texto.

        ofs.open(argv[2]);      //Se abre el archivo de salida.
        assert(ofs.is_open());

        for (int j = 0; j < n; j = j + 2)       //Para rotar de par de racionales.
        {
            for (int i = 0; i < operator_size; i++)     //Para rotar de operación.
            {
                rational_vector[j].WriteFile(ofs);      //Se escribe el primer racional.

                if (operator_id[i] == 'm')      //Se escribe el operador.
                    ofs << "  <= ";
                else if (operator_id[i] == 'M')
                    ofs << "  >= ";
                else
                    ofs << "  " << operator_id[i] << "  ";

                rational_vector[j + 1].WriteFile(ofs);  //Se escribe el segundo racional.
                ofs << "  =  ";
                aux_bool =
                    r1.Operate(rational_vector[j], rational_vector[j + 1], i);
                if (i <= 3) {   //Se escribe la respuesta simplificada.
                    r1.Simplify();      //Diferenciando entre
                    r1.WriteFile(ofs);  //operaciónes y comparaciones.
                } else if (aux_bool)
                    ofs << "true";
                else
                    ofs << "false";
                ofs << "\n";
            }
            ofs << endl;
        }

        ofs.close();            //Se 'cierra el archivo'.
        cout << "\nProceso completo." << endl << endl;
    }
    return 0;
}
