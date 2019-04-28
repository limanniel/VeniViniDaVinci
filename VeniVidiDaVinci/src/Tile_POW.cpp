#include "Tile_POW.h"



Tile_POW::Tile_POW(SDL_Renderer* renderer, TileTypes type, Vector2D position)
	: Tile(renderer, type, position)
{
	_sourceRect->w = _texture->GetWidth() / 3;
}


Tile_POW::~Tile_POW()
{
}

void Tile_POW::Render(float xOffset, float yOffset)
{
	SDL_Rect partOfSpriteSheet{ _textureOffset * _sourceRect->w, 0, _sourceRect->w, _height };
	_texture->Render(partOfSpriteSheet, *_sourceRect, SDL_FLIP_NONE);
}

void Tile_POW::Update(float deltaTime)
{
}

void Tile_POW::TakeAHit()
{
	_NumberOfHitsLeft--;
	_textureOffset++;
}
