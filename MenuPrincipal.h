#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "Estado.h"
#include "EstadoJuego.h"
#include "Boton.h"
#include "EstadoTop10.h"

class MenuPrincipal : public Estado {
	
	Text squareRoot;
	
	Sprite leaderBoards;
	
	unique_ptr<Boton>jugar;
//	unique_ptr<Boton>opciones;
	unique_ptr<Boton>salir;
	
	unique_ptr<View>viewMenu;
	
	shared_ptr<RenderWindow>ventana;
	
	Vector2f posicionMouse;
	
public:
	MenuPrincipal(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados);
	void TerminarEstado();
	void ActualizarEstado();
	void DibujarEstado();
	void ManejarEventoEstado(unique_ptr<Event>&e);
	void CargarTexturas();
	void InicializarDespuesDeCargarTexturas();
	
	~MenuPrincipal() {}
};

#endif

