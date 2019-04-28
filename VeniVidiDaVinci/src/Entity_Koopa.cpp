#include "Entity_Koopa.h"


Entity_Koopa::Entity_Koopa(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	: Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 32;
	_MovementSpeed = 0.15f;
	_animationDuration = 150.0f;
	_SourceRect = new SDL_Rect{(int)position.x, (int)position.y, _singleSpriteWidth, _singleSpriteHeight};
}


Entity_Koopa::~Entity_Koopa()
{
}

void Entity_Koopa::Render()
{
	Entity::Render();
}

void Entity_Koopa::Update(float deltaTime, SDL_Event event)
{
	Entity::Update(deltaTime, event);
	CheckIfMapBoundryIsHit();

	if (!_IsInjured)
	{
		_yFrame = 0 * _singleSpriteHeight;
		
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
		MovementAnimation(deltaTime);
	}
	else
	{
		_yFrame = 1 * _singleSpriteHeight;
		_MovingLeft = false;
		_MovingRight = false;

		_InjuredTime -= deltaTime;

		if (_InjuredTime <= 0.0f)
		{
			_xFrame = 5 * _singleSpriteWidth;
			_InjuredTime = 5000.0f;
			FlipRightwayUp();
		}
		KnockedAnimation(deltaTime);
	}
}

bool Entity_Koopa::Collision(void* blockRef, TileTypes type)
{
	return false;
}

void Entity_Koopa::FlipRightwayUp()
{
	_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	_IsInjured = false;
	//Jump();
}

void Entity_Koopa::CheckIfMapBoundryIsHit()
{
	if (_Position.x <= 0 || _Position.x + _singleSpriteWidth >= SCREEN_WIDTH)
	{
		_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	}
}

void Entity_Koopa::MovementAnimation(float deltaTime)
{
	_animationDelay += deltaTime;
	if (_animationDelay >= _animationDuration)
	{
		_animationDelay = 0.0f;
		_currentFrame++;

		if (_currentFrame > 4)
		{
			_currentFrame = 0;
		}
		_xFrame = _currentFrame * _singleSpriteWidth;
	}
}

void Entity_Koopa::KnockedAnimation(float deltaTime)
{
	_animationDelay += deltaTime;
	if (_animationDelay >= _KnockedAnimationDuration)
	{
		_animationDelay = 0.0f;
		_currentFrame++;

		if (_currentFrame > 4)
		{
			_currentFrame = 3;
		}
		_xFrame = _currentFrame * _singleSpriteWidth;
	}
}
