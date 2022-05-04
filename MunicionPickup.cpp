#include "MunicionPickup.h"

MunicionPickup::MunicionPickup(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable) : Pickups(tex, posicion, jugador, 
textosAnimados, fuente, soundsUsable) {
	sprite.setScale(0.5f, 0.5f);
}

void MunicionPickup::Afectar(){
	int randValueToSum = 10 + rand()%10;
	jugador->Municion() += randValueToSum;
	soundsUsable["ammoUpSound"]->play();
	textosAnimados->push_back(TextoAnimado(sprite.getPosition(), Color(90, 255, 50), 30.f, "+" + to_string(randValueToSum), fuente, 0.3f));
}

