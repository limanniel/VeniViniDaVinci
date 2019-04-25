#pragma once
#include "GameScreen.h"
#include "LevelMap.h"
#include "Tile.h"

class GameScreenLevelEditor : public GameScreen
{
private:
	Texture2D* _tileTexture;
	Tile* _tile;
	Tile* _groundTile;
	Texture2D* _groundTileTexture;

	int map[MAP_HEIGHT][MAP_WIDTH]{ 0 };
	LevelMap* _levelMap{ nullptr };

public:
	GameScreenLevelEditor(SDL_Renderer* renderer);
	~GameScreenLevelEditor();

	void Render();
	void Update(float deltaTime, SDL_Event event);
};

