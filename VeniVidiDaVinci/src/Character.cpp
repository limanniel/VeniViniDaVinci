#include "Character.h"

Character::Character(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map)
	:mRenderer(renderer), mFacingDirection(FACING_RIGHT), mMovingLeft(false), mMovingRight(false), mCharacterSpeed(100), mCollisionRadius(15.0f), mCurrentLevelMap(map)
{
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	SetPosition(startPosition); // Set character starting position
}

Character::Character(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition)
	:mRenderer(renderer), mFacingDirection(FACING_RIGHT), mMovingLeft(false), mMovingRight(false), mCharacterSpeed(100), mCollisionRadius(15.0f)
{
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	SetPosition(startPosition); 
}

Character::~Character()
{
	mRenderer = nullptr;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(mPosition, SDL_RendererFlip::SDL_FLIP_NONE, 0.0f);
	}
	else {
		mTexture->Render(mPosition, SDL_RendererFlip::SDL_FLIP_HORIZONTAL, 0.0f);
	}
}

void Character::Update(float deltaTime, SDL_Event event)
{
	if (mCurrentLevelMap != nullptr) {
		// Collsiion position variables
		int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
		int footPosition = (int)(mPosition.y + (mTexture->GetHeight())) / TILE_HEIGHT;

		// Deal with gravity
		if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
			AddGravity(deltaTime); // Add gravity to the character
		}
		else {
			//Collided with ground so we can jump again
			mCanJump = true;
		}
	}

	if (mJumping) {
		mPosition.y -= mJumpForce * deltaTime; // Adjust position
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime; // Reduce jump force;
		// Is jump force 0 or less?
		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	if (mMovingLeft) {
		MoveLeft(deltaTime);
	}
	else if (mMovingRight) {
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= deltaTime * mCharacterSpeed;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += deltaTime * mCharacterSpeed;
}

void Character::AddGravity(float deltaTime)
{
	if (mPosition.y + mTexture->GetHeight() <= SCREEN_HEIGHT) {
		mPosition.y += GRAVITY_FORCE * deltaTime;
		mCanJump = false;
	}
	else if (mPosition.y + mTexture->GetHeight() >= SCREEN_HEIGHT) {
		mCanJump = true;
	}
}

void Character::Jump()
{
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::CancelJump()
{
	mJumping = false;
}