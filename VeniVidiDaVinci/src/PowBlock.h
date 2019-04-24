#pragma once
#include "SDL.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Collisions.h"

class PowBlock
{
private:
	SDL_Renderer * mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	void TakeAHit();
	bool isAvailable() const { return mNumberOfHitsLeft > 0; };
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight); };
};
