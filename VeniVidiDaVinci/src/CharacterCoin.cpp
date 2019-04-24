#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map)
	: Character(renderer, imagePath, startPosition, map), mAnimationDuration(0.20f)
{
	mPosition = startPosition;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();

	mFrameDelay = 0.0f;
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Update(float deltaTime, SDL_Event event)
{
	mFrameDelay += deltaTime;
	if (mFrameDelay >= mAnimationDuration) {
		mFrameDelay = 0.0f;
		mCurrentFrame++;

		if (mCurrentFrame > 2) {
			mCurrentFrame = 0;
		}
	}
	mActiveFrame = mCurrentFrame * mSingleSpriteWidth;
}

void CharacterCoin::Render()
{
	SDL_Rect portionOfSpritesheet{ mActiveFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect{ static_cast<int>(mPosition.x), static_cast<int>(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}