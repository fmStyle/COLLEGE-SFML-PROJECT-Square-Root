#include "LittleBoy.h"
#include "FuncionesAnguloDistancia.h"

LittleBoy::LittleBoy(float size, shared_ptr<RenderWindow>&ventana,float life, shared_ptr<Jugador>&jugador, Vector2f InitialPos, map<string, shared_ptr<Sound>> *soundsUsable) : Entidad(size, ventana, life, soundsUsable){
	//	this->jugador = jugador;
	
	this->tag = "littleboy";
	
	runOnceForMain = false;
	
	initLife = life;
	hitten = false;
	
	speed = 15;
	CuadradoPrincipal.setPosition(InitialPos);
	CuadradoPrincipal.setSize(Vector2f(size, size));
	CuadradoPrincipal.setOrigin(Vector2f(size/2, size/2));
	
	
	CuadradoPrincipal.setFillColor(Color::Red);
	
	CuadradoPrincipal.setOutlineThickness(size*7.5/60);
	CuadradoPrincipal.setOutlineColor(Color::White);
	
	for (int i = 0; i<2; i++){
		CuadradosSecundarios.push_back(RectangleShape(Vector2f(size/2, size/2)));
		CuadradosSecundarios[i].setOrigin(Vector2f(size/4, size/4));
		CuadradosSecundarios[i].setFillColor(Color(255, 0, 0));
		
		CuadradosSecundarios[i].setOutlineThickness(7.5f);
		CuadradosSecundarios[i].setOutlineColor(Color::White);
		//		CuadradosSecundarios[i].setSize(Vector2f(size/2, size/2));
	}
	
	radio = sqrt((pow(size*5/6, 2) + pow(size*5/6, 2)));
	c1.restart();
	
	speedX = 0;
	speedY = 0;
	
	life = 100.f;
	lifeShape.setSize(Vector2f((life * size)*2/initLife, size * 1/4));
	lifeShape.setOrigin(Vector2f(life/2, (life*2/16)/2));
	lifeShape.setFillColor(Color::Red);
	lifeShape.setOutlineThickness(5.f); lifeShape.setOutlineColor(Color::White);
	
	dead = false; deadDead = false;
	
	runOnce = 0;
	runOnce2 = 0;
	runOnce3 = 0;
	
	this->jugador = jugador;
}

