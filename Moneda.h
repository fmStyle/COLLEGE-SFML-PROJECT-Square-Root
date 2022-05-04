#ifndef MONEDA_H
#define MONEDA_H

#include "Pickups.h"

class Moneda : public Pickups{
public:
	Moneda(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable);
	void Afectar();
private:
};

#endif

