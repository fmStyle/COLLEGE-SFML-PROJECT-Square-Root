#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados) : Estado(ventana, fuenteJuego, estados) {
	
	viewMenu = make_unique<View>(Vector2f(1280/2, 720/2), Vector2f(1280, 720));
	
	squareRoot.setFont(*m_fuenteJuego);
	squareRoot.setString("Square Root!");
	squareRoot.setCharacterSize(150.f);
	squareRoot.setPosition(Vector2f(1280/2 - 475, 720/2 - 275));
	squareRoot.setFillColor(Color::White);
	squareRoot.setOutlineColor(Color::Black);
	squareRoot.setOutlineThickness(15.f);
	
	jugar = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Play!", "escenaJuego", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2), &soundsUsable);
	
//	opciones = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Options", "opciones", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2 + 125), &soundsUsable);
	
	salir = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Exit :(", "salir", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2 + 150), &soundsUsable);
	
}

void MenuPrincipal::TerminarEstado(){
	terminado = true;
}
void MenuPrincipal::ActualizarEstado(){
	posicionMouse = Ventana()->mapPixelToCoords(Mouse::getPosition(*Ventana()));
	
	jugar->ActualizarBoton(posicionMouse);
	
//	opciones->ActualizarBoton(posicionMouse);
	

	
	salir->ActualizarBoton(posicionMouse);
	if (jugar->Presionado()){
		soundsUsable["selectionSound"]->play();
		estados->push(make_shared<EstadoJuego>(m_ventana, m_fuenteJuego, estados));
		estados->top()->CargarTexturas();
		estados->top()->InicializarDespuesDeCargarTexturas();
		jugar->Presionado() = false;
	}
//	if (opciones->Presionado()){
//		/// En trabajo!
//	}
	
	if (salir->Presionado()) estados->top()->Terminado() = true;
//	TextoJugar.setPosition(Vector2f(BotonJugar.getPosition().x - 84.f, BotonJugar.getPosition().y - 50.f));
	
	if (leaderBoards.getGlobalBounds().contains(posicionMouse)){
		leaderBoards.setColor(Color(255, 255, 255, 255));
		if (Mouse::isButtonPressed(Mouse::Left)){
			estados->push(make_shared<EstadoTop10>(Ventana(), m_fuenteJuego, estados));
			estados->top()->CargarTexturas();
			estados->top()->InicializarDespuesDeCargarTexturas();
		}
	} else{
		leaderBoards.setColor(Color(255, 255, 255, 150));
	}
	
	//cout<<to_string(posicionMouse.x)<<" "<<to_string(posicionMouse.y)<<endl;
}
void MenuPrincipal::DibujarEstado(){
//	Ventana()->draw(BotonJugar);
//	Ventana()->draw(TextoJugar);
	
	Ventana()->setView(*viewMenu);
	
	Ventana()->draw(squareRoot);
	
	jugar->DibujarBoton(Ventana());
	
//	opciones->DibujarBoton(Ventana());
	
	salir->DibujarBoton(Ventana());
	
	Ventana()->draw(leaderBoards);
	
	
}
void MenuPrincipal::ManejarEventoEstado(unique_ptr<Event>&e){
	if (e->type == Event::MouseButtonPressed){
		if (e->mouseButton.button == Mouse::Left){
			jugar->ManejarEventoBoton(posicionMouse, e);
//			opciones->ManejarEventoBoton(posicionMouse, e);
			salir->ManejarEventoBoton(posicionMouse, e);
//			estados->push(make_shared<EstadoJuego>(m_ventana, m_fuenteJuego, estados));
//			estados->top()->CargarTexturas();
//			estados->top()->InicializarDespuesDeCargarTexturas();
		}
		/// Debug
		if (e->mouseButton.button == Mouse::Right){
			
		}
	}
}
void MenuPrincipal::CargarTexturas(){
	textures["trofeo"] = make_shared<Texture>();
	textures["trofeo"]->loadFromFile("trofeo.png");
	
	sounds["selectionSound"] = make_shared<SoundBuffer>();
	sounds["selectionSound"]->loadFromFile("Sounds/selectionSound.ogg");
	soundsUsable["selectionSound"] = make_shared<Sound>(*sounds["selectionSound"]);
}
void MenuPrincipal::InicializarDespuesDeCargarTexturas(){
	squareRoot.setFont(*m_fuenteJuego);
	squareRoot.setString("Square Root!");
	squareRoot.setCharacterSize(150.f);
	squareRoot.setPosition(Vector2f(1280/2 - 475, 720/2 - 275));
	squareRoot.setFillColor(Color::White);
	squareRoot.setOutlineColor(Color::Black);
	squareRoot.setOutlineThickness(15.f);
	
	leaderBoards.setTexture(*textures["trofeo"]);
	leaderBoards.setPosition(Vector2f(1150, 580));
	leaderBoards.setScale(Vector2f(0.5, 0.5));
	
	jugar = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Play!", "escenaJuego", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2), &soundsUsable);
	
//	opciones = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Options", "opciones", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2 + 125), &soundsUsable);
	
	salir = make_unique<Boton>(Color(255, 220, 255, 180), Color(255, 220, 255, 230), "Exit :(", "salir", 400, 100, m_fuenteJuego, Vector2f(1280/2, 720/2 + 150), &soundsUsable);
}
