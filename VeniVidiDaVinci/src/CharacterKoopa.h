#pragma once
#include "Character.h"
class CharacterKoopa :
	public Character
{
private:
	int mSingleSpriteWidth;
	int mSingleSpriteHeight;

	bool mAlive;
	bool mInjured;
	float mInjuredTime;
	void CheckIfMapBoundryIsHit();

	void FlipRightwayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event event);

	void TakeDamage();
	void Jump();

	void SetAlive(bool state);
	bool GetAlive() const { return mAlive; };
	bool GetInjured() const { return mInjured; }
};
