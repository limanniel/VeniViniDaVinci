#pragma once
#include "Entity.h"

class Entity_Mario : public Entity
{
private:
	// Animation
	const float _animationDuration;
	float _animationDelay{ 0.0f };
	int _currentFame{ 1 }, _activeFrame{ 0 }, _jumpFrame{ 0 };

	void RunningAnimation(double deltaTime);

public:
	Entity_Mario(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_Mario();

	void Render() override;
	void Update(double deltaTime, SDL_Event event) override;
};

