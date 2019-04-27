#include "Entity_Mario.h"



Entity_Mario::Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	:Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 42;
	_MovementSpeed = 0.18f;
	_animationDuration = 1.5f;
	_SourceRect = Rect2D(position.x, position.y, _singleSpriteWidth, _singleSpriteHeight);
}


Entity_Mario::~Entity_Mario()
{
}

void Entity_Mario::Render()
{
	Entity::Render();
}

void Entity_Mario::Update(float deltaTime, SDL_Event event)
{
	Entity::Update(deltaTime, event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			_MovingLeft = true;
			_MovingRight = false;
			RunningAnimation(deltaTime);
			break;
		case SDLK_RIGHT:
			_MovingLeft = false;
			_MovingRight = true;
			RunningAnimation(deltaTime);
			break;
		case SDLK_SPACE:
			if (_CanJump){
				Jump();
				_xFrame = 0;
				_yFrame = _singleSpriteHeight;
				break;
			}
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			_MovingLeft = false;
			_xFrame = 0;
			break;
		case SDLK_RIGHT:
			_MovingRight = false;
			_xFrame = 0;
		case SDLK_SPACE:
			_yFrame = 0;
			break;
		}
		break;

	default:
		break;
	}


}

void Entity_Mario::RunningAnimation(float deltaTime)
{
	if (_yFrame == 0)
	{
		_animationDelay += deltaTime;
		if (_animationDelay >= _animationDuration)
		{
			_animationDelay = 0.0f;
			_currentFrame++;

			if (_currentFrame > 3)
			{
				_currentFrame = 0;
			}
		}
		_xFrame = _currentFrame * _singleSpriteWidth;
	}
}