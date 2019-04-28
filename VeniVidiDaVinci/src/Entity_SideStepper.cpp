#include "Entity_SideStepper.h"



Entity_SideStepper::Entity_SideStepper(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	: Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 32;
	_MovementSpeed = 0.12f;
	_animationDuration = 150.0f;
	_SourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _singleSpriteWidth, _singleSpriteHeight };
	_yFrame = 0;
}


Entity_SideStepper::~Entity_SideStepper()
{
}

void Entity_SideStepper::Render()
{
	Entity::Render();
}

void Entity_SideStepper::Update(float deltaTime, SDL_Event event)
{
	Entity::Update(deltaTime, event);
	CheckIfMapBoundryIsHit();

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

	AnimateMovement(deltaTime);
}

bool Entity_SideStepper::Collision(void* blockRef, TileTypes type)
{
	if (type == TileTypes::PLATFORM)
	{
		auto BlockTile = static_cast<Tile*>(blockRef);

		SDL_Rect characterHeadRect{ (int)_Position.x, (int)_Position.y, _singleSpriteWidth, _singleSpriteHeight };
		SDL_Rect characterFeetRect{ (int)_Position.x + _singleSpriteWidth / 2, (int)_Position.y + _singleSpriteHeight, 1, 1 };
		SDL_Rect objectTopRect{ (int)BlockTile->GetRect()->x, (int)BlockTile->GetRect()->y, (int)BlockTile->GetRect()->w, 1 };

		// Check if on the top of the block
		if (Collisions::Instance()->Box(characterFeetRect, objectTopRect))
		{
			_IsOnTheGround = true;
			return true;
		}

		// Character is airborne 
		else
		{
			_IsOnTheGround = false;
			FlipRightwayUp();
			return false;
		}
	}

	else if (type == TileTypes::COIN)
	{
		auto BlockTile = static_cast<Tile_Coin*>(blockRef);

		// Check if collided with coin
		if (Collisions::Instance()->Box(*_SourceRect, *BlockTile->GetRect()))
		{
			return false;
		}
		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}

void Entity_SideStepper::FlipRightwayUp()
{
	_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
}

void Entity_SideStepper::CheckIfMapBoundryIsHit()
{
	if (_Position.x <= 0 || _Position.x + _singleSpriteWidth >= SCREEN_WIDTH)
	{
		_FacingDirection = _FacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	}
}

void Entity_SideStepper::AnimateMovement(float deltaTime)
{
	_animationDelay += deltaTime;
	if (_animationDelay >= _animationDuration)
	{
		_animationDelay = 0.0f;
		_currentFrame++;

		if (_currentFrame > 1)
		{
			_currentFrame = 0;
		}
		_xFrame = _currentFrame * _singleSpriteWidth;
	}
}
