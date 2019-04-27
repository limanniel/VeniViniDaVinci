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
	Rect2D _SourceRect{ 0, 0, 0, 0 };
	bool _IsOnTheGround{ true };

	// Movement
	const float _MovementSpeed{ 0.25f };
	FACING _FacingDirection{FACING::RIGHT};
	bool _MovingLeft{ false }, _MovingRight{ false };
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	// Jump related 
	bool _CanJump{ false };
	bool _IsJumping{ false };
	float _JumpForce{ INITIAL_JUMP_FORCE };
	void Jump();

	// Gravity related
	float _GravityForce{ INITIAL_GRAVITY_FORCE };
	void AddGravity(float deltaTime);
	
	// Animation
	int _singleSpriteWidth{ 32 }, _singleSpriteHeight{ 32 };
	float _animationDuration{ 0.0f };
	float _animationDelay{ 0.0f };
	int _currentFame{ 1 }, _activeFrame{ 0 };


public:
	Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	virtual ~Entity();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event event);

	inline Rect2D GetSDLRect() const { return _SourceRect; }
	inline void SetIsOnTheGround(bool state) { _IsOnTheGround = state; }
	inline void SetIfCanJump(bool state) { _CanJump = state; }

};

