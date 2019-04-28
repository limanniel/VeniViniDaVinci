#pragma once
#include "Entity.h"

class Entity_Mario : public Entity
{
private:
	void RunningAnimation(float deltaTime);
	bool _TriggeredBlock{ false };

public:
	Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_Mario();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
	bool Collision(void* blockRef, TileTypes type) override;
};

