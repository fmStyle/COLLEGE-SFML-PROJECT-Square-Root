#include "TileEngine.h"
#include "FuncionesAnguloDistancia.h"

TileEngine::TileEngine(float tileSize, int playableArea, map<string, shared_ptr<Texture>> *textures) {
	this->textures = textures;
	this->tileSize = tileSize;
	this->playableArea = playableArea;

}



void TileEngine::DrawTiles(shared_ptr<RenderWindow>&ventana){
	for (int i = 0; i<matrizDeTiles.size(); ++i){
		for (int j = 0; j<matrizDeTiles[i].size(); ++j){
			ventana->draw(matrizDeTiles[i][j]);
		}
	}
}

bool TileEngine::UpdateTilesAndPlayer(shared_ptr<Jugador> &jugador){
	bool golpeo = false;
	for (FloatRect &x : areaDangerTiles){
		if (x.intersects(jugador->RectanguloJugador().getGlobalBounds())){
			float xPosition = x.left + 64;
			float yPosition = x.top + 64;
			float AnguloAJugador = Angulo(jugador->Posicion(), Vector2f(xPosition, yPosition))*M_PI/180;
			jugador->VelocidadX() = -cos(AnguloAJugador) * 27;
			jugador->VelocidadY() = sin(AnguloAJugador) * 27;
			jugador->Vida() -= 10 + rand()%20;
			jugador->AnimacionGolpeado();
			cout<<AnguloAJugador<<endl;
			golpeo = true;
		}
	}
	return golpeo;
}

void TileEngine::CreateTiles(int dangerTileProbability, int decoTileProbability, const vector<TileInfo>&possibleTiles, float tileScale){
	
	for (int i = 0; i<playableArea; i++){
		vector<Sprite> aux;
		matrizDeTiles.push_back(aux);
		for (int j = 0; j<playableArea; j++){
			Sprite auxBackground;
			vector<string> backgroundTextureNames;
			vector<string>dangerTextureNames;
			vector<string>decoTextureNames;
			
			for (int i = 0; i<possibleTiles.size(); ++i){
				switch(possibleTiles[i].mode){
				case 0:
					backgroundTextureNames.push_back(possibleTiles[i].textureName);
					break;
				case 1:
					dangerTextureNames.push_back(possibleTiles[i].textureName);
					break;
				case 2:
					decoTextureNames.push_back(possibleTiles[i].textureName);
					break;
				}
			}
			
			tileSize = tileScale * (*textures)[backgroundTextureNames[0]]->getSize().x;
			
			if (backgroundTextureNames.size() > 1){
				int randChoice = rand()%(backgroundTextureNames.size());
				
				auxBackground.setTexture(*(*textures)[backgroundTextureNames[randChoice]]);
				auxBackground.setScale(Vector2f(tileScale, tileScale));
				
				auxBackground.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
				if (i==0 && j==0){
					topCoordinate.x = auxBackground.getPosition().x;
					topCoordinate.y = auxBackground.getPosition().y;
				}
				if (i + 1 == playableArea && j + 1 == playableArea){
					downCoordinate.x = auxBackground.getPosition().x + tileSize;
					downCoordinate.y = auxBackground.getPosition().y + tileSize;
				}
				matrizDeTiles[i].push_back(auxBackground);
			} else{
				auxBackground.setTexture(*(*textures)[backgroundTextureNames[0]]);
				auxBackground.setScale(Vector2f(tileScale, tileScale));
				auxBackground.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
				
				
				matrizDeTiles[i].push_back(auxBackground);
			}
			
			int tileTopChoice = rand()%3;
			switch (tileTopChoice){
			case 0:
				
				break;
			case 1:
				{
					if (dangerTextureNames.empty()) break;
					if (dangerTextureNames.size() > 1){
						int dangerTileChoice = rand()%(dangerTileProbability);
						switch (dangerTileChoice){
						case 0:
							Sprite auxSprite;
//							int randChoice1 = rand()%2;
//							if (randChoice1 == 1){
								int randChoice = rand()%(dangerTextureNames.size());
								auxSprite.setTexture(*(*textures)[dangerTextureNames[randChoice]]);
								auxSprite.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
								auxSprite.setScale(Vector2f(tileScale, tileScale));
								matrizDeTiles[i].push_back(auxSprite);
								areaDangerTiles.push_back(matrizDeTiles[i][matrizDeTiles[i].size()-1].getGlobalBounds());
//							}
							break;
						}
					} else{
						int randChoice1 = rand()%(dangerTileProbability);
						if (randChoice1 == 0){
							Sprite auxSprite;
							auxSprite.setTexture(*(*textures)[dangerTextureNames[0]]);
							auxSprite.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
							auxSprite.setScale(Vector2f(tileScale, tileScale));
							matrizDeTiles[i].push_back(auxSprite);
//							areaDangerTiles.push_back(matrizDeTiles[i][areaDangerTiles.size()-1].getGlobalBounds());
						}
					}
				}
				break;
			case 2:
			{
				if (decoTextureNames.empty()) break;
				if (decoTextureNames.size() > 1){
					int decoTileChoice = rand()%(decoTileProbability+1);
					switch (decoTileChoice){
					case 0:
						Sprite auxSprite;
						int randChoice = rand()%(decoTextureNames.size());
						auxSprite.setTexture(*(*textures)[decoTextureNames[randChoice]]);
						auxSprite.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
						auxSprite.setScale(Vector2f(tileScale, tileScale));
//						auxSprite.setScale(Vector2f(rand()%int(tileScale), rand()%int(tileScale)));
//						auxSprite.setRotation(rand()%360);
						matrizDeTiles[i].push_back(auxSprite);
						
						break;
					}
				} else{
					int randChoice1 = rand()%(decoTileProbability);
					if (randChoice1 == 0){
						Sprite auxSprite;
						auxSprite.setTexture(*(*textures)[decoTextureNames[0]]);
						auxSprite.setPosition(Vector2f(j*tileSize - 640, i*tileSize - 360));
						auxSprite.setScale(Vector2f((tileScale), (tileScale)));
//						auxSprite.setRotation(rand()%360);
						matrizDeTiles[i].push_back(auxSprite);
					}
				}

			}
			break;
			}
//			auxRec.setSize(Vector2f(tileSize - 640, tileSize - 360));
			
//			auxRec.setFillColor(Color::Blue);
			
			
			
		}
	}
}

