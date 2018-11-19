#include <stdio.h>
#include <math.h>
#include "iostream"
#include "fstream"
using namespace std;

float derivada_x(float vx)
{ // Funcion que devulve la derivada de la posicion x
	return vx;
}

float derivada_y(float vy)
{ // Funcion que devulve la derivada de la posicion y
	return vy;
}


float derivada_vx(float vx, float vy)
{ // Funcion que devulve la derivada de la velocidad x
  // coeficiente de friccion c, gravedad y masa. todo en SI
	float c=0.2, g=10, m=0.2;

	float resultado = 0;
	float norma_v;

	norma_v = sqrt(vx*vx + vy*vy);
	resultado = -c*(norma_v*norma_v/m)*(vx/norma_v);
	return resultado;
}

float derivada_vy(float vx, float vy)
{ // Funcion que devulve la derivada de la velocidad y

	// coeficiente de friccion c, gravedad y masa. todo en SI
	float c=0.2, g=10, m=0.2;

  float resultado = 0;
	float norma_v;

	norma_v = sqrt(vx*vx + vy*vy);
	resultado = -g -c*(norma_v*norma_v/m)*(vy/norma_v);

	return resultado;
}


int main(int argc, char const *argv[])
{

	float angulo=45.0;
	calcular_proyectil(angulo);
	/* code */
	return 0;
}
