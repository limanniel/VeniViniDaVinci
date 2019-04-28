#include "Entity_Mario.h"



Entity_Mario::Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	:Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 42;
	_MovementSpeed = 0.17f;
	_animationDuration = 1.5f;
	_SourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _singleSpriteWidth, _singleSpriteHeight };
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

void Entity_Mario::Collision(Tile& blockRef)
{
	SDL_Rect characterHeadRect{ (int)_Position.x, (int)_Position.y, _singleSpriteWidth, _singleSpriteHeight };
	SDL_Rect characterFeetRect{ (int)_Position.x + _singleSpriteWidth / 2, (int)_Position.y + _singleSpriteHeight, 1, 1 };
	SDL_Rect objectTopRect{ (int)blockRef.GetSourceRect()->x, (int)blockRef.GetSourceRect()->y, (int)blockRef.GetSourceRect()->w, 1 };

	// Check if on the top of the block
	if (Collisions::Instance()->Box(characterFeetRect, objectTopRect))
	{
		_CanJump = true;
		_IsOnTheGround = true;
	}

	// If you Jump collide with any block
	else if (Collisions::Instance()->Box(characterHeadRect, *blockRef.GetSourceRect()))
	{
		CancelJump();
		_IsOnTheGround = false;
	}

	// Character is airborne 
	else
	{
		_CanJump = false;
		_IsOnTheGround = false;
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