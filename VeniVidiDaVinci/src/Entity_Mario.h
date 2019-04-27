#pragma once
#include "Entity.h"

class Entity_Mario : public Entity
{
private:
	// Animation
	int _jumpFrame{ 0 };

	void RunningAnimation(float deltaTime);

public:
	Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_Mario();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
};

