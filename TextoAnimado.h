#ifndef TEXTOANIMADO_H
#define TEXTOANIMADO_H

#include "Entidad.h"

class TextoAnimado {
public:
	TextoAnimado(Vector2f posicion, Color color, float tamano, string texto, shared_ptr<Font>&fuente, float duracionAnimacion);
	void ActualizarMovimientoTexto();
	void DibujarTexto(shared_ptr<RenderWindow>&ventana);
	bool &Terminado() {return terminado;}
private:
	Text aux;
	Clock relojTexto;
	bool terminado;
	float animacionColor;
	float duracionAnimacion;
	Color color;
	bool ejecutarUnaVez;
//protected:
//	deque<TextoAnimado>textosAnimados;
};

#endif

