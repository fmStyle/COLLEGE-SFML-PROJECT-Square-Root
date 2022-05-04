//#include <SFML/Graphics.hpp>
#include "FuncionesAnguloDistancia.h"
#include <cmath>
using namespace std;
using namespace sf;

float Angulo(Vector2f posicion1, Vector2f posicion2){
	/// La diferencia de Y se calcula al reves porque SFML va desde 1 a 0 en el eje Y (De abajo para arriba)
	return atan2(posicion1.y-posicion2.y, posicion2.x-posicion1.x)*180/M_PI;
}
	
//float Distancia(Vector2f posicion1, Vector2f posicion2){
//	float distanciaX = abs(posicion1.x - posicion2.x);
//	float distanciaY = abs(posicion1.y - posicion2.y);
//	return (sqrt(pow(distanciaX, 2) + pow(distanciaY, 2)));
//}
//	
