#ifndef BALA_H
#define BALA_H

#include <SFML/Graphics.hpp>
#include "Entidad.h"
using namespace std;
using namespace sf;

struct datosDisparo{
	
	Color colorDisparo;
	
	float m_velocidad;
	float m_danio;
	int m_municiones;
	int m_anguloError;
	int m_probabilidadCritico;
	
	bool m_automatico;
	/// La cadencia viene dada en milisegundos
	
	Clock relojCadencia;
	float m_cadencia;
	datosDisparo() {}
	
	datosDisparo(float velocidad, float danio, int municiones, int anguloError, bool automatico, float cadencia, int probabilidadCritico){
		m_velocidad = velocidad; m_danio = danio;
		m_municiones = municiones; m_anguloError = anguloError; 
		m_automatico = automatico; m_cadencia = cadencia;
		m_probabilidadCritico = probabilidadCritico;
		
	}
};

class Bala{
	float VelocidadX;
	float VelocidadY;
	RectangleShape bala;
	
	Vector2f posicion;
	
	datosDisparo m_datos;
	
	int runOnce;
	Clock c1;
	bool pego;
	bool terminado;
	
	bool critico;
public:
	Bala(float angulo, float tamano, Vector2f posicion, datosDisparo d);
	void ActualizarMovimientoBala();
	void DibujarBala(shared_ptr<RenderWindow>&ventana);
	
	datosDisparo Datos() {return m_datos;}
	
	bool Critico() {return critico;}
	
	bool &Pego() {return pego;}
	bool Terminado() {return terminado;}
	RectangleShape &CuadradoBala() {return bala;}
	float BalaVelocidadX(){return VelocidadX;}
	float BalaVelocidadY(){return VelocidadY;}
	
	Vector2f PosicionBala() {return posicion;}
};

#endif
