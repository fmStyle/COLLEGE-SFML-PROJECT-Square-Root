#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H


#include "Juego.h"
#include "Squarex.h"
#include "GUI.h"
#include "TextoAnimado.h"
#include "PickUpVida.h"
#include "Moneda.h"
#include "MunicionPickup.h"

#include "LittleBoy.h"
#include "Boton.h"

#include "EstadoTienda.h"
#include "EstadoGuardarPuntajes.h"

#include "TileEngine.h"

//#include "Entidad.h"


class EstadoJuego : public Estado {
	
	deque<TextoAnimado>textosAnimados;
	
	
	list<shared_ptr<Pickups>>pickups;
	
	bool ejecutarUnaVezMuerte;
	
	float duracionAnimacionCritico;
	bool ejecutarReloj;
	Clock relojCritico;
	
	shared_ptr<Jugador>jugador;
	unique_ptr<GUI>gui;
	vector<Bala>balas;
	
	float anguloAMouse;
	Vector2f posicionMouse;
	
	
	shared_ptr<int>nroRonda;
	int nroEnemigosAsesinados;
	int nroEnemigosASpawnear;
	int nroEnemigosAIncrementar;
	
	Clock delaySpawn;
	Clock roundDelay;
	
	Clock muerte;
	bool correrUnaVezClock;
	bool correrUnaVezMuerte;
	bool crearPersonaje;
	
	RectangleShape EfectoMuerte;
	Text GameOver;
	
	Sprite lapizEscribirDatos;
	
	unique_ptr<Boton> VolverAJugar;
	unique_ptr<Boton> Menu;
	unique_ptr<Boton> Salir;
	
	/// Prueba
	unique_ptr<Squarex>prueba;
	
	vector<shared_ptr<Entidad>>enemigos;
	
	unique_ptr<TileEngine> tiles;
	
public:
	EstadoJuego(shared_ptr<RenderWindow>&ventana, shared_ptr<Font> &fuenteJuego, stack<shared_ptr<Estado>>*estados);
	
	/// Funciones
	
	void TerminarEstado();
	void ActualizarEstado();
	void DibujarEstado();
	void ManejarEventoEstado(unique_ptr<Event>&e);
	
	void AnimacionCritico(Vector2f PosicionDePegada);
	
	void CargarTexturas();
	
	void InicializarDespuesDeCargarTexturas();
	
	~EstadoJuego();
};

#endif

