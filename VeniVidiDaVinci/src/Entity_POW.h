#pragma once
#include "Entity.h"
class Entity_POW : public Entity
{
private:
	int _NumberOfHitsLeft{ 3 };

public:
	Entity_POW(SDL_Renderer* renderer, const char* texturePath, Vector2D position);
	~Entity_POW();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;

	inline bool IsAvailable() const { return _NumberOfHitsLeft > 0; }
	void TakeAHit();
};

