#include "EstadoJuego.h"
#include <iostream>

EstadoJuego::EstadoJuego(shared_ptr<RenderWindow>&ventana, shared_ptr<Font> &fuenteJuego, stack<shared_ptr<Estado>>*estados) : Estado(ventana, fuenteJuego, estados) {
	
	jugador = make_shared<Jugador>(50.f, Ventana(), 100.f, balas, &soundsUsable);
	
	nroRonda = make_unique<int>(1);
	v1 = make_shared<View>(Vector2f(jugador->Posicion()), Vector2f(1280.f, 720.f));
	
	duracionAnimacionCritico = 1.5f;
	ejecutarReloj = true;

	nroEnemigosASpawnear = 3;
	nroEnemigosAIncrementar = 2;
	nroEnemigosAsesinados = 0;
	
	delaySpawn.restart();
	correrUnaVezClock = false;
	correrUnaVezMuerte = false;
	
	GameOver.setFont(*m_fuenteJuego);
	GameOver.setString("Game Over!");
	GameOver.setCharacterSize(150.f);
	
	ejecutarUnaVezMuerte = false;
}

void EstadoJuego::TerminarEstado(){
	terminado = true;
}

void EstadoJuego::ActualizarEstado(){
	posicionMouse = Ventana()->mapPixelToCoords(Mouse::getPosition(*Ventana()));
	
	/// prueba
	
	int counter = 0;
	for (Bala &x : balas){
		x.ActualizarMovimientoBala();
		if (x.Terminado()) balas.erase(balas.begin() + counter);
		for (shared_ptr<Entidad>enemigo : enemigos){
			if (Colisiona(x.CuadradoBala().getGlobalBounds(), enemigo->coordenadasGlobales())){
				if (enemigo->Vida() > 0){
					if (x.Critico() && !x.Pego()){
						AnimacionCritico(x.PosicionBala());
						soundsUsable["criticalAttackSound"]->play();
					}
					x.Pego() = true;
					enemigo->FeedbackBala(x.CuadradoBala().getPosition(), x.Datos().m_danio);
					enemigo->Vida() -= x.Datos().m_danio;
					enemigo->ActualizarBarraDeVida();
				}
				else{
					if (enemigo->runOnceForMain == false){
						nroEnemigosAsesinados++;
						if (enemigo->tag == "squarex"){
							for (int i = 0; i<rand()%4; i++){
								//cout<<"ok"<<endl;
								pickups.push_back(make_shared<PickUpVida>(*textures["hearth"], enemigo->Posicion(), jugador, &textosAnimados, m_fuenteJuego, soundsUsable));
							}
						}
						if (enemigo->tag == "littleboy"){
							for (int i = 0; i<rand()%4; i++){
								pickups.push_back(make_shared<MunicionPickup>(*textures["municion"], enemigo->Posicion(), jugador, &textosAnimados, m_fuenteJuego, soundsUsable));
							}
						}
						for (int i = 0; i<rand()%4; i++){
							pickups.push_back(make_shared<Moneda>(*textures["moneda"], enemigo->Posicion(), jugador, &textosAnimados, m_fuenteJuego, soundsUsable));
						}
						enemigo->runOnceForMain = true;
						continue;
					}
				}
			}
		}
		counter++;
	}
	
	this->anguloAMouse = jugador->AnguloAMouse();
	
	
	/// Actualizacion de camara
	
	/// Top left corner
	if ((jugador->Posicion().x - 1280/2 < tiles->topCoordinate.x) && (jugador->Posicion().y - 720/2 < tiles->topCoordinate.y)){
		v1->setCenter(Vector2f(tiles->topCoordinate.x + 1280/2, tiles->topCoordinate.y + 720/2));
	}
	bool leftDownCorner = false;
	if ((jugador->Posicion().x - 1280/2 < tiles->topCoordinate.x) && !(jugador->Posicion().y - 720/2 < tiles->topCoordinate.y)){
		if (jugador->Posicion().y + 720/2 > tiles->downCoordinate.y){
			cout<<"OK"<<endl;
			v1->setCenter(Vector2f(tiles->topCoordinate.x + 1280/2, tiles->downCoordinate.y - 720/2));
			leftDownCorner = true;
		}
		else v1->setCenter(Vector2f(tiles->topCoordinate.x + 1280/2, jugador->Posicion().y));
	}
	if (!(jugador->Posicion().x - 1280/2 < tiles->topCoordinate.x) && (jugador->Posicion().y - 720/2 < tiles->topCoordinate.y)){
		v1->setCenter(Vector2f(jugador->Posicion().x, tiles->topCoordinate.y + 720/2));
		
	}
	if ((jugador->Posicion().x + 1280/2 > tiles->downCoordinate.x) && (jugador->Posicion().y + 720/2 > tiles->downCoordinate.y)){
		v1->setCenter(Vector2f(tiles->downCoordinate.x - 1280/2, tiles->downCoordinate.y - 720/2));
	}
	if ((jugador->Posicion().x + 1280/2 > tiles->downCoordinate.x) && !(jugador->Posicion().y + 720/2 > tiles->downCoordinate.y)){
		if ((jugador->Posicion().y - 720/2 < tiles->topCoordinate.y)){
			v1->setCenter(Vector2f(tiles->downCoordinate.x - 1280/2, tiles->topCoordinate.y + 720/2));
		}
		else v1->setCenter(Vector2f(tiles->downCoordinate.x - 1280/2, jugador->Posicion().y));
	}
	if (!(jugador->Posicion().x + 1280/2 > tiles->downCoordinate.x) && (jugador->Posicion().y + 720/2 > tiles->downCoordinate.y)){
		if (!leftDownCorner)
		v1->setCenter(Vector2f(jugador->Posicion().x, tiles->downCoordinate.y - 720/2));
	}
	if (!(jugador->Posicion().x - 1280/2 < tiles->topCoordinate.x) && !(jugador->Posicion().y - 720/2  < tiles->topCoordinate.y)){
		if (!(jugador->Posicion().x + 1280/2 > tiles->downCoordinate.x) && !(jugador->Posicion().y + 720/2 > tiles->downCoordinate.y)){
			if (!leftDownCorner)
			v1->setCenter(jugador->Posicion());
		}
	}
	
	/// Muerte del jugador
	if(jugador->Vida() <= 0){
		if (!correrUnaVezMuerte){
			muerte.restart();
			jugador->Muerto() = true;
			
			EfectoMuerte.setSize(Vector2f(1280, 720));
			EfectoMuerte.setOrigin(1280/2, 720/2);
			EfectoMuerte.setPosition(v1->getCenter());
			
			GameOver.setPosition(Vector2f(v1->getCenter().x - 430.f, v1->getCenter().y - 250.f));
			
			VolverAJugar = make_unique<Boton>(Color(255, 255, 255, 140), Color(255, 255, 255, 210), "Try Again", "tryagain", 300, 100, m_fuenteJuego, Vector2f(v1->getCenter().x, v1->getCenter().y + 100), &soundsUsable);
			
			Menu = make_unique<Boton>(Color(255, 220, 255, 140), Color(255, 220, 255, 210), "Menu", "mainmenu", 300, 100, m_fuenteJuego, Vector2f(v1->getCenter().x, v1->getCenter().y + 220), &soundsUsable);
			
			correrUnaVezMuerte = true;
			lapizEscribirDatos.setPosition(Vector2f(v1->getCenter().x + 500, v1->getCenter().y - 330));
			lapizEscribirDatos.setScale(Vector2f(0.5f, 0.5f));
		}
		
		VolverAJugar->ActualizarBoton(posicionMouse);
		Menu->ActualizarBoton(posicionMouse);
		
		/// Actualizacion del lapiz
		if (lapizEscribirDatos.getGlobalBounds().contains(posicionMouse)){
			lapizEscribirDatos.setColor(Color(255, 255, 255, 255));
			if (Mouse::isButtonPressed(Mouse::Left)){
				estados->push(make_shared<EstadoGuardarPuntajes>(Ventana(), m_fuenteJuego, estados, *nroRonda));
				estados->top()->CargarTexturas();
				estados->top()->InicializarDespuesDeCargarTexturas();
			}
		} else{
			lapizEscribirDatos.setColor(Color(255, 255, 255, 150));
		}
		
		
	}else{
		jugador->ActualizarEntidad();
	}
	
	jugador->Mover();
	if (jugador->Muerto()){
		if (!ejecutarUnaVezMuerte){
			soundsUsable["deathSound"]->play();
			ejecutarUnaVezMuerte = true;
		}
		if(muerte.getElapsedTime().asSeconds() < 2.f){
			float aux = -255/2 * muerte.getElapsedTime().asSeconds() + 255;
			float aux2 = 130/2 * muerte.getElapsedTime().asSeconds();
			float aux3 = 255/2 * muerte.getElapsedTime().asSeconds();
			
			jugador->RectanguloJugador().setFillColor(Color(aux, aux, aux, aux));
			jugador->RectanguloJugador().setOutlineColor(Color(aux, aux, aux, aux));
			
			EfectoMuerte.setFillColor(Color(255, 0, 0, aux2));
			GameOver.setFillColor(Color(255, 255, 255, aux3));
		}
	} 
	
	if (tiles->UpdateTilesAndPlayer(jugador)){
		soundsUsable["hitten"]->play();
	}
	/// Actualizacion De Enemigos
	
	for (int i = 0; i<enemigos.size(); ++i){
		if (enemigos[i]->deadDead){
			enemigos.erase(enemigos.begin() + i);
			continue;
		}
		enemigos[i]->ActualizarEntidad();
		enemigos[i]->Mover();
	}
	
//	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
//		cout<<"Estado Terminado"<<endl;
//		TerminarEstado();
//	}
	
	if (Mouse::isButtonPressed(Mouse::Left)){
		if (jugador->DatosActualesDisparo().m_automatico){
			jugador->Disparar(balas);
		}
	}
	
	/// Actualizacion de los textos
	for (auto it = textosAnimados.begin(); it!=textosAnimados.end(); ++it){
		it->ActualizarMovimientoTexto();
//		if (it->Terminado() && !textosAnimados.empty()) textosAnimados.pop_front();
	}
	
	auto iteratorAnimatedText =  remove_if(textosAnimados.begin(), textosAnimados.end(), [&](TextoAnimado t) -> bool{
		return (t.Terminado() && !textosAnimados.empty());
	});
	textosAnimados.erase(iteratorAnimatedText, textosAnimados.end());
	
	/// Chequeo de los items pickupeables
	for (auto it = pickups.begin(); it!=pickups.end(); ++it){
		(*it)->ActualizarPickup();
	}
//	auto checkAgarrado = [&](shared_ptr<Pickups> a) -> bool {
//		return a->Agarrado();
//	};
	
	auto iteratorPickups = remove_if(pickups.begin(), pickups.end(), [&](shared_ptr<Pickups> a) -> bool {
		return a->Agarrado();
	});
	pickups.erase(iteratorPickups, pickups.end());
	
	/// Manejo de rondas
	
	if (!jugador->Muerto()){
		if (delaySpawn.getElapsedTime().asSeconds() > 2.f && nroEnemigosAsesinados < nroEnemigosASpawnear) {
			correrUnaVezClock = false;
			int aux = rand()%2;
			Vector2f auxVec;
			float xAux = -1500/2 + rand()%3000/2;
			float yAux;
			if (xAux < -1280 || xAux > 1280){
				int aux2 = rand()%2;
				switch (aux){
				case 0:
					yAux = -1500;
					break;
				case 1:
					yAux = 1500;
				}
			} else{
				yAux = -1500/2 + rand()%1500;
			}
			auxVec.x = v1->getCenter().x + xAux;
			auxVec.y = v1->getCenter().y + yAux;
			switch (aux){
			case 0:
				enemigos.push_back(make_shared<Squarex>(20.f + float(rand()%20), Ventana(), 100.f, jugador, auxVec, &soundsUsable));
				break;
			case 1:
				enemigos.push_back(make_shared<LittleBoy>(25.f + float(rand()%20), Ventana(), 100.f, jugador, auxVec, &soundsUsable));
				break;
			}
			
			delaySpawn.restart();
		} 
		if (nroEnemigosAsesinados >= nroEnemigosASpawnear && enemigos.size() == 0){
			if (!correrUnaVezClock){
				roundDelay.restart();
				(*nroRonda)++;
			}
			correrUnaVezClock = true;
			if (roundDelay.getElapsedTime().asSeconds() > 5.f){
				nroEnemigosAsesinados = 0;
				nroEnemigosASpawnear += nroEnemigosAIncrementar;
				nroEnemigosAIncrementar += int(rand()%3);
			}
		}
	}
	
	
	gui->ActualizarGUI(posicionMouse);
	if (gui->shopButtonPressed){
		estados->push(make_shared<EstadoTienda>(Ventana(), m_fuenteJuego, estados, &jugador, (*textures["moneda"]), (*textures["municion"]), (*textures["hearth"]), *soundsUsable["BuySound"], *soundsUsable["NotBuySound"]));
		estados->top()->CargarTexturas();
		estados->top()->InicializarDespuesDeCargarTexturas();
		gui->shopButtonPressed = false;
	}
	
	if (jugador->Muerto() && Menu->Presionado()){
		estados->top()->Terminado() = true;
	}
	if (jugador->Muerto() && VolverAJugar->Presionado()){
		estados->top()->Terminado() = true;
		estados->push(make_shared<EstadoJuego>(Ventana(), m_fuenteJuego, estados));
		estados->top()->CargarTexturas();
		estados->top()->InicializarDespuesDeCargarTexturas();
		VolverAJugar->Presionado() = false;
	}
}

