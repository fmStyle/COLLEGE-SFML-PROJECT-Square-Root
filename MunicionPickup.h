#ifndef MUNICIONPICKUP_H
#define MUNICIONPICKUP_H

#include "Pickups.h"

class MunicionPickup : public Pickups{
public:
	MunicionPickup(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable);
	void Afectar();
private:
};

#endif

