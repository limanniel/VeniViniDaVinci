#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
{
	_Renderer = renderer;
	_Texture = new Texture2D(_Renderer);
	_Texture->LoadFromFile(texturePath);
	_SourceRect = Rect2D(position.x, position.y, 32, 42);
}


Entity::~Entity()
{
	delete _Texture;
	_Texture = nullptr;
}

void Entity::Render()
{
	if (_FacingDirection == FACING::RIGHT)
		_Texture->Render(_SourceRect, SDL_FLIP_NONE, 0.0f);
	else
		_Texture->Render(_SourceRect, SDL_FLIP_HORIZONTAL, 0.0f);
}

void Entity::Update(double deltaTime, SDL_Event event)
{
	if (!_IsOnTheGround)
	{
		AddGravity(deltaTime);
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

void Entity::MoveLeft(double deltaTime)
{
	_FacingDirection = FACING::LEFT;
	_SourceRect.x -= _MovementSpeed * deltaTime;
}

void Entity::MoveRight(double deltaTime)
{
	_FacingDirection = FACING::RIGHT;
	_SourceRect.x += _MovementSpeed * deltaTime;
}

void Entity::AddGravity(double deltaTime)
{
	_SourceRect.y += GRAVITY_FORCE * deltaTime;
}
