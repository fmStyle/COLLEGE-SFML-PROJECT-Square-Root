#include "TextoAnimado.h"

TextoAnimado::TextoAnimado(Vector2f posicion, Color color, float tamano, string texto, shared_ptr<Font>&fuente, float duracionAnimacion) {
//	this->textosAnimados = textosAnimados;
	aux.setFont(*fuente);
	aux.setString(texto);
	aux.setColor(color);
	aux.setPosition(posicion);
	aux.setCharacterSize(tamano);
	relojTexto.restart();
	animacionColor = 0;
	this->duracionAnimacion = duracionAnimacion;
	this->color = color;
	ejecutarUnaVez = false;
	terminado = false;
}

void TextoAnimado::ActualizarMovimientoTexto(){
	
	
	
	if (ejecutarUnaVez == false){
		relojTexto.restart();
		ejecutarUnaVez = true;
	}
	animacionColor = (-255/duracionAnimacion) * relojTexto.getElapsedTime().asSeconds() + 255;
	aux.move(0, -5.f);
	
	float r = color.r;
	float g = color.g;
	float b = color.b;
	
	aux.setFillColor(Color(r, g, b, animacionColor));
	if (relojTexto.getElapsedTime().asSeconds()>duracionAnimacion) terminado = true;
	
}
void TextoAnimado::DibujarTexto(shared_ptr<RenderWindow>&ventana){
	ventana->draw(aux);
}
