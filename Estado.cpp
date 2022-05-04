#include "Estado.h"

Estado::Estado(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados) {
	this->estados = estados;
	m_ventana = ventana;
	terminado = false;
	m_fuenteJuego = fuenteJuego;
}

Estado::~Estado() {
	
}

