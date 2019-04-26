#pragma once
#include <SDL.h>
#include "Texture2D.h"
#include "Constants.h"

class Tile
{
private:
	int _width, _height;
	Texture2D* _texture;
	SDL_Rect* _sourceRect{ nullptr };


public:
	Tile(Texture2D* texture, Vector2D position = {0,0});
	Tile(SDL_Renderer* renderer, TileTypes type, Vector2D position = { 0,0 });
	~Tile();

	void Render(Vector2D position);
	void Render();


};

