#ifndef BOTON_H
#define BOTON_H

#include "Jugador.h"

class Boton {
	
	RectangleShape boton;
	Text textoBoton;
	
	Vector2f posicion;
	
	string buttonTag;
	
	Color sinMouse;
	Color conMouse;
	
	float sizeX;
	float sizeY;
	
	shared_ptr<Font>fuente;
	map<string, shared_ptr<Sound>> *soundsUsable;
	
	bool presionado;
	
public:
	Boton(Color sinMouse, Color conMouse, string textoAMostrar, string buttonTag, float sizeX, float sizeY, shared_ptr<Font>&fuente, Vector2f posicion, map<string, shared_ptr<Sound>> *soundsUsable);
	void ActualizarBoton(Vector2f mousePos);
	void ManejarEventoBoton(Vector2f mousePos, unique_ptr<Event>&e);
	void DibujarBoton(shared_ptr<RenderWindow>&ventana);
	bool &Presionado() {return presionado;}
private:
};

#endif

