#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Tile.h"
#include "Collisions.h"

class Entity
{
protected:
	SDL_Renderer* _Renderer;
	Texture2D* _Texture;
	Rect2D _SourceRect;

	bool _IsOnTheGround{ true };

	// Movement
	const float _MovementSpeed{ 0.25f };
	FACING _FacingDirection{FACING::RIGHT};
	bool _MovingLeft{ false }, _MovingRight{ false };
	void MoveLeft(double deltaTime);
	void MoveRight(double deltaTime);

	void AddGravity(double deltaTime);

public:
	Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	virtual ~Entity();

	virtual void Render();
	virtual void Update(double deltaTime, SDL_Event event);

	inline Rect2D GetSDLRect() const { return _SourceRect; }
	inline void SetIsOnTheGround(bool state) { _IsOnTheGround = state; }

};

