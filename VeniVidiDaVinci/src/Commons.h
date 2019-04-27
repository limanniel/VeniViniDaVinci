#pragma once

//struct Vector2D
//{
//	float x, y;
//
//	Vector2D()
//	{
//		x = 0.0f;
//		y = 0.0f;
//	}
//
//	Vector2D(float initialX, float initialY)
//	{
//		x = initialX;
//		y = initialY;
//	}
//};

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
	int w, h;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		w = 0;
		h = 0;
	}
	Rect2D(float X, float Y, int Width, int Height)
	{
		x = X;
		y = Y;
		w = Width;
		h = Height;
	}

	// Make Rect2D castable onto SDL_Rect
	explicit operator SDL_Rect() { return SDL_Rect{ (int)x, (int)y, w, h }; }
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

enum class FACING
{
	LEFT = 0,
	RIGHT
};

enum class TileTypes : char
{
	NONE = '0',
	PLATFORM = '1',
	POW = '2',
	COIN = '3',
	RIGHT_PIPE = '4',
	LEFT_PIPE = '5',
	MARIO_SPAWN = '6'
};
