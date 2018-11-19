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

float calcular_proyectil(float angulo)
{ // hacer los calculos del proyectil que se dispara con cada angulo

	cout << "Calculando trayectoria del proyectil a " << angulo << " grados" << endl;
  float angulor = angulo/180*3.14159;
  // paso de tiempo, tiempo total
  float ht=0.0002;
  // x,y,vx,vy en el pasado 0 y en el futuro 1
	float x0=0.0, x1;
	float y0=0.0, y1;
	float vx0=300*cos(angulor), vx1;
	float vy0=300*sin(angulor), vy1;

  // Crear 4ks por cada variable y una variable para la pendiente de cada variable
	float pendientex=0.0, k1x=0.0, k2x=0.0, k3x=0.0, k4x=0.0;
	float pendientey=0.0, k1y=0.0, k2y=0.0, k3y=0.0, k4y=0.0;
	float pendientevx=0.0, k1vx=0.0, k2vx=0.0, k3vx=0.0, k4vx=0.0;
	float pendientevy=0.0, k1vy=0.0, k2vy=0.0, k3vy=0.0, k4vy=0.0;

	ofstream archivo_salida("proyectil.txt");
}

int i=0;
do
{
  // calcular derivada en el punto que conozco
  k1x = derivada_x(vx0);
  k1y = derivada_y(vy0);
  k1vx = derivada_vx(vx0, vy0);
  k1vy = derivada_vy(vx0, vy0);

  // calcular derivada medio paso adelante con pendiente k1
  k2x = derivada_x(vx0 + 0.5*ht*k1vx);
  k2y = derivada_y(vy0 + 0.5*ht*k1vy);
  k2vx = derivada_vx(vx0 + 0.5*ht*k1vx, vy0 + 0.5*ht*k1vy);
  k2vy = derivada_vy(vx0 + 0.5*ht*k1vx, vy0 + 0.5*ht*k1vy);

  // calcular derivada medio paso adelante con pendiente k2
  k3x = derivada_x(vx0 + 0.5*ht*k2vx);
  k3y = derivada_y(vy0 + 0.5*ht*k2vy);
  k3vx = derivada_vx(vx0 + 0.5*ht*k2vx, vy0 + 0.5*ht*k2vy);
  k3vy = derivada_vy(vx0 + 0.5*ht*k2vx, vy0 + 0.5*ht*k2vy);

  // calcular derivada un paso adelante con pendiente k3
  k4x = derivada_x(vx0 + 1.0*ht*k3vx);
  k4y = derivada_y(vy0 + 1.0*ht*k3vy);
  k4vx = derivada_vx(vx0 + 1.0*ht*k3vx, vy0 + 1.0*ht*k3vy);
  k4vy = derivada_vy(vx0 + 1.0*ht*k3vx, vy0 + 1.0*ht*k3vy);

  // Calcular la pendiente a partir de las 4ks
  pendientex = (1.0*k1x + 2.0*k2x + 2.0*k3x + 1.0*k4x)/6.0;
  pendientey = (1.0*k1y + 2.0*k2y + 2.0*k3y + 1.0*k4y)/6.0;
  pendientevx = (1.0*k1vx + 2.0*k2vx + 2.0*k3vx + 1.0*k4vx)/6.0;
  pendientevy = (1.0*k1vy + 2.0*k2vy + 2.0*k3vy + 1.0*k4vy)/6.0;

  // Actualizar sitema un paso de tiempo
  x1 = x0 + pendientex*ht;
  y1 = y0 + pendientey*ht;
  vx1 = vx0 + pendientevx*ht;
  vy1 = vy0 + pendientevy*ht;


  archivo_salida << x0 << " " << vx0 << " " << y0 << " " << vy0 << endl;

  // Guardar los valores del futuro (1) en el pasado(1) para preparar
  // la siguiente iteracion
  x0 = x1;
  y0 = y1;
  vx0 = vx1;
  vy0 = vy1;

  i=i+1;

}

int main(int argc, char const *argv[])
{

	float angulo=45.0;
	calcular_proyectil(angulo);
	/* code */
	return 0;
}
