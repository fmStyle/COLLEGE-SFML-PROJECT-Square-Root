#ifndef JUEGO_H
#define JUEGO_H

#include "Estado.h"
#include "Jugador.h"
#include "EstadoJuego.h"
#include "Entidad.h"
#include "TextoAnimado.h"
#include "MenuPrincipal.h"



//#include "FuncionesAnguloDistancia.h"

using namespace std;
using namespace sf;

class Juego {
	/// Variables
	shared_ptr<RenderWindow>ventana;
	unique_ptr<Event>e;
	
	Music MainMusic;
	
	int cantidadDeGuardados;
	
	stack<shared_ptr<Estado>>Estados;
	
	View v1;
	
	shared_ptr<Font> fuenteJuego;
	
	/// Inicializadores
	void IniciarVentana();
	void IniciarEvento();
	void IniciarEstados();
public:
	/// Constructor
	Juego();
	
	/// Funciones
	void GameLoop();
	void ManejarEventos();
	void Dibujar();
	
	void CorrerJuego();
	
	/// Destructor
	~Juego();

};

#endif

