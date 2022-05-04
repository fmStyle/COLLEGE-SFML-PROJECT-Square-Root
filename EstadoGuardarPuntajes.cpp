#include "EstadoGuardarPuntajes.h"
#include <cstring>
using namespace std;

EstadoGuardarPuntajes::EstadoGuardarPuntajes(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados, int &nroRonda) : Estado(ventana, fuenteJuego, estados) {
	playerText.setFont(*m_fuenteJuego);
	Guide.setFont(*m_fuenteJuego);
	Guide.setString("Enter your name (Press Enter to accept)");
	Guide.setPosition(Vector2f(1280/2 - 400, 720/2 - 100));
	
	playerText.setPosition(Vector2f(1280/2 - 300, 720/2));
	viewGuardarPuntajes = make_unique<View>(Vector2f(1280/2, 720/2), Vector2f(1280, 720));

	datos.nroRonda = nroRonda;
	
	
	string x;
	int counter = 0;
}

void EstadoGuardarPuntajes::TerminarEstado(){
	
}
void EstadoGuardarPuntajes::ActualizarEstado(){
	
}
void EstadoGuardarPuntajes::DibujarEstado(){
	Ventana()->setView(*viewGuardarPuntajes);
	Ventana()->draw(playerText);
	Ventana()->draw(Guide);
}
void EstadoGuardarPuntajes::ManejarEventoEstado(unique_ptr<Event>&e){
	if (e->type == Event::KeyPressed){
		if (e->key.code == Keyboard::Return){
			/// Aca se guardan los datos del jugador 
			string s = playerInput;
			strcpy(datos.nombre, s.c_str());
			arch.open("records.dat", ios::out | ios::binary | ios::app);
			if (arch.is_open()){
				arch.write(reinterpret_cast<char*>(&datos), sizeof(datos));
				arch.close();
			} 
			estados->pop();
		}
	}
	if (e->type == Event::TextEntered)
	{
		playerInput +=e->text.unicode;
		playerText.setString(playerInput);
	}
}
void EstadoGuardarPuntajes::CargarTexturas(){
	
}
void EstadoGuardarPuntajes::InicializarDespuesDeCargarTexturas(){
	
}
