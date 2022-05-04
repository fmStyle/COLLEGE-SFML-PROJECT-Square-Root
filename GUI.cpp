#include "GUI.h"

GUI::GUI(shared_ptr<RenderWindow>&ventana, shared_ptr<Jugador>&j, map<string, shared_ptr<Texture>>&textures, shared_ptr<Font>&m_fuenteJuego, shared_ptr<int>&nroRonda) {
	this->textures = textures;
	this->m_fuenteJuego = m_fuenteJuego;
	this->ventana = ventana;
//	this->jugador = jugador;
	jugador = j;
	this->nroRonda = nroRonda;
	v1 = make_shared<View>(Vector2f(jugador->Posicion()), Vector2f(1280.f, 720.f));
	vida.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y - 330));
	vida.setSize(Vector2f(jugador->Vida(), 10.f));
	vida.setFillColor(Color::Red);
	vida.setOutlineThickness(5.f);
	vida.setOutlineColor(Color::White);
	
	shopButtonPressed = false;
	
	rondaActual.setFont(*m_fuenteJuego);
	string auxString = "Round: " + to_string(*nroRonda) + string(" ");
	rondaActual.setString(auxString);
	rondaActual.setFillColor(Color::White);
	rondaActual.setOutlineThickness(5.f);
	rondaActual.setOutlineColor(Color::Black);
	rondaActual.setCharacterSize(35.f);
	
	
	monedasSprite.setTexture(*textures["moneda"]);
	monedasSprite.setOrigin((*textures["moneda"]).getSize().x/2, (*textures["moneda"]).getSize().y/2);
	monedasSprite.setScale(0.25, 0.25);
	monedas.setFont(*m_fuenteJuego);
	monedas.setString("Coins: " + to_string(jugador->Monedas()));
	monedas.setFillColor(Color::White);
	monedas.setOutlineThickness(5.f);
	monedas.setOutlineColor(Color::Black);
	monedas.setCharacterSize(25.f);
	
	
	municionesSprite.setTexture(*textures["municion"]);
	municionesSprite.setOrigin((*textures["municion"]).getSize().x/2, (*textures["municion"]).getSize().y/2);
	municionesSprite.setScale(0.25, 0.25);
	
	municiones.setFont(*m_fuenteJuego);
	municiones.setString("Ammo: " + to_string(jugador->Municion()));
	municiones.setFillColor(Color::White);
	municiones.setOutlineThickness(5.f);
	municiones.setOutlineColor(Color::Black);
	municiones.setCharacterSize(25.f);
	
	
	ActualGun.setFont(*m_fuenteJuego);
//	ActualGun.setString("Ammo: " + to_string(jugador->Municion()));
	ActualGun.setFillColor(Color(255, 255, 255, 120));
	ActualGun.setOutlineThickness(2.5f);
	ActualGun.setOutlineColor(Color(0, 0, 0, 120));
	ActualGun.setCharacterSize(15.f);
	
	shopButton.setTexture(*textures["ShopButton"]);
	shopButton.setScale(Vector2f(2.5f, 2.5f));
	
	
}
void GUI::ActualizarGUI(Vector2f posicionMouse){
//	vida.setPosition(worldPos);
	v1->setCenter(jugador->Posicion());
	vida.setSize(Vector2f(jugador->Vida() * 3, 10.f));
	
	vida.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y - 330));
	
	
	rondaActual.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y + 200));
	string auxString = "Round: " + to_string(*nroRonda);
	rondaActual.setString(auxString);
	
	monedasSprite.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y - 270));
	monedas.setString("Coins: " + to_string(jugador->Monedas()));
	monedas.setPosition(Vector2f(v1->getCenter().x - 570, v1->getCenter().y - 285));
	
	municionesSprite.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y - 232));
	municiones.setString("Ammo: " + to_string(jugador->Municion()));
	municiones.setPosition(Vector2f(v1->getCenter().x - 570, v1->getCenter().y - 250));
	
	ActualGun.setPosition(Vector2f(v1->getCenter().x - 600, v1->getCenter().y + 100));
	
	shopButton.setPosition(Vector2f(v1->getCenter().x + 500, v1->getCenter().y + 270));
	if (shopButton.getGlobalBounds().contains(posicionMouse)){
		shopButton.setColor(Color(255, 255, 255, 255));
		if (Mouse::isButtonPressed(Mouse::Left)){
			shopButtonPressed = true;
		}
	} else{
		shopButton.setColor(Color(255, 255, 255, 150));
	}
	
	switch(jugador->ModoDisparo()){
	case 0:
		ActualGun.setString("Gun in use: Machine Square Gun\nDamage: " + to_string(jugador->DatosActualesDisparo().m_danio) + "\nCritical Chance: " + to_string(
		100/jugador->DatosActualesDisparo().m_probabilidadCritico) + "%");
		break;
	case 1:
		ActualGun.setString("Gun in use: Shot Square Gun\nDamage: " + to_string(jugador->DatosActualesDisparo().m_danio) + "\nCritical Chance: " + to_string(
		100/jugador->DatosActualesDisparo().m_probabilidadCritico) + "%");
		break;
	}
	
}
void GUI::DibujarGUI(){
//	ventana->setView
	ventana->draw(vida);
	ventana->draw(rondaActual);
	ventana->draw(monedasSprite);
	ventana->draw(monedas);
	
	ventana->draw(municionesSprite);
	ventana->draw(municiones);
	ventana->draw(ActualGun);
	ventana->draw(shopButton);
}

