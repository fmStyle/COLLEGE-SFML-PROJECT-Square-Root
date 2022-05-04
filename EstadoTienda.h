#ifndef ESTADOTIENDA_H
#define ESTADOTIENDA_H

#include "Estado.h"
#include "Boton.h"

class EstadoTienda : public Estado{
public:
	/// Paso las texturas por el constructor porque por alguna razon no existen si uso (*textures["..."]) que es parte de estado.h
	/// Eso es algo que me gustaría entender porque no funciona, si es que se supone que cargo las texturas en el estado anterior
	EstadoTienda(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados, shared_ptr<Jugador>*jugador, Texture &coinTexture, Texture &bulletTexture, Texture &lifeTexture, Sound &BuySound, Sound &NotBuySound);
	
	Vector2f mousePos;
	
	unique_ptr<View>viewTienda;
	

	
	void TerminarEstado();
	void ActualizarEstado();
	void DibujarEstado();
	void ManejarEventoEstado(unique_ptr<Event>&e);
	void CargarTexturas();
	void InicializarDespuesDeCargarTexturas();
	
	~EstadoTienda() {}
private:
	Sound buySound;
	Sound notBuySound;
		
	Text availableCoins;
	Sprite coin;
	
	Sprite bullet;
	unique_ptr<Boton>compraBalas;
	Text infoCompraBalas;
	int precioBala, balasAComprar;
	
	Sprite life;
	Text infoCompraVida;
	unique_ptr<Boton>compraVida;
	int precioVida, vidaAComprar;
	shared_ptr<Jugador>*jugador;
};

#endif

