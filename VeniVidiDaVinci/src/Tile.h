#pragma once
#include <SDL.h>
#include "Texture2D.h"
#include "Constants.h"

class Tile
{
protected:
	int _width, _height;
	Texture2D* _texture;
	int _xFrame{ 0 };
	SDL_Rect* _sourceRect{ nullptr };


public:
	Tile(Texture2D* texture, Vector2D position = {0,0});
	Tile(SDL_Renderer* renderer, TileTypes type, Vector2D position = { 0,0 });
	virtual ~Tile();

	virtual void Render(Vector2D position);
	virtual void Render(float xOffset = 0.0f, float yOffset = 0.0f);
	virtual void Update(float deltaTime);

	inline SDL_Rect* GetRect() const { return _sourceRect; }
};