void EstadoJuego::DibujarEstado(){
	Ventana()->setView(*v1);
	
	tiles->DrawTiles(Ventana());
	
	for (shared_ptr<Pickups>p : pickups){
		p->DibujarPickup(Ventana());
	}
	
	for (shared_ptr<Entidad>enemigo : enemigos){
		enemigo->DibujarEntidad();
	}
	
	jugador->DibujarEntidad();
	for (Bala &x : balas){
		x.DibujarBala(Ventana());
	}
	
	for (TextoAnimado &t : textosAnimados){
		t.DibujarTexto(Ventana());
	}
	
	if (!jugador->Muerto()){
		Ventana()->setView(*(gui->ViewGUI()));
		gui->DibujarGUI();
	} else{
		Ventana()->draw(EfectoMuerte);
		Ventana()->draw(GameOver);
		VolverAJugar->DibujarBoton(Ventana());
		Menu->DibujarBoton(Ventana());
		Ventana()->draw(lapizEscribirDatos);
	}
}
void EstadoJuego::ManejarEventoEstado(unique_ptr<Event>&e){
	if (jugador->Muerto()){
		VolverAJugar->ManejarEventoBoton(posicionMouse, e);
		Menu->ManejarEventoBoton(posicionMouse, e);
	} else{
		if (e->type == Event::MouseButtonPressed){
			if (e->mouseButton.button == Mouse::Left){
				if (!jugador->DatosActualesDisparo().m_automatico){
					jugador->Disparar(balas);
					jugador->DatosActualesDisparo().relojCadencia.restart();
				}
			}
			/// Debug
			if (e->mouseButton.button == Mouse::Right){
				
			}
		}
		if (e->type == Event::KeyPressed){
			if (e->key.code == Keyboard::Num1){
				jugador->ModoDisparo() = 0;
			}
			if (e->key.code == Keyboard::Num2){
				jugador->ModoDisparo() = 1;
			}
//			if (e->key.code == Keyboard::Num3){
//				estados->push(make_shared<EstadoTienda>(Ventana(), m_fuenteJuego, estados));
//				estados->top()->CargarTexturas();
//				estados->top()->InicializarDespuesDeCargarTexturas();
//			}
		}
	}
}

