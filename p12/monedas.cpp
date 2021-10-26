#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main( int argc, char** argv )
{
  double cantidad_ini = 17.86;

  int cantidad = (int)(cantidad_ini * 100), total = 0, num;
  vector<int> valor = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
  vector<int> solucion = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for ( int i = 0; cantidad > 0 ; i++)
    if ( cantidad >= valor[i] )
    {
      num = cantidad / valor[i];
      solucion[i] = num;
      total += num;
      cantidad = cantidad % valor[i];

      cout << num << " x " << (float) valor[i] / 100 << endl;
    }
    cout << "Total: " << total << endl;


return 0;
}
