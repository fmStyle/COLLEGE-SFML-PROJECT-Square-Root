#include "Juego.h"


using namespace std;

/// Constructor
Juego::Juego() {
	IniciarVentana();
	IniciarEstados();
	IniciarEvento();
}

/// Inicializadores
void Juego::IniciarVentana(){
	
	srand(time(0));
	
	ifstream window_conf("Config/window.ini");
	
	string window_name = "SQUARE ROOT (Pre-Alpha)";
	VideoMode v(1280, 720);
	int framerate = 60;
	bool vertical_sync = false;
	
	vector<string>randomNames = {"The path of the square", "Cubes are evil", "The magic of roots!", "Who said that a square could shoot", "Imagine having a complex area!"};
	
	if (window_conf.is_open()){
		getline(window_conf, window_name);
		window_conf>>v.width>>v.height;
		window_conf>>framerate;
		window_conf>>vertical_sync;
	}
	
	window_conf.close();
	
	ventana = make_shared<RenderWindow>(v,window_name + " - " + randomNames[rand()%(randomNames.size())]);
	ventana->setFramerateLimit(framerate);
	ventana->setVerticalSyncEnabled(vertical_sync);
	
	fuenteJuego = make_shared<Font>();
	fuenteJuego->loadFromFile("upheavtt.ttf");	
	
	MainMusic.openFromFile("Sounds/squareRootMainMusic1.ogg");
//	MainMusic.setVolume(-20.f);
	MainMusic.play();
}

void Juego::IniciarEvento(){
	e = make_unique<Event>();
}

void Juego::IniciarEstados(){
//	this->Estados.push(make_shared<EstadoJuego>(ventana, fuenteJuego, Estados));
	this->Estados.push(make_shared<MenuPrincipal>(ventana, fuenteJuego, &this->Estados));
	this->Estados.top()->CargarTexturas();
	this->Estados.top()->InicializarDespuesDeCargarTexturas();
}

/// Funciones
void Juego::GameLoop(){
	
	this->ManejarEventos();
	
	if (!this->Estados.empty()){
		this->Estados.top()->ActualizarEstado();
		if (this->Estados.top()->Terminado()) {
//			this->Estados.top()->CargarTexturas();
			// Si se quita el primer estado se cierra el juego
			if (this->Estados.size() == 1) ventana->close();
			
			// Si no, no se vuelve al estado anterior
			this->Estados.pop();
		}
	}
	
}

void Juego::ManejarEventos(){
	while (ventana->pollEvent(*e)){
		if (e->type == Event::Closed){
			ventana->close();
			std::cout<<"Juego Terminado"<<std::endl;
		}
		/// Se ejecuta el código que necesite el estado
		Estados.top()->ManejarEventoEstado(e);
	}
	
}

void Juego::Dibujar(){
	ventana->clear();
	
	if (!this->Estados.empty()){
		this->Estados.top()->DibujarEstado();
	}
	
	ventana->display();
}

void Juego::CorrerJuego(){
	std::cout<<"Juego Inicializado"<<std::endl;
	
	
	while (ventana->isOpen()){
		
		GameLoop();
		
		Dibujar();
	}
}


/// Destructor
Juego::~Juego() {
	
}

