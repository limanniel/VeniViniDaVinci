#pragma once
#include "GameScreen.h"
#include "LevelMap.h"
#include "Text.h"
#include "Tile.h"

class GameScreenLevelEditor : public GameScreen
{
private:
	Texture2D* _HUD;
	Text* _HUDBlockName[LE_AMOUNTOFTYPEBLOCKS - 1];
	Text* _HUDSaveMap;
	Text* _HUDPlayLevel;

	Texture2D* _tilesTextures[LE_AMOUNTOFTYPEBLOCKS];
	Tile* _tiles[LE_AMOUNTOFTYPEBLOCKS];


	int map[MAP_HEIGHT][MAP_WIDTH]{ 0 };
	LevelMap* _levelMap{ nullptr };

	int _ActiveBlock{ 1 };
	int BlockSelector(SDL_Event event);

	bool ValidateMap();
	void SaveMap();

public:
	GameScreenLevelEditor(SDL_Renderer* renderer);
	~GameScreenLevelEditor();

	void Render();
	void Update(float deltaTime, SDL_Event event);
};

