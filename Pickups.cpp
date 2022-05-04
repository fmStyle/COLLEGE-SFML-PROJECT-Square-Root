#include "Pickups.h"

Pickups::Pickups(Texture &tex, Vector2f posicion, shared_ptr<Jugador>&jugador, deque<TextoAnimado>*textosAnimados, shared_ptr<Font>&fuente, map<string, shared_ptr<Sound>> &soundsUsable) {
	
	this->textosAnimados = textosAnimados;
	this->fuente = fuente;
	
	this->soundsUsable = soundsUsable;
	
	sprite.setTexture(tex);
	sprite.setOrigin(Vector2f(tex.getSize().x/2, tex.getSize().y/2));
	this->posicion = posicion;
	this->jugador = jugador;
	randomDir = rand()%628;
	randomDir /= 100.f;
	//cout<<randomDir<<endl;
	speedX = cos(randomDir) * 7 + float(rand()%15);
	speedY = sin(randomDir) * 7 + float(rand()%15);
	sprite.setPosition(posicion);
	//cout<<speedX<<endl;
	//cout<<speedY<<endl;
	agarrado = false;
}

void Pickups::ActualizarPickup(){
	
	speedX *= 0.9;
	speedY *= 0.9;
	
	if (abs(speedX) + abs(speedY) < 0.1){
		speedX = 0;
		speedY = 0;
	}
	
	sprite.move(speedX, speedY);
	
	posicion = sprite.getPosition();
	
	if (sqrt(pow(jugador->Posicion().x - posicion.x, 2) + pow(jugador->Posicion().y - posicion.y, 2)) < 70.f){
		Afectar();
		agarrado = true;
	}
	
//		if (Colisiona(jugador->coordenadasGlobales(), sprite.getGlobalBounds())){
//			cout<<"hola"<<endl;
//			Afectar();
//			agarrado = true;
//		}
	
}

void Pickups::DibujarPickup(shared_ptr<RenderWindow>&ventana){
	ventana->draw(sprite);
}
