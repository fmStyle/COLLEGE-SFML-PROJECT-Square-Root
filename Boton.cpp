#include "Boton.h"

Boton::Boton(Color sinMouse, Color conMouse, string textoAMostrar, string buttonTag, float sizeX, float sizeY, shared_ptr<Font>&fuente, Vector2f posicion, map<string, shared_ptr<Sound>> *soundsUsable) {
	this->sinMouse = sinMouse; this->conMouse = conMouse;
	this->sizeX = sizeX; this->sizeY = sizeY;
	this->soundsUsable = soundsUsable;
	
	boton.setSize(Vector2f(sizeX, sizeY));
	boton.setOrigin(Vector2f(sizeX/2, sizeY/2));
	boton.setPosition(posicion);
	boton.setFillColor(sinMouse);

	
	textoBoton.setFont(*fuente);
	textoBoton.setString(textoAMostrar);
	textoBoton.setCharacterSize(sizeX*sizeY*40/20000);
	
	
	textoBoton.setPosition(Vector2f(posicion.x - sizeX/2.f, posicion.y - sizeY/2.f));
	presionado = false;
}

void Boton::ActualizarBoton(Vector2f mousePos){
	if (boton.getGlobalBounds().contains(mousePos)){
		boton.setFillColor(conMouse);
	}else{
		boton.setFillColor(sinMouse);
	}
}

void Boton::ManejarEventoBoton(Vector2f mousePos, unique_ptr<Event>&e){
	if (boton.getGlobalBounds().contains(mousePos)){
		if (e->mouseButton.button == Mouse::Left){
			if (!presionado){
				//(*soundsUsable)["selectionSound"]->play();
				presionado = true;
			}
		}
	}
}

void Boton::DibujarBoton(shared_ptr<RenderWindow>&ventana){
	ventana->draw(boton);
	ventana->draw(textoBoton);
}

