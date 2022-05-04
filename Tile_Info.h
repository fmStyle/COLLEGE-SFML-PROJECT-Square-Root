#ifndef TILEINFO_H
#define TILEINFO_H

#include "Jugador.h"

struct TileInfo {
	string textureName;
	int textureSize;
	int mode; // 0 : background, 1 : danger tile, 2 : deco tile
	TileInfo(string textureName, int mode, int textureSize);
};

#endif

