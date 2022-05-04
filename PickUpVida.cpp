#include "PickUpVida.h"

PickUpVida::PickUpVida(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable) : Pickups(tex, posicion, 
jugador, textosAnimados, fuente, soundsUsable) {
	sprite.setScale(0.5f, 0.5f);
}

void PickUpVida::Afectar(){
	int vidaAux = jugador->Vida();
	int randValueToSum = 15 + rand()%15;
	soundsUsable["healthUpSound"]->play();
	if (jugador->Vida() < jugador->VidaMax())
	{
		if (vidaAux = vidaAux + randValueToSum > jugador->VidaMax()){
			jugador->Vida() = jugador->VidaMax();
		} else{
			jugador->Vida() += randValueToSum;
			textosAnimados->push_back(TextoAnimado(sprite.getPosition(), Color(255, 0, 0), 30.f, "+" + to_string(randValueToSum), fuente, 0.3f));
		}
	} 
}
