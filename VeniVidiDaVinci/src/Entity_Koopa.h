#pragma once
#include "Entity.h"
class Entity_Koopa : public Entity
{
private:
	bool _IsAlive{ true };
	bool _IsInjured{ false };
	float _InjuredTime{ 0.0f };

	void FlipRightwayUp();
	void CheckIfMapBoundryIsHit();

	void MovementAnimation(float deltaTime);

public:
	Entity_Koopa(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_Koopa();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
};

