#ifndef LITTLEBOY_H
#define LITTLEBOY_H

#include "Entidad.h"
#include "Jugador.h"
#include "Pickups.h"


class LittleBoy : public Entidad{
	
	//	Jugador jugador;
	RectangleShape CuadradoPrincipal;
	vector<RectangleShape>CuadradosSecundarios;
	shared_ptr<Jugador>jugador;
	float radio;
	Clock c1;
	Clock c2;
	Clock c3;
	float speed;
	
	list<shared_ptr<Pickups>>pickups;
	vector<shared_ptr<Texture>>textures;
	
	RectangleShape lifeShape;
	
	bool hitten;
	int runOnce;
	int runOnce2;
	int runOnce3;
	
	float initLife;
	
	float speedX;
	float speedY;
	
	bool bulletHitten;
	
public:
	
	bool dead;
	
	LittleBoy(float size, shared_ptr<RenderWindow>&ventana, float life, shared_ptr<Jugador>&jugador, Vector2f InitialPos, map<string, shared_ptr<Sound>> *soundsUsable);
	
	void Mover();
	void ActualizarEntidad();
	void DibujarEntidad();
	void ActualizarBarraDeVida();
	void FeedbackBala(Vector2f PosicionBala, float DanioBala);
	
	FloatRect coordenadasGlobales();
	
	~LittleBoy() {}
};

#endif
