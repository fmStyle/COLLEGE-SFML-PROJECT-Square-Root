#ifndef TILEENGINE_H
#define TILEENGINE_H

#include "Tile_Info.h"

class TileEngine {
	
	
	int playableArea;
	
	/// De momento rectangleShape, luego tendrían que ser tiles
	map<string, shared_ptr<Texture>> *textures;
	vector<vector<Sprite>>matrizDeTiles;
	vector<FloatRect>areaDangerTiles;
	
public:
	float tileSize;
	Vector2f topCoordinate;
	Vector2f downCoordinate;
	TileEngine(float tileSize, int playableArea, map<string, shared_ptr<Texture>> *textures);
	void CreateTiles(int dangerTileProbability, int decoTileProbability, const vector<TileInfo>&possibleTiles, float tileScale);
	bool UpdateTilesAndPlayer(shared_ptr<Jugador> &jugador);
	void DrawTiles(shared_ptr<RenderWindow>&ventana);
};

#endif

