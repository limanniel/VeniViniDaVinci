#pragma once

struct Vector2D
{
	float x, y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x, y;
	int width, height;

	Rect2D(float X, float Y, int Width, int Height)
	{
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}
};

struct Circle2D
{
	Vector2D position;
	float radius;

	Circle2D(Vector2D Position, float Radius)
	{
		position = Position;
		radius = Radius;
	}
};

enum SCREENS
{
	SCREEN_LevelEditor = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};
