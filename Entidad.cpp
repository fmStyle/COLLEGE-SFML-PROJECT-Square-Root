#include "Entidad.h"

Entidad::Entidad(float size, shared_ptr<RenderWindow>&ventana, float life, map<string, shared_ptr<Sound>> *soundsUsable) {
	this->soundsUsable = soundsUsable;
	this->life = life;
	this->size = size;
	m_ventana = ventana;
}

//Entidad::~Entidad() {
//	
//}
//
