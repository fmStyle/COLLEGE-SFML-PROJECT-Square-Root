#include "EstadoTop10.h"

using namespace std;

bool comparador(datosFinales a, datosFinales b){
	return a.nroRonda > b.nroRonda;
}

EstadoTop10::EstadoTop10(shared_ptr<RenderWindow>&ventana, shared_ptr<Font>&fuenteJuego, stack<shared_ptr<Estado>>*estados) : Estado(ventana, fuenteJuego, estados){
	viewTop10 = make_unique<View>(Vector2f(1280/2, 720/2), Vector2f(1280, 720));
	arch.open("records.dat", ios::in | ios::binary | ios::ate);

	tamanoBinario = arch.tellg() / sizeof(datosFinales);
	arch.seekg(0);

	for (int i = 0; i<tamanoBinario; i++){
		datosFinales datos;
		arch.seekg(i*sizeof(datosFinales));
		arch.read(reinterpret_cast<char*>(&datos), sizeof(datos));
		DatosFinales.push_back(datos); 	
	}
	sort(DatosFinales.begin(), DatosFinales.end(), comparador);
	for (int i = 0; i<DatosFinales.size(); i++){
		puestos.push_back(Text());
		puestos[i].setFont(*m_fuenteJuego);
		puestos[i].setString("Top " + to_string(i + 1) + " /// Nombre: " + DatosFinales[i].nombre + " /// Ronda mas alta: " + to_string(DatosFinales[i].nroRonda));
		puestos[i].setPosition(Vector2f(260, i*70));
		puestos[i].setCharacterSize(30.f);
	}
}


void EstadoTop10::TerminarEstado(){}
void EstadoTop10::ActualizarEstado(){}
void EstadoTop10::DibujarEstado(){
	Ventana()->setView(*viewTop10);
	for (auto x : puestos){
		Ventana()->draw(x);
	}
}
void EstadoTop10::ManejarEventoEstado(unique_ptr<Event>&e){
	if (e->type == Event::KeyPressed){
		if (e->key.code == Keyboard::Escape){
			estados->top()->Terminado() = true;
		}
	}
}
void EstadoTop10::CargarTexturas(){}
void EstadoTop10::InicializarDespuesDeCargarTexturas(){}

