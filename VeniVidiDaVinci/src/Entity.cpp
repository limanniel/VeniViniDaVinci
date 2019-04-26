#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
{
	_Renderer = renderer;
	_Texture = new Texture2D(_Renderer);
	_Texture->LoadFromFile(texturePath);
	_Position = position;
}


Entity::~Entity()
{
	delete _Texture;
	_Texture = nullptr;

}

void Entity::Render()
{
	if (_FacingDirection == FACING::RIGHT)
		_Texture->Render(_Position, SDL_FLIP_NONE, 0.0f);
	else
		_Texture->Render(_Position, SDL_FLIP_HORIZONTAL, 0.0f);
}

void Entity::Update(float deltaTime, SDL_Event event)
{
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
	_FacingDirection = FACING::RIGHT;
	_Position.x += _MovementSpeed * deltaTime;
}
