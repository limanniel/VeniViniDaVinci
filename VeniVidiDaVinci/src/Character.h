#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mCurrentLevelMap{ nullptr };

	// Movement
	FACING mFacingDirection;
	bool mMovingLeft, mMovingRight;
	int mCharacterSpeed;

	// Jumping
	bool mCanJump;
	bool mJumping;
	float mJumpForce;
	void Jump();

	//Gravity
	void AddGravity(float deltaTime);
	float mCollisionRadius;

public:
	Character(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map);
	Character(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition);
	virtual ~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event event);

	// Movement
	void SetPosition(Vector2D newPosition);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float delatTime);

	// Jumping
	bool isJumping() const { return mJumping; }
	void CancelJump();

	// Collision
	float getCollisionRadius() const { return mCollisionRadius; }
	Circle2D getCollisionCircle() const { return Circle2D(mPosition, mCollisionRadius); }
	Rect2D getCollisionBox() const { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }
	Vector2D GetPosition() const { return mPosition; }
};
