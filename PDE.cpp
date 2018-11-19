#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;
//int atoi(const char *str) converts the string argument str to an integer (type int). (tomado de tutorials point)
int main(int argc, char const *argv[])
{
  // arg[1]=0 para condiciones fijas
	// arg[1]=1 para condiciones periodicas
	// arg[1]=2 para condiciones abiertas

  // archivo en el que se va a scribir
  ofstream escribir_datos(argv[2]);

// Imprimir en la terminal el caso a tratar
//int atoi(const char *str) converts the string argument str to an integer (type int).
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
// se definen las variables.
float conductividad; //* m^2/s
conductividad = 1.62;

float calorEspecifico; // J / (kg*K)
calorEspecifico = 820;

float densidad; // kg / m^3
densidad = 2710;

float coeficienteDifusion;
coeficienteDifusion = conductividad/(calorEspecifico*densidad);

// tamano de la malla
int npuntos;
npuntos = 80;

float h;
h = 50.0/(npuntos-1);
// crear malla x,y con npuntos valores de 0 a 50.0
int i,j;
float X[npuntos][npuntos];
float Y[npuntos][npuntos];

// crear malla
for (i = 0; i < npuntos; ++i)
{
  for (j = 0; j < npuntos; ++j)
  {
    X[i][j] = i*h;
    Y[i][j] = j*h;
  }
}

}
