#ifndef PICKUPVIDA_H
#define PICKUPVIDA_H

#include "Pickups.h"


class PickUpVida : public Pickups {
public:
	PickUpVida(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable);
	void Afectar();
};

#endif

