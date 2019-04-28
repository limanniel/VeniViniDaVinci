#pragma once
#include "Tile.h"

class Tile_POW : public Tile
{
private:
	int _textureOffset{ 0 };
	int _NumberOfHitsLeft{ 3 };

public:
	Tile_POW(SDL_Renderer* renderer, TileTypes type, Vector2D position);
	~Tile_POW();

	void Render();
	void TakeAHit();
	inline bool IsAvailable() const { return _NumberOfHitsLeft > 0; }
};

