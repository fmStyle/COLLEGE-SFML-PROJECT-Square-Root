#ifndef ESTADOTOP10_H
#define ESTADOTOP10_H

#include "EstadoGuardarPuntajes.h"
#include <algorithm>

struct datosFinales{
	int nroRonda;
	char nombre[50];
};

class EstadoTop10 : public Estado{
public:
	EstadoTop10(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados);
	
	void TerminarEstado();
	void ActualizarEstado();
	void DibujarEstado();
	void ManejarEventoEstado(unique_ptr<Event>&e);
	void CargarTexturas();
	void InicializarDespuesDeCargarTexturas();
	
	~EstadoTop10() {}
private:
	
	ifstream arch;
	
	vector<Text>puestos;
	vector<datosFinales> DatosFinales;
	int tamanoBinario;
	
	unique_ptr<View>viewTop10;
};

#endif

