#pragma once
#include "Entity.h"
class Entity_SideStepper : public Entity
{
private:
	bool _IsAlive{ true };
	bool _IsInjured{ false };

	void FlipRightwayUp();
	void CheckIfMapBoundryIsHit();
	void AnimateMovement(float deltaTime);

public:
	Entity_SideStepper(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_SideStepper();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
	bool Collision(void* blockRef, TileTypes type) override;
};