void EstadoJuego::AnimacionCritico(Vector2f PosicionDePegada){
	textosAnimados.push_back(TextoAnimado(PosicionDePegada, Color::Red, 27.f, "Critical!", m_fuenteJuego, 0.5f));
}

void EstadoJuego::CargarTexturas(){
	
	/// Carga de texturas y sprites
	textures["hearth"] = make_shared<Texture>();
	textures["hearth"]->loadFromFile("hearth.png");
	
	textures["moneda"] = make_shared<Texture>();
	textures["moneda"]->loadFromFile("moneda.png");
	
	textures["municion"] = make_shared<Texture>();
	textures["municion"]->loadFromFile("municion.png");
	
	textures["lapiz"] = make_shared<Texture>();
	textures["lapiz"]->loadFromFile("lapiz.png");
	
	textures["ShopButton"] = make_shared<Texture>();
	textures["ShopButton"]->loadFromFile("IconoShop.png");
	
	textures["TileBackground1"] = make_shared<Texture>();
	textures["TileBackground1"]->loadFromFile("Tiles/TileBackground4.png");
	
	textures["TileBackground2"] = make_shared<Texture>();
	textures["TileBackground2"]->loadFromFile("Tiles/TileBackground5.png");
	
	textures["TileBackground3"] = make_shared<Texture>();
	textures["TileBackground3"]->loadFromFile("Tiles/TileBackground6.png");
	
	textures["DangerTile1"] = make_shared<Texture>();
	textures["DangerTile1"]->loadFromFile("Tiles/DangerTile1.png");
	
	textures["DangerTile2"] = make_shared<Texture>();
	textures["DangerTile2"]->loadFromFile("Tiles/DangerTile2.png");
	
	textures["DangerTile3"] = make_shared<Texture>();
	textures["DangerTile3"]->loadFromFile("Tiles/DangerTile3.png");
	textures["DangerTile4"] = make_shared<Texture>();
	textures["DangerTile4"]->loadFromFile("Tiles/DangerTile4.png");
	
	textures["DecoTile1"] = make_shared<Texture>();
	textures["DecoTile1"]->loadFromFile("Tiles/DecoTile1.png");
	
	textures["DecoTile2"] = make_shared<Texture>();
	textures["DecoTile2"]->loadFromFile("Tiles/DecoTile2.png");
	
	textures["DecoTile3"] = make_shared<Texture>();
	textures["DecoTile3"]->loadFromFile("Tiles/DecoTile3.png");
	
	textures["DecoTile4"] = make_shared<Texture>();
	textures["DecoTile4"]->loadFromFile("Tiles/DecoTile4.png");
	
	textures["DecoTile5"] = make_shared<Texture>();
	textures["DecoTile5"]->loadFromFile("Tiles/DecoTile5.png");
	
//	textures["TileBackground1"] = make_shared<Texture>();
//	textures["TileBackground1"]->loadFromFile("TileBackground1.png");
	
	/// Carga de sonidos
	sounds["criticalAttackSound"] = make_shared<SoundBuffer>();
	sounds["criticalAttackSound"]->loadFromFile("Sounds/criticalAttack.ogg");
	soundsUsable["criticalAttackSound"] = make_shared<Sound>(*sounds["criticalAttackSound"]);
	
	sounds["ammoUpSound"] = make_shared<SoundBuffer>();
	sounds["ammoUpSound"]->loadFromFile("Sounds/ammoUpSound.ogg");
	soundsUsable["ammoUpSound"] = make_shared<Sound>(*sounds["ammoUpSound"]);
	
	sounds["coinUpSound"] = make_shared<SoundBuffer>();
	sounds["coinUpSound"]->loadFromFile("Sounds/coinUpSound.ogg");
	soundsUsable["coinUpSound"] = make_shared<Sound>(*sounds["coinUpSound"]);
	
	sounds["deathSound"] = make_shared<SoundBuffer>();
	sounds["deathSound"]->loadFromFile("Sounds/deathSound.ogg");
	soundsUsable["deathSound"] = make_shared<Sound>(*sounds["deathSound"]);
	
	sounds["healthUpSound"] = make_shared<SoundBuffer>();
	sounds["healthUpSound"]->loadFromFile("Sounds/healthUpSound.ogg");
	soundsUsable["healthUpSound"] = make_shared<Sound>(*sounds["healthUpSound"]);
	
	sounds["hitten"] = make_shared<SoundBuffer>();
	sounds["hitten"]->loadFromFile("Sounds/hitten.ogg");
	soundsUsable["hitten"] = make_shared<Sound>(*sounds["hitten"]);
	
	sounds["hitten"] = make_shared<SoundBuffer>();
	sounds["hitten"]->loadFromFile("Sounds/hitten.ogg");
	soundsUsable["hitten"] = make_shared<Sound>(*sounds["hitten"]);
	
	sounds["machineGunShotSound"] = make_shared<SoundBuffer>();
	sounds["machineGunShotSound"]->loadFromFile("Sounds/machineGunShotSound.ogg");
	soundsUsable["machineGunShotSound"] = make_shared<Sound>(*sounds["machineGunShotSound"]);
	
	sounds["shotGunShotSound"] = make_shared<SoundBuffer>();
	sounds["shotGunShotSound"]->loadFromFile("Sounds/shotGunShotSound.ogg");
	soundsUsable["shotGunShotSound"] = make_shared<Sound>(*sounds["shotGunShotSound"]);
	
	sounds["BuySound"] = make_shared<SoundBuffer>();
	sounds["BuySound"]->loadFromFile("Sounds/moneyupRandSound5.ogg");
	soundsUsable["BuySound"] = make_shared<Sound>(*sounds["BuySound"]);
	
	sounds["NotBuySound"] = make_shared<SoundBuffer>();
	sounds["NotBuySound"]->loadFromFile("Sounds/NotBuySound.ogg");
	soundsUsable["NotBuySound"] = make_shared<Sound>(*sounds["NotBuySound"]);
}

