#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed)
	: Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mCharacterSpeed = movementSpeed;
	mPosition = startPosition;

	mAlive = true;
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::Render()
{
	int left = 0;

	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { static_cast<int>(mPosition.x), static_cast<int>(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING::RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event event)
{
	Character::Update(deltaTime, event);
	CheckIfMapBoundryIsHit();

	if (!mInjured) {
		if (mFacingDirection == FACING::LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING::RIGHT) {
			mMovingLeft = false;
			mMovingRight = true;
		}
	}
	else {
		mMovingRight = false;
		mMovingLeft = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0f) {
			FlipRightwayUp();
		}
	}
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::SetAlive(bool state)
{
	mAlive = state;
}

void CharacterKoopa::CheckIfMapBoundryIsHit()
{
	if (mPosition.x < 0 || mPosition.x + mSingleSpriteWidth >= SCREEN_WIDTH) 
	{
		mFacingDirection = mFacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
		//std::cout << "HIT" << std::endl;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	mFacingDirection = mFacingDirection == FACING::LEFT ? FACING::RIGHT : FACING::LEFT;
	mInjured = false;
	Jump();
}