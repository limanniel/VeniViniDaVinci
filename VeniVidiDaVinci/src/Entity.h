#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "Collisions.h"

class Entity
{
protected:
	SDL_Renderer* _Renderer;
	Texture2D* _Texture;
	Vector2D _Position;

	// Movement
	float _MovementSpeed{ 0.20f };
	FACING _FacingDirection{FACING::RIGHT};
	bool _MovingLeft{ false }, _MovingRight{ false };
	void MoveLeft(double deltaTime);
	void MoveRight(double deltaTime);

public:
	Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	virtual ~Entity();

	virtual void Render();
	virtual void Update(double deltaTime, SDL_Event event);
};

