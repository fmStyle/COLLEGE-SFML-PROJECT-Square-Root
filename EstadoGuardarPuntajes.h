#ifndef ESTADOGUARDARPUNTAJES_H
#define ESTADOGUARDARPUNTAJES_H

#include "Estado.h"
#include <fstream>

struct datosAGuardar{
	int nroRonda;
	char nombre[50];
};

class EstadoGuardarPuntajes : public Estado {
public:
	EstadoGuardarPuntajes(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados, int &nroRonda);
	
	void TerminarEstado();
	void ActualizarEstado();
	void DibujarEstado();
	void ManejarEventoEstado(unique_ptr<Event>&e);
	void CargarTexturas();
	void InicializarDespuesDeCargarTexturas();
	
	~EstadoGuardarPuntajes() {}
private:
	datosAGuardar datos;
	
	fstream arch;
	
	unique_ptr<View>viewGuardarPuntajes;
	
	Text Guide;
	
	String playerInput;
	Text playerText;
};

#endif

