#pragma once
#include "Character.h"
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event event);
};
