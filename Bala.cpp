#include "Bala.h"
#include <cstdlib>
using namespace std;

Bala::Bala(float angulo, float tamano, Vector2f posicion, datosDisparo d){
	
	c1.restart();
	
	m_datos = d;

	float anguloRandom = (-(d.m_anguloError) + rand()%(2*d.m_anguloError))*M_PI/180;
	VelocidadX = cos(angulo*M_PI/180 + anguloRandom) * d.m_velocidad;
	VelocidadY = sin(angulo*M_PI/180 + anguloRandom) * d.m_velocidad;
	bala.setSize(Vector2f(tamano, tamano));
	bala.setPosition(posicion);
	bala.setRotation(angulo+anguloRandom*180/M_PI);
	int randomCritic = rand()%d.m_probabilidadCritico;
	switch (randomCritic){
	case 0:
		d.m_danio = d.m_danio * 2;
		bala.setFillColor(Color::Red);
		critico = true;
		break;
	default:
		bala.setFillColor(Color::Yellow);
		critico = false;
		break;
	}
	bala.setOutlineThickness(7.f);
	bala.setOutlineColor(Color::White);
	
	pego = false;
	terminado = false;
	runOnce = 0;
}

void Bala::ActualizarMovimientoBala(){
	posicion = bala.getPosition();
	if (!pego){
		bala.move(VelocidadX, VelocidadY);
		if (c1.getElapsedTime().asSeconds()>4){
			terminado = true;
		}
	} else{
		m_datos.m_danio = 0;
		if (runOnce == 0){
			c1.restart();
			runOnce++;
		}
		if (c1.getElapsedTime().asSeconds() > 0.25) terminado = true;
		bala.setFillColor(Color(255, 255, 255, -255*c1.getElapsedTime().asSeconds()/0.25 + 255));
		bala.setOutlineColor(Color(255, 255, 255, -255*c1.getElapsedTime().asSeconds()/0.25 + 255));
	}
}

void Bala::DibujarBala(shared_ptr<RenderWindow>&ventana){
	ventana->draw(bala);
}
