#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
{
	_Renderer = renderer;
	_Position = position;
	_Texture = new Texture2D(_Renderer);
	_Texture->LoadFromFile(texturePath);
}


Entity::~Entity()
{
	delete _Texture;
	_Texture = nullptr;
}

void Entity::Render()
{
	SDL_Rect portionOfSpriteSheet{ _xFrame, _yFrame, _singleSpriteWidth, _singleSpriteHeight };

	if (_FacingDirection == FACING::RIGHT)
	{
		_Texture->Render(portionOfSpriteSheet, *_SourceRect, SDL_FLIP_NONE);
	}
	else
	{
		_Texture->Render(portionOfSpriteSheet, *_SourceRect, SDL_FLIP_HORIZONTAL);
	}
}

void Entity::Update(float deltaTime, SDL_Event event)
{
	_SourceRect->x = (int)_Position.x;
	_SourceRect->y = (int)_Position.y;

	// Check if Entity is on the ground, if no then add Gravity to pull it down
	if (!_IsOnTheGround)
	{
		AddGravity(deltaTime);
	}

	else
	{
		_GravityForce = INITIAL_GRAVITY_FORCE;
	}
	
	if (_IsJumping)
	{
		_Position.y -= _JumpForce * deltaTime;
		_JumpForce -= (JUMP_FORCE_DECREMENT / 2)* deltaTime;
		if (_JumpForce <= 0.0f)
		{
			_IsJumping = false;
		}
	}

	if (_MovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (_MovingRight)
	{
		MoveRight(deltaTime);
	}
}

void Entity::MoveLeft(float deltaTime)
{
	_FacingDirection = FACING::LEFT;
	_Position.x -= _MovementSpeed * deltaTime;
}

void Entity::MoveRight(float deltaTime)
{
	std::cout << "x: " << _SourceRect->x << std::endl;
	_FacingDirection = FACING::RIGHT;
	_Position.x += _MovementSpeed * deltaTime;
}

void Entity::AddGravity(float deltaTime)
{
	if (_GravityForce < TERMINAL_GRAVITY_FORCE)
	{
		_GravityForce += GRAVITY_INCREMENT * deltaTime;
	}
	_Position.y += _GravityForce * deltaTime;
}

void Entity::Jump()
{
	if (!_IsJumping)
	{
		_JumpForce = INITIAL_JUMP_FORCE;
		_IsJumping = true;
		_CanJump = false;
	}
}

