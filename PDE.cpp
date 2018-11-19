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

  // archivo en el que se va a escribir
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
// Arreglos de la temperatura
float presente[npuntos][npuntos];
float futuro[npuntos][npuntos];

// Asignar valores iniciales
for (i = 0; i < npuntos; ++i)
{
  for (j = 0; j < npuntos; ++j)
  {
    if ( pow(X[i][j]-25.0, 2) + pow(Y[i][j]-25.0, 2) <= 10.0 )
    { // Corresponde a la varilla
      presente[i][j] = 100.0;
      futuro[i][j] = 100.0;
    }else
    { // Corresponde a calcita
      presente[i][j] = 10;
      futuro[i][j] = 10;
    }
  }
}

// Si hay condiciones de frontera fijas, asignar los valores
if (atoi(argv[1])==0)
{
  for (i = 0; i < npuntos; ++i)
  {
    presente[0][i] = 10.0; // borde superior
    presente[npuntos-1][i] = 10.0; // borde inferior

    presente[i][0] = 10.0; // borde derecho
    presente[i][npuntos-1] = 10.0; // borde izquierdo


    futuro[0][i] = 10.0;
    futuro[npuntos-1][i] = 10.0;

    futuro[i][0] = 10.0;
    futuro[i][npuntos-1] = 10.0;


  }
}

int indice_tiempo;
int pasos_de_tiempo;
pasos_de_tiempo = 1000;
float diferencial_tiempo = 0.1*pow(h,2)/coeficienteDifusion;

for (indice_tiempo = 0; indice_tiempo < pasos_de_tiempo; ++indice_tiempo)
{

  // recorrido en los puntos de la calcita
  for (i = 1; i < npuntos-1; ++i)
  {
    for (j = 1; j < npuntos-1; ++j)
    {
      if ( pow(X[i][j]-25.0, 2) + pow(Y[i][j]-25.0, 2) >= 10.0 )
      { // Corresponde a la calcita
        futuro[i][j] = presente[i][j] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[i-1][j] + presente[i+1][j] - 4.0*presente[i][j] + presente[i][j-1] + presente[i][j+1]);

    }
  }
}
// recorrido en los puntos de los bordes
// dependiendo de las condiciones de frontera el recorrido es diferente
// Si son condiciones de frontera fijas, no hay que hacer nada mas
if (atoi(argv[1])==1)
{ // Condiciones de fronteras Abiertas
  // La derivada espacial en los bordes es 0
  for (i = 0; i < npuntos; ++i)
  {
    futuro[i][0] = futuro[i][1]; // El borde de arriba (0) toma el valor de los nodos mas cercanos (1)
    futuro[i][npuntos-1] = futuro[i][npuntos-2];

    futuro[0][i] = futuro[1][i]; // El borde de la izquierda (0) toma el valor de los nodos mas cercanos (1)
    futuro[npuntos-1][i] = futuro[npuntos-2][i];
  }
}
else if (atoi(argv[1])==2)
{ // "Condiciones de fronteras periodicas"
  // Los nodos a la derecha de los nodos del borde derecho son los nodos del borde izquierdo y viceverza
  // Los nodos arriba de los nodos del borde superior son los nodos del borde inferior y viceverza
  for (i = 1; i < npuntos-1; ++i)
  {
    futuro[i][0] = presente[i][0] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[i-1][0] + presente[i+1][0] - 4.0*presente[i][0] + presente[i][npuntos-1] + presente[i][0+1]);
    futuro[i][npuntos-1] = presente[i][npuntos-1] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[i-1][npuntos-1] + presente[i+1][npuntos-1] - 4.0*presente[i][npuntos-1] + presente[i][npuntos-1-1] + presente[i][0]);

    futuro[0][i] = presente[0][i] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-1][i] + presente[0+1][i] - 4.0*presente[0][i] + presente[0][i-1] + presente[0][i+1]);
    futuro[npuntos-1][i] = presente[npuntos-1][i] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-2][i] + presente[0][i] - 4.0*presente[npuntos-1][i] + presente[npuntos-1][i-1] + presente[npuntos-1][i+1]);
  }

  // calcular las esquinas
  futuro[0][0] = presente[0][0] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-1][0] + presente[0+1][0] - 4.0*presente[0][0] + presente[0][npuntos-1] + presente[0][0+1]);
  futuro[npuntos-1][0] = presente[npuntos-1][0] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-2][0] + presente[0][0] - 4.0*presente[npuntos-1][0] + presente[npuntos-1][npuntos-1] + presente[npuntos-1][0+1]);
  futuro[0][npuntos-1] = presente[0][npuntos-1] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-1][npuntos-1] + presente[0+1][npuntos-1] - 4.0*presente[0][npuntos-1] + presente[0][npuntos-2] + presente[0][0]);
  futuro[npuntos-1][npuntos-1] = presente[npuntos-1][npuntos-1] + coeficienteDifusion*diferencial_tiempo/pow(h,2) * (presente[npuntos-2][npuntos-1] + presente[0][npuntos-1] - 4.0*presente[npuntos-1][npuntos-1] + presente[npuntos-1][npuntos-2] + presente[npuntos-1][0]);
}
// Actualizar sistema
for (i = 0; i < npuntos; ++i)
{
  for (j = 0; j < npuntos; ++j)
  {
    presente[i][j] = futuro[i][j];
  }
}


// exportar datos
for (i = 0; i < npuntos; ++i)
{
  for (j = 0; j < npuntos; ++j)
  {
    escribir_datos << futuro[i][j] << " ";
  }
  escribir_datos << "\n";
}

return 0;
}
