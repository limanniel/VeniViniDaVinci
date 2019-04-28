#include "Entity_POW.h"

Entity_POW::Entity_POW(SDL_Renderer* renderer, const char* texturePath, Vector2D position)
	: Entity(renderer, texturePath, position)
{
	_singleSpriteWidth = 32;
	_singleSpriteHeight = 32;
	_SourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _singleSpriteWidth, _singleSpriteHeight };
}


Entity_POW::~Entity_POW()
{
}

void Entity_POW::Render()
{
	Entity::Render();
}

void Entity_POW::Update(float deltaTime, SDL_Event event)
{

}

void Entity_POW::Collision(Tile& blockRef)
{
}

void Entity_POW::TakeAHit()
{
	_NumberOfHitsLeft--;
	_xFrame += _singleSpriteWidth;
}
