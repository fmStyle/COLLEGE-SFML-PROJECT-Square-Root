#include "Jugador.h"
#include "FuncionesAnguloDistancia.h"

using namespace std;

Jugador::Jugador(float size, shared_ptr<RenderWindow>&ventana, float life, vector<Bala>&balas, map<string, shared_ptr<Sound>> *soundsUsable) : Entidad(size, ventana, life, soundsUsable){
	
	monedas = 0;
	municion = 100;
	
	muerto = false;
	
	jugador.setSize(Vector2f(size, size));
	jugador.setPosition(1280/2, 720/2);
	jugador.setOrigin(size/2.f, size/2.f);
	jugador.setOutlineThickness(7.5);
	jugador.setOutlineColor(Color::White);
	c1.restart();
	aceleracion = 2.f;
	desaceleracion = 0.8f;
	friccion = 0.3f;
	
	modoDisparo = 0;
	d.push_back(datosDisparo(40.f, 25.f, 30, 15, true, 150.f, 5));
	d.push_back(datosDisparo(35.f, 18.f, 30, 18, false, 500.f, 3));
	
	this->balas = balas;
	
	velocidadX = 0.f;
	velocidadY = 0.f;
	
	vidaMax = life;
}

void Jugador::ActualizarEntidad(){
	Posicion() = jugador.getPosition();
	if (this->Vida() > vidaMax) this->Vida() = vidaMax;
	
	/// Animacion color
	if (c1.getElapsedTime().asSeconds() > 3.14) c1.restart();
	jugador.setFillColor(Color(255, 0, sin(c1.getElapsedTime().asSeconds()) * 100));
	
	/// Rotacion hacia el cursor
	Vector2f posicionMouse = Ventana()->mapPixelToCoords(Mouse::getPosition(*Ventana()));
	anguloAMouse = -Angulo(Posicion(), posicionMouse);
	jugador.setRotation(anguloAMouse);
	
	/// Proceso de input
	if (Keyboard::isKeyPressed(Keyboard::Key::A)){
		velocidadX = velocidadX - aceleracion;
	} 	
	if (Keyboard::isKeyPressed(Keyboard::Key::D)){
		velocidadX = velocidadX + aceleracion;
	} 	
	if (Keyboard::isKeyPressed(Keyboard::Key::W)){
		velocidadY = velocidadY - aceleracion;
	} 	
	if (Keyboard::isKeyPressed(Keyboard::Key::S)){
		velocidadY = velocidadY + aceleracion;
	} 
	
	/// Desaceleracion
	velocidadX *= desaceleracion;
	velocidadY *= desaceleracion;
	
	/// Friccion
	if (abs(velocidadX) + abs(velocidadY)< 0.3f) {
		velocidadX =0.f; velocidadY = 0.f;
	}
	
	/// Le paso el vector de balas por referencia al jugador en caso de que quiera usarlo en una clase mas adelante
	
}

void Jugador::Mover(){
	if (muerto){
		velocidadX *= 0.9;
		velocidadY *= 0.9;
	}
	jugador.move(velocidadX, velocidadY);
}

void Jugador::DibujarEntidad(){
	Ventana()->draw(jugador);
}

void Jugador::Disparar(vector<Bala>&balas){
	if (d[modoDisparo].relojCadencia.getElapsedTime().asMilliseconds() > d[modoDisparo].m_cadencia){
		/// Ametralladora
		if (modoDisparo == 0 && this->Municion() > 0){
			balas.push_back(Bala(anguloAMouse, 20.f, Posicion(), d[modoDisparo]));
			velocidadX = -(balas[balas.size()-1].BalaVelocidadX());
			velocidadY = -(balas[balas.size()-1].BalaVelocidadY());
			d[modoDisparo].relojCadencia.restart();
			municion--;
			(*soundsUsable)["machineGunShotSound"]->play();
		}
		/// Escopeta
		if (modoDisparo == 1 && this->Municion() > 5){
			for (int i = 0; i<5; i++){
				balas.push_back(Bala(anguloAMouse, 20.f, Posicion(), d[modoDisparo]));
				municion--;
			}
			velocidadX = cos(-anguloAMouse*M_PI/180 + M_PI)* d[modoDisparo].m_velocidad * 1.5;
			velocidadY = sin(-anguloAMouse*M_PI/180) * d[modoDisparo].m_velocidad * 1.5;
			d[modoDisparo].relojCadencia.restart();
			(*soundsUsable)["shotGunShotSound"]->play();
		}
	}
	this->balas = balas;
}

Jugador::~Jugador() {
	
}

//Jugador::Jugador(float size) : Entidad(size) {
//	jugador.setSize(Vector2f(size, size));
//	jugador.setPosition(1280/2, 720/2);
//}
//
//void Jugador::DibujarEntidad(shared_ptr<RenderWindow>&ventana){
//	ventana->draw(jugador);
//}

