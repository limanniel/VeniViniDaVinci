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
	int _MovementSpeed{ 150 };
	FACING _FacingDirection{FACING::RIGHT};
	bool _MovingLeft{ false }, _MovingRight{ false };
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

public:
	Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	virtual ~Entity();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event event);
};

