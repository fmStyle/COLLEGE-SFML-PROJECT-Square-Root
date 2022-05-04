#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "Estado.h"


template <typename T>
void HitAnimation(T t, int runOnce){
	Clock c1;
	Color n;
	Color c = t.getFillColor();
	bool rFilled, gFilled, bFilled;
	if (runOnce == 0){
		c1.restart();
		
		n.r = 255;
		n.g = 255;
		n.b = 255;
		runOnce++;
	}
	
	if (n.r > c.r) {
		n.r = -255*c1.getElapsedTime().asSeconds()/0.25 + 255;
	} else rFilled = true;
	
	if (n.g > c.b) {
		n.g = -255*c1.getElapsedTime().asSeconds()/0.25 + 255;
		
	} else gFilled = true;
	
	if (n.b > c.b) {
		n.b = -255*c1.getElapsedTime().asSeconds()/0.25 + 255;
		
	} else bFilled = true;
	t.setFillColor(n);
	if (rFilled && gFilled && bFilled) t.setFillColor(c);
}

template <typename T, typename X>
bool Colisiona(T t, X x){
	if (t.intersects(x)) return true;
	return false;
}


class Entidad {
private:
	Vector2f posicion;
	shared_ptr<RenderWindow>m_ventana;
protected:
	float size;
	
protected:
	float life;
	float AnguloAJugador;
	float DistanciaAJugador;
	map<string, shared_ptr<Sound>> *soundsUsable;
	
public:
	bool runOnceForMain;
	bool deadDead;
	
	string tag;
	
	Entidad(float size, shared_ptr<RenderWindow>&ventana, float life, map<string, shared_ptr<Sound>> *soundsUsable);
	
	/// Funciones
	virtual void Mover() = 0;
	virtual void ActualizarEntidad() = 0;
	virtual void DibujarEntidad() = 0;
	virtual FloatRect coordenadasGlobales() = 0;
	virtual void ActualizarBarraDeVida() {}
	virtual void FeedbackBala(Vector2f PosicionBala, float DanioBala) {}
	
	float &Vida() {return life;}
	
//	virtual void Disparar() = 0;
	Vector2f &Posicion() {return posicion;}
	shared_ptr<RenderWindow>&Ventana() {return m_ventana;}
	
	virtual ~Entidad() {}

};

#endif

