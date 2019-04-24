#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map)
	: Character(renderer, imagePath, startPosition, map)
{
}

CharacterLuigi::~CharacterLuigi()
{
}

void CharacterLuigi::Update(float deltaTime, SDL_Event event)
{
	Character::Update(deltaTime, event);

	switch (event.type) {
		// Key-Down
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;

		case SDLK_d:
			mMovingRight = true;
			mMovingLeft = false;
			break;

		case SDLK_w:
			if (mCanJump) {
				Jump();
			}
			break;

		default:
			break;
		}
		break;
		// Key-Up
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = false;
			break;

		case SDLK_d:
			mMovingRight = false;
			break;

		default:
			break;
		}
		break;
	}
}