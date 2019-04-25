#pragma once
#include <SDL.h>
#include "Texture2D.h"
#include "Constants.h"

class Tile
{
private:
	int _width, _height;
	Texture2D* _texture;
	SDL_Rect* _sourceRect;


public:
	Tile(Texture2D* texture);
	~Tile();

	void Render(Vector2D position);
};

