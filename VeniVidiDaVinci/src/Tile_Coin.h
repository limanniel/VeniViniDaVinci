#pragma once
#include "Tile.h"

class Tile_Coin : public Tile
{
private:
	float _animationDuration{ 150.0f };
	float _animationDelay{ 0.0f };
	int _currentFrame{ 0 };

public:
	Tile_Coin(SDL_Renderer* renderer, TileTypes type, Vector2D position);
	~Tile_Coin();

	void Render(float xOffset = 0.0f, float yOffset = 0.0f) override;
	void Update(float deltaTime) override;
};

