#include "Entity_Mario.h"



Entity_Mario::Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	:Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 42;
	_animationDuration = 1.5f;
	_SourceRect = Rect2D(position.x, position.y, _singleSpriteWidth, _singleSpriteHeight);
}


Entity_Mario::~Entity_Mario()
{
}

void Entity_Mario::Render()
{
	SDL_Rect portionOfSpriteSheet{ _activeFrame, _jumpFrame, _singleSpriteWidth, _singleSpriteHeight };

	if (_FacingDirection == FACING::RIGHT)
	{
		_Texture->Render(portionOfSpriteSheet, (SDL_Rect)_SourceRect, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		_Texture->Render(portionOfSpriteSheet, (SDL_Rect)_SourceRect, SDL_FLIP_NONE);
	}
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
				_activeFrame = 0;
				_jumpFrame = _singleSpriteHeight;
				break;
			}
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			_MovingLeft = false;
			_activeFrame = 0;
			break;
		case SDLK_RIGHT:
			_MovingRight = false;
			_activeFrame = 0;
		case SDLK_SPACE:
			_jumpFrame = 0;
			break;
		}
		break;

	default:
		break;
	}


}

void Entity_Mario::RunningAnimation(float deltaTime)
{
	if (_jumpFrame == 0)
	{
		_animationDelay += deltaTime;
		if (_animationDelay >= _animationDuration)
		{
			_animationDelay = 0.0f;
			_currentFame++;

			if (_currentFame > 3)
			{
				_currentFame = 0;
			}
		}
		_activeFrame = _currentFame * _singleSpriteWidth;
	}
}