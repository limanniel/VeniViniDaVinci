#pragma once
#include "Character.h"
class CharacterCoin : public Character
{
private:
	int mSingleSpriteWidth;
	int mSingleSpriteHeight;
	bool mCollected{ false };

	// Animation
	const float mAnimationDuration;
	float mFrameDelay;
	float mCurrentFrame;
	float mActiveFrame;

public:
	CharacterCoin(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterCoin();

	void Update(float deltaTime, SDL_Event event);
	void Render();

	void SetCollected(bool state) { mCollected = state; }
	bool IsCollected() const { return mCollected; }
};
