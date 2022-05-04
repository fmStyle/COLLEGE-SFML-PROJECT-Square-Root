#ifndef ESTADO_H
#define ESTADO_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <map>
#include <cmath>
#include <deque>
#include <list>


using namespace std;
using namespace sf;

/// Clase abstracta
class Estado {
	
	
protected:
	
	shared_ptr<RenderWindow>m_ventana;
	
	bool terminado;
	shared_ptr<View>v1;
	
	stack<shared_ptr<Estado>>*estados;
	
	map<string, shared_ptr<Texture>> textures;
	map<string, shared_ptr<SoundBuffer>> sounds;
	map<string, shared_ptr<Sound>> soundsUsable;
	Music mainMusic;
	
	shared_ptr<Font> m_fuenteJuego;
public:
	/// Constructor
	Estado(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados);
	
	/// Funciones
	bool &Terminado(){return terminado;}
	shared_ptr<RenderWindow>&Ventana() {return m_ventana;}
	virtual void TerminarEstado() = 0;
	virtual void ActualizarEstado() = 0;
	virtual void DibujarEstado() = 0;
	virtual void ManejarEventoEstado(unique_ptr<Event>&e) = 0;
	virtual void CargarTexturas() = 0;
	virtual void InicializarDespuesDeCargarTexturas() = 0;
	
	
	/// Destructor
	virtual ~Estado();
};

#endif

