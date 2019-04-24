#pragma once
#include "Character.h"
class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event event);
};
