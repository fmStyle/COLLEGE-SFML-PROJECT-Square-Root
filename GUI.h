#ifndef GUI_H
#define GUI_H
#include "Jugador.h"

//#include <sstring>

class GUI {
	
	Sprite shopButton;
	
	
	shared_ptr<RenderWindow>ventana;
	shared_ptr<View>v1;
	shared_ptr<Jugador> jugador;
	
	RectangleShape vida;
	
	Text rondaActual;
	
	Sprite municionesSprite;
	Text municiones;
	
	Sprite monedasSprite;
	Text monedas;
	
	Text ActualGun;

	map<string, shared_ptr<Texture>>textures;
	shared_ptr<Font> m_fuenteJuego;
	
	shared_ptr<int>nroRonda;
	
public:
	bool shopButtonPressed;
	GUI(shared_ptr<RenderWindow>&ventana, shared_ptr<Jugador>&j, map<string, shared_ptr<Texture>>&textures, shared_ptr<Font>&m_fuenteJuego, shared_ptr<int>&nroRonda);
	void ActualizarGUI(Vector2f posicionMouse);
	shared_ptr<View>&ViewGUI() {return v1;}
	void DibujarGUI();
};

#endif

