#include "EstadoTienda.h"

EstadoTienda::EstadoTienda(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados, shared_ptr<Jugador>*jugador, Texture &coinTexture, Texture &bulletTexture, Texture &lifeTexture, Sound &BuySound, Sound &NotBuySound) : Estado(ventana, fuenteJuego, estados){
	
	this->buySound = BuySound;
	this->notBuySound = NotBuySound;
	
	coin.setTexture(coinTexture);
	coin.setScale(Vector2f(0.5f, 0.5f));
	coin.setPosition(0, 50);
	availableCoins.setFont(*fuenteJuego);
	availableCoins.setPosition(Vector2f(coin.getTexture()->getSize().x + 5, 50));
	
	
	this->jugador = jugador;
	precioBala = 15;
	balasAComprar = 30;
	
	bullet.setTexture(bulletTexture);
	bullet.setScale(Vector2f(0.5f, 0.5f));
	bullet.setPosition(0, 125);
	infoCompraBalas.setFont(*fuenteJuego);
	infoCompraBalas.setPosition(Vector2f(bullet.getTexture()->getSize().x, 125));
	
	compraBalas = make_unique<Boton>(Color(0, 255, 0, 120), Color(0, 255, 0, 210), "Buy bullets", "comprabalas", 200.f, 63.f, m_fuenteJuego, Vector2f(1280/2 - 200, 720/2), &soundsUsable);
	
	life.setTexture(lifeTexture);
	life.setScale(Vector2f(0.5f, 0.5f));
	life.setPosition(0, 200);
	precioVida = 15;
	vidaAComprar = 40;
	infoCompraVida.setFont(*fuenteJuego);
	infoCompraVida.setPosition(Vector2f(life.getTexture()->getSize().x, 200));
	
	compraVida = make_unique<Boton>(Color(255, 0, 0, 120), Color(255, 0, 0, 210), "Buy Life", "compravida", 200.f, 63.f, m_fuenteJuego, Vector2f(1280/2 + 200, 720/2), &soundsUsable);

	viewTienda = make_unique<View>(Vector2f(1280 /2, 720/2), Vector2f(1280, 720));
	
}


void EstadoTienda::TerminarEstado(){}
void EstadoTienda::ActualizarEstado(){
	availableCoins.setString("Coins Available: " + to_string((*jugador)->Monedas()));
	infoCompraBalas.setString("Price: " + to_string(precioBala) + " /// You Get: " + to_string(balasAComprar) + " Bullets /// Available: " + to_string((*jugador)->Vida()));
	infoCompraVida.setString("Price: " + to_string(precioVida) + " /// You Get: " + to_string(vidaAComprar) + " Life /// Available: " + to_string((*jugador)->Municion()));
	mousePos = Ventana()->mapPixelToCoords(Mouse::getPosition(*Ventana()));
	compraBalas->ActualizarBoton(mousePos);
	compraVida->ActualizarBoton(mousePos);
	if (Mouse::isButtonPressed(Mouse::Left)) cout<<"ok"<<endl;
	if (compraBalas->Presionado() && (*jugador)->Monedas() >= precioBala){
		cout<<"ok"<<endl;
		(*jugador)->Municion() += balasAComprar;
		(*jugador)->Monedas() -= precioBala;
		buySound.play();
		compraBalas->Presionado() = false;
	} else if (compraBalas->Presionado() && (*jugador)->Monedas() < precioBala){
		notBuySound.play();
		compraBalas->Presionado() = false;
	}
	
	if (compraVida->Presionado() && (*jugador)->Monedas() >= precioVida){
		cout<<"ok"<<endl;
		(*jugador)->Vida() += vidaAComprar;
		(*jugador)->Monedas() -= precioVida;
		buySound.play();
		compraVida->Presionado() = false;
	} else if (compraVida->Presionado() && (*jugador)->Monedas() < precioVida){
		notBuySound.play();
		compraVida->Presionado() = false;
	}
}
void EstadoTienda::DibujarEstado(){
	Ventana()->draw(coin);
	Ventana()->draw(availableCoins);
	Ventana()->draw(bullet);
	Ventana()->draw(life);
	
	Ventana()->setView(*viewTienda);
	compraBalas->DibujarBoton(Ventana());
	Ventana()->draw(infoCompraBalas);
	
	compraVida->DibujarBoton(Ventana());
	Ventana()->draw(infoCompraVida);
}
void EstadoTienda::ManejarEventoEstado(unique_ptr<Event>&e){
	if (e->type == Event::MouseButtonPressed){
		if (e->mouseButton.button == Mouse::Left){
			compraBalas->ManejarEventoBoton(mousePos, e);
			compraVida->ManejarEventoBoton(mousePos, e);
		}
	}
	if (e->type == Event::KeyPressed){
		if (e->key.code == Keyboard::Escape){
			estados->top()->Terminado() = true;
		}
	}

}
void EstadoTienda::CargarTexturas(){}
void EstadoTienda::InicializarDespuesDeCargarTexturas(){}