void LittleBoy::Mover(){
	
	
	//		CuadradoPrincipal.move(cos(AnguloAJugador*M_PI/180) * speed, -sin(AnguloAJugador*M_PI/180)* speed); 
	
	/// Inteligencia del bicho
	if (!dead){
		//		if (speedX > 30.f) speedX = 30;
		//		if (speedY > 30.f) speedY = 30;
		if (!hitten && DistanciaAJugador < 1200.f && DistanciaAJugador > 300.f){
			speedX += cos(AnguloAJugador*M_PI/180) *1.2;
			speedY += sin(AnguloAJugador*M_PI/180) * 2.3;
			
			CuadradoPrincipal.move(speedX, -speedY);
			
			runOnce = 0;
			
		}else if (!hitten && DistanciaAJugador <= 300.f){
			if (jugador->Muerto()){
				speedX += cos(rand()%10*M_PI/180) * 4.f;
				speedY += sin(rand()%10*M_PI/180) * 4.f;
			} else{
				speedX += cos(AnguloAJugador*M_PI/180) * 2.8f;
				speedY += sin(AnguloAJugador*M_PI/180) * 2.8f;
			}
			CuadradoPrincipal.move(speedX, -speedY);
		}
		else if (!hitten && DistanciaAJugador >= 1200.f){
			CuadradoPrincipal.move(cos(AnguloAJugador*M_PI/180) * speed, -sin(AnguloAJugador*M_PI/180)* speed); 
		}else if (hitten){
			if (runOnce == 0){
				
				
				switch (bulletHitten){
				case 0:
					jugador->VelocidadX() = cos(AnguloAJugador*M_PI/180) * 45;
					jugador->VelocidadY() = -sin(AnguloAJugador*M_PI/180) * 45;
					break;
				}
				runOnce++;
			}
			speedX *= 0.9;
			speedY *= 0.9;
			
			CuadradoPrincipal.move(-speedX, speedY);
		}
	} else{
		CuadradoPrincipal.setFillColor(Color(255, 255, 255, -255*c3.getElapsedTime().asSeconds()/0.5 + 255));
		CuadradoPrincipal.setOutlineColor(Color(255, 255, 255, -255*c3.getElapsedTime().asSeconds()/0.5 + 255));
		for (int i = 0; i<2; i++){
			CuadradosSecundarios[i].setFillColor(Color(255, 255, 255, -255*c3.getElapsedTime().asSeconds()/0.5 + 255));
			CuadradosSecundarios[i].setOutlineColor(Color(255, 255, 255, -255*c3.getElapsedTime().asSeconds()/0.5 + 255));
		}
	}
	
	
}
void LittleBoy::ActualizarEntidad(){
	Posicion() = CuadradoPrincipal.getPosition();
	
	
	if (this->life <= 0){
		if (runOnce3 == 0){
			dead = true;
			c3.restart();
			runOnce3++;
		}
		if (c3.getElapsedTime().asSeconds() > 0.48) deadDead = true;
	}
	
	if (!dead){
		/// Conseguir angulo al jugador
		if (!hitten)
			AnguloAJugador = Angulo(jugador->Posicion(), CuadradoPrincipal.getPosition()) + 180;
		/// Conseguir distancia al jugador
		float distanciaX = abs(jugador->Posicion().x - Posicion().x);
		float distanciaY = abs(jugador->Posicion().y - Posicion().y);
		DistanciaAJugador = sqrt((pow(distanciaX, 2) + pow(distanciaY, 2)));
		
		/// Rotacion del cuadrado principal
		CuadradoPrincipal.rotate(-sin((AnguloAJugador*M_PI)/180) * 25);
		CuadradoPrincipal.setFillColor(Color(255, abs(cos((AnguloAJugador*M_PI)/180)) * 100, 0));
		
		/// Rotacion de los cuadrados secundarios y seteo del color
		for (int i = 0; i<2; i++){
			CuadradosSecundarios[i].rotate(-cos((AnguloAJugador*M_PI)/180) * 25);
			CuadradosSecundarios[i].setFillColor(Color(255, abs(cos((AnguloAJugador*M_PI)/180)) * 200, 0));
		}
		if (c1.getElapsedTime().asSeconds() > 3.14*2) c1.restart();
		
		/// Chequeo del hit con el jugador
		if (DistanciaAJugador<radio * 1.5) {
			hitten = true;
			if (runOnce2 == 0 && !jugador->muerto){
				jugador->Vida() -= (abs(speedX) + abs(speedY) + rand()%5) * 1/8;
				(*soundsUsable)["hitten"]->play();
				c2.restart();
				runOnce2++;
			}
		}
		if (hitten && c2.getElapsedTime().asSeconds() > 1.5f){
			hitten = false;
			bulletHitten = false;
			runOnce2 = 0;
		}
		
		/// Posicionamiento de la barra de vida
		lifeShape.setPosition(Vector2f(Posicion().x, Posicion().y - 2*size));
		
		/// Giro al rededor del centro del cuadrado principal de los cuadrados secundarios
		CuadradosSecundarios[0].setPosition(Vector2f(CuadradoPrincipal.getPosition().x + cos(c1.getElapsedTime().asSeconds()) * radio, CuadradoPrincipal.getPosition().y - sin(c1.getElapsedTime().asSeconds()) * radio));
//		CuadradosSecundarios[1].setPosition(Vector2f(CuadradoPrincipal.getPosition().x + cos(c1.getElapsedTime().asSeconds()) * radio, CuadradoPrincipal.getPosition().y + sin(c1.getElapsedTime().asSeconds()) * radio));
//		CuadradosSecundarios[1].setPosition(Vector2f(CuadradoPrincipal.getPosition().x - cos(c1.getElapsedTime().asSeconds()) * radio, CuadradoPrincipal.getPosition().y - sin(c1.getElapsedTime().asSeconds()) * radio));
		CuadradosSecundarios[1].setPosition(Vector2f(CuadradoPrincipal.getPosition().x - cos(c1.getElapsedTime().asSeconds()) * radio, CuadradoPrincipal.getPosition().y + sin(c1.getElapsedTime().asSeconds()) * radio));
	}
	
}
void LittleBoy::DibujarEntidad(){
	Ventana()->draw(CuadradoPrincipal);
	if (!dead) Ventana()->draw(lifeShape);
	for (RectangleShape &x : CuadradosSecundarios){
		Ventana()->draw(x);
	}
}

void LittleBoy::FeedbackBala(Vector2f PosicionBala, float DanioBala){
	float AnguloABala = Angulo(PosicionBala, CuadradoPrincipal.getPosition()) + 180;
	speedX = -cos(AnguloABala*M_PI/180) * DanioBala*2;
	speedY = sin(AnguloABala*M_PI/180) * DanioBala*2;
	hitten = true;
	bulletHitten = true;
}

void LittleBoy::ActualizarBarraDeVida(){
	//	lifeShape.setSize(Vector2f(life, 50.f));
	lifeShape.setSize(Vector2f((life * size)*2/initLife, size * 1/4));
}

FloatRect LittleBoy::coordenadasGlobales(){
	CircleShape r;
	r.setRadius(radio);
	r.setPosition(Posicion());
	return r.getGlobalBounds();
}