void EstadoJuego::InicializarDespuesDeCargarTexturas(){
	gui = make_unique<GUI>(Ventana(), jugador, textures, m_fuenteJuego, nroRonda);
	lapizEscribirDatos.setTexture(*textures["lapiz"]);
	
	vector<TileInfo>aux;
	aux.push_back(TileInfo("TileBackground1", 0, 64));
//	aux.push_back(TileInfo("TileBackground2", 0, 64));
	aux.push_back(TileInfo("TileBackground3", 0, 64));
	aux.push_back(TileInfo("DangerTile1", 2, 64));
	aux.push_back(TileInfo("DangerTile2", 1, 64));
	aux.push_back(TileInfo("DangerTile3", 1, 64));
	aux.push_back(TileInfo("DangerTile4", 1, 64));
	aux.push_back(TileInfo("DecoTile1", 2, 64));
	aux.push_back(TileInfo("DecoTile2", 2, 64));
	aux.push_back(TileInfo("DecoTile3", 2, 64));
	aux.push_back(TileInfo("DecoTile4", 2, 64));
	aux.push_back(TileInfo("DecoTile5", 2, 64));
	
	tiles = make_unique<TileEngine>(64.f, 20, &textures);
	tiles->CreateTiles(15, 20, aux, 2);
}

EstadoJuego::~EstadoJuego() {
	
}

