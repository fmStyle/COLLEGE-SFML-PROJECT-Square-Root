#include "Moneda.h"

//Moneda::Moneda() {
//	
//}

Moneda::Moneda(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable) : Pickups(tex, posicion, 
jugador, textosAnimados, fuente, soundsUsable) {
	sprite.setScale(0.5f, 0.5f);
}

void Moneda::Afectar(){
	int randValueToSum = 1 + rand()%3;
	jugador->Monedas() += randValueToSum;
	soundsUsable["coinUpSound"]->play();
	textosAnimados->push_back(TextoAnimado(sprite.getPosition(), Color(255, 255, 0), 30.f, "+" + to_string(randValueToSum), fuente, 0.3f));
}
