#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidad.h"
#include "Bala.h"

class Jugador : public Entidad{
	/// Variables
	float aceleracion;
	float desaceleracion; // Valor entre 0 y 1
	float friccion = 0.3;
	
	float velocidadX;
	float velocidadY;
	
	float anguloAMouse;
	
	
	
	int modoDisparo;
	vector<datosDisparo>d;
	
	RectangleShape jugador;
	Clock c1;
	
	float vidaMax;
	
	int municion;
	
	int monedas;
protected:
	vector<Bala>balas;
public:
	bool muerto;
	Jugador(float size, shared_ptr<RenderWindow>&ventana, float life, vector<Bala>&balas, map<string, shared_ptr<Sound>> *soundsUsable);
	
	/// Funciones
	void Mover();
	void ActualizarEntidad();
	void DibujarEntidad();
	void Disparar(vector<Bala>&balas);
	float AnguloAMouse (){return anguloAMouse;}
	
	vector<Bala>&Balas() {return balas;}
	
	float &VelocidadX() {return velocidadX;}
	float &VelocidadY() {return velocidadY;}
	
	void AnimacionGolpeado() {HitAnimation(jugador, 0);}
	
	int &ModoDisparo(){return modoDisparo;}
	
	datosDisparo DatosActualesDisparo(){return d[modoDisparo];}
	
	FloatRect coordenadasGlobales() {return jugador.getGlobalBounds();}
	
	float &VidaMax() {return vidaMax;}
	
	int &Municion() {return municion;}
	
	int &Monedas() {return monedas;}
	
	bool &Muerto() {return muerto;}
	
	RectangleShape &RectanguloJugador() {return jugador;}
	
	~Jugador();
private:
};

#endif

