#ifndef PICKUPS_H
#define PICKUPS_H

#include "Jugador.h"
#include "TextoAnimado.h"

class Pickups {
	float speedX;
	float speedY;
	float randomDir;
protected:
	Sprite sprite;
	shared_ptr<Jugador>jugador;
	bool agarrado;
	Vector2f posicion;
	
	deque<TextoAnimado>*textosAnimados; 
	map<string, shared_ptr<Sound>> soundsUsable;
	shared_ptr<Font>fuente;
public:
	Pickups(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable);
	void ActualizarPickup();
	void DibujarPickup(shared_ptr<RenderWindow>&ventana);
	virtual void Afectar() = 0;
	bool &Agarrado() {return agarrado;}
};

#endif

