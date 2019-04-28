#include "Collisions.h"

Collisions* Collisions::mInstance = nullptr;

Collisions::Collisions()
{
	boxResult = { 0, 0, 0, 0 };
}

Collisions::~Collisions()
{
	mInstance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!mInstance) {
		mInstance = new Collisions;
	}

	return mInstance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.w / 2) > rect2.x
		&& rect1.x + (rect1.w / 2) < rect2.x + rect2.w
		&& rect1.y + rect1.h > rect2.y
		&& rect1.y + rect1.h < rect2.y + rect2.h) {
		return true;
	}
	return false;
}

bool Collisions::Box(SDL_Rect& rect1, SDL_Rect& rect2)
{
	if (SDL_HasIntersection(&rect1, &rect2)) {
		return true;
	}
	return false;
}

//bool Collisions::Circle(Entity* character1, Entity* character2)
//{
//	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x), (character1->GetPosition().y - character2->GetPosition().y));
//	double distance = sqrt((vec.x*vec.x) + (vec.y*vec.y));
//	double combinedDistance = (character1->getCollisionRadius() + character2->getCollisionRadius());
//
//	return distance < combinedDistance;
//}

bool Collisions::Circle(Circle2D circle1, Circle2D circle2)
{
	Vector2D vec = Vector2D((circle1.position.x - circle2.position.x), (circle1.position.y - circle2.position.y));
	double distance = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	double combinedDistance = (circle1.radius + circle2.radius);

	return distance < combinedDistance;
}