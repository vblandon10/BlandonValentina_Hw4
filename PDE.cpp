#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

int main(int argc, char const *argv[])
{
  // arg[1]=0 para condiciones fijas
	// arg[1]=1 para condiciones periodicas
	// arg[1]=2 para condiciones abiertas

  // archivo en el que se va a scribir
  ofstream escribir_datos(argv[2]);

// Imprimir en la terminal el caso a tratar
if (atoi(argv[1])==0)
{
  cout << "Condiciones de fronteras Fijas" << "\n\n";
}else if (atoi(argv[1])==1)
{
  cout << "Condiciones de fronteras Abiertas" << "\n\n";
}else if (atoi(argv[1])==2)
{
  cout << "Condiciones de fronteras periodicas" << "\n\n";
}

}
