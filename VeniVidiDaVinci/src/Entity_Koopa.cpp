#include "Entity_Koopa.h"


Entity_Koopa::Entity_Koopa(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	: Entity(renderer, texturePath, position)
{
	_SourceRect = Rect2D(position.x, position.y, _singleSpriteWidth, _singleSpriteHeight);
}


Entity_Koopa::~Entity_Koopa()
{
}

void Entity_Koopa::Render()
{
	SDL_Rect portionOfSpriteSheet{ 0, 0, _singleSpriteWidth, _singleSpriteHeight };

	if (_FacingDirection == FACING::RIGHT)
	{
		_Texture->Render(portionOfSpriteSheet, (SDL_Rect)_SourceRect, SDL_FLIP_NONE);
	}
	else
	{
		_Texture->Render(portionOfSpriteSheet, (SDL_Rect)_SourceRect, SDL_FLIP_HORIZONTAL);
	}
}

void Entity_Koopa::Update(float deltaTime, SDL_Event event)
{
	Entity::Update(deltaTime, event);
	CheckIfMapBoundryIsHit();

	if (!_IsInjured)
	{
		if (_FacingDirection == FACING::LEFT)
		{
			_MovingLeft = true;
			_MovingRight = false;
		}
		else if (_FacingDirection == FACING::RIGHT)
		{
			_MovingRight = true;
			_MovingLeft = false;
		}
	}
	else
	{
		_MovingLeft = false;
		_MovingRight = false;

		_InjuredTime -= deltaTime;

		if (_InjuredTime <= 0.0f)
		{
			FlipRightwayUp();
		}
	}
}

void Entity_Koopa::FlipRightwayUp()
{
	_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	_IsInjured = false;
	Jump();
}

void Entity_Koopa::CheckIfMapBoundryIsHit()
{
	if (_SourceRect.x < 0 || _SourceRect.x + _singleSpriteWidth >= SCREEN_WIDTH)
	{
		_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	}
}

void Entity_Koopa::MovementAnimation(float deltaTime)
{
}
