#pragma once
#include <SDL.h>
#include "Commons.h"

class Character;

class Collisions
{
private:
	Collisions();
	static Collisions* mInstance;
	SDL_Rect boxResult;

public:
	~Collisions();
	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Circle(Circle2D circle1, Circle2D circle2);
	bool Box(Rect2D rect1, Rect2D rect2);
	bool Box(SDL_Rect& rect1, SDL_Rect& rect2);
};
