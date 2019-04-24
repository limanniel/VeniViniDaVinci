#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
	: mRenderer(renderer), mLevelMap(map)
{
	std::string imagePath = "resources/Images/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str())) {
		std::cerr << "Failed to load texture: " << imagePath.c_str() << std::endl;
		return;
	}

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 sprites on this spritesheer in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();

	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260.0f);
}

PowBlock::~PowBlock()
{
	mRenderer = nullptr;
	delete mTexture;
	mLevelMap = nullptr;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft >= 0) {
		// Get the portion of the spritesheet you want to draw.
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//								 Xpos, YPos, WidthOfSingleSprite, HeightOfSingleSprite
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		// Determine where you want it drawn.
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		// Draw It
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;
	if (mNumberOfHitsLeft <= 0) {
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}