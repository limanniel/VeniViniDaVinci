#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, const char* imagePath, Vector2D startPosition, LevelMap* map)
	: Character(renderer, imagePath, startPosition, map)
{
}

CharacterMario::~CharacterMario()
{
}

void CharacterMario::Update(float deltaTime, SDL_Event event)
{
	Character::Update(deltaTime, event);

	switch (event.type) {
		// Key-Down
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			break;

		case SDLK_SPACE:
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
		case SDLK_LEFT:
			mMovingLeft = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			break;

		default:
			break;
		}
		break;
	}
}