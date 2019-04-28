#include "Tile_Coin.h"



Tile_Coin::Tile_Coin(SDL_Renderer* renderer, TileTypes type, Vector2D position)
	: Tile(renderer, type, position)
{
	// Overwritte default values grabbed from texture source
	_sourceRect->w = 32;
	_sourceRect->h = 32;
}


Tile_Coin::~Tile_Coin()
{
}

void Tile_Coin::Render(float xOffset, float yOffset)
{
	SDL_Rect partOfSpriteSheet{ _xFrame, 0, _sourceRect->w, _sourceRect->h };
	_texture->Render(partOfSpriteSheet, *_sourceRect, SDL_FLIP_NONE);
}

void Tile_Coin::Update(float deltaTime)
{
	_animationDelay += deltaTime;
	if (_animationDelay >= _animationDuration)
	{
		_animationDelay = 0.0f;
		_currentFrame++;

		if (_currentFrame > 2)
		{
			_currentFrame = 0;
		}
		_xFrame = _currentFrame * _sourceRect->w;
	}
}
