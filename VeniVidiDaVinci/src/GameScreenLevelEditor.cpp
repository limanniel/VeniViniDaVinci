#include "GameScreenLevelEditor.h"
#include <string>
#include <iostream>
#include <fstream>

GameScreenLevelEditor::GameScreenLevelEditor(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_bgTexture = new Texture2D(renderer);
	_bgTexture->LoadFromFile("resources/Images/Backgrounds/1.png");
	_HUD = new Texture2D(renderer);
	_HUD->LoadFromFile("resources/Images/LevelEditor/LevelEditorHUD.png");

	for (unsigned int i = 0; i < LE_AMOUNTOFTYPEBLOCKS - 1; i++)
	{
		_HUDBlockName[i] = new Text(renderer, MarioFont, new SDL_Rect{ 80, 465, 128, 18 });
	}
	_HUDBlockName[0]->CreateText("Platform Block");
	_HUDBlockName[1]->CreateText("Power Block");
	_HUDBlockName[2]->CreateText("Coin Pickup");
	_HUDBlockName[3]->CreateText("Right Pipe");
	_HUDBlockName[4]->CreateText("Left Pipe");
	_HUDBlockName[5]->CreateText("Mario Spawner");

	_levelMap = new LevelMap(map);

	for (unsigned int i = 0; i < LE_AMOUNTOFTYPEBLOCKS; i++)
	{
		std::string texturePath = "resources/Images/LevelEditor/.png";
		_tilesTextures[i] = new Texture2D(renderer);
		texturePath.insert(29, std::to_string(i));
		_tilesTextures[i]->LoadFromFile(texturePath.c_str());

		_tiles[i] = new Tile(_tilesTextures[i]);
	}

	_HUDSaveMap = new Text(renderer, MarioFont, new SDL_Rect{ 350, 465, 128, 18 });
	_HUDSaveMap->CreateText("Save Map");
	_HUDPlayLevel = new Text(renderer, MarioFont, new SDL_Rect{ 350, 435, 128, 18 });
	_HUDPlayLevel->CreateText("Play Level");
}


GameScreenLevelEditor::~GameScreenLevelEditor()
{
	for (unsigned int i = 0; i < LE_AMOUNTOFTYPEBLOCKS; i++)
	{
		delete _tilesTextures[i];
		delete _tiles[i];
		_tilesTextures[i] = nullptr;
		_tiles[i] = nullptr;
	}

	for (unsigned int i = 0; i < LE_AMOUNTOFTYPEBLOCKS - 1; i++) 
	{
		delete _HUDBlockName[i];
		_HUDBlockName[i] = nullptr;
	}
	delete _HUDSaveMap;
	_HUDSaveMap = nullptr;

	delete _HUDPlayLevel;
	_HUDPlayLevel = nullptr;

	delete _bgTexture;
	_bgTexture = nullptr;

	delete _levelMap;
	_levelMap = nullptr;
}

void GameScreenLevelEditor::Render()
{
	_bgTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE, 0.0f);

	float yPos = 0.0f;
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		float xPos = 0.0f;
		for (unsigned int j = 0; j < MAP_WIDTH; j++) {
			_tiles[_levelMap->GetTileAt(i, j)]->Render(Vector2D(xPos, yPos));
			xPos += TILE_WIDTH;
		}
		yPos += TILE_HEIGHT;
	}
	_HUD->Render(Vector2D(0.0f, 412.0f), SDL_FLIP_NONE, 0.0f);
	_HUDSaveMap->Render();
	_HUDPlayLevel->Render();
	_HUDBlockName[_ActiveBlock - 1]->Render();
	_tiles[_ActiveBlock]->Render(Vector2D(39.0f, 458.0f));
}

void GameScreenLevelEditor::Update(float deltaTime, SDL_Event event)
{
	int mousePosX{ 0 }, mousePosY{ 0 };
	SDL_GetMouseState(&mousePosX, &mousePosY);
	_ActiveBlock = BlockSelector(event);

	if (Collisions::Instance()->Box(*new SDL_Rect{ mousePosX, mousePosY, 16, 16 }, *_HUDSaveMap->GetPosition()))
	{
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				SaveMap();
			}
		}
	}
	if (Collisions::Instance()->Box(*new SDL_Rect{ mousePosX, mousePosY, 16, 16 }, *_HUDPlayLevel->GetPosition()))
	{
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				SCREEN = SCREEN_LEVEL2;
				SCREEN_CHANGE = true;
			}
		}
	}
		

	// Limit Window area for edition to Level Editor only + take offset for mouse
	if (mousePosX < SCREEN_WIDTH && mousePosY < SCREEN_HEIGHT - 100) {
		mousePosX -= 12;
		mousePosY -= 12;

		// Calculate Position of the block
		int centralXPosition = (int)(mousePosX + (TILE_WIDTH * 0.5f)) / TILE_WIDTH;
		int footposition = (int)(mousePosY + (TILE_HEIGHT * 0.5f)) / TILE_HEIGHT;

		// Change tile to selected block
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				_levelMap->ChangeTileAt(footposition, centralXPosition, _ActiveBlock);
			}
		}
		// Remove Tile
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				_levelMap->ChangeTileAt(footposition, centralXPosition, 0);
			}
		}
	}
}

int GameScreenLevelEditor::BlockSelector(SDL_Event event)
{
	int wheelY = 0;
	if (event.type == SDL_MOUSEWHEEL) {
		wheelY = event.wheel.y;
		if (wheelY > 0) {
			_ActiveBlock++;
			if (_ActiveBlock > LE_AMOUNTOFTYPEBLOCKS - 1) // Index starts at 0
				_ActiveBlock = 1;
		}
		else if (wheelY < 0) {
			_ActiveBlock--;
			if (_ActiveBlock < 1)
				_ActiveBlock = LE_AMOUNTOFTYPEBLOCKS - 1;
		}
	}
	return _ActiveBlock;
}

bool GameScreenLevelEditor::ValidateMap()
{
	return true;
}

void GameScreenLevelEditor::SaveMap()
{
	if (ValidateMap())
	{
		std::ofstream file;
		file.open("resources/LevelEditor_Maps/1.map", std::ios::out);

		for (unsigned int i = 0; i < MAP_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < MAP_WIDTH; j++) {
				file << _levelMap->GetTileAt(i, j);
			}
			file << "\n";
		}
		std::cout << "Map Saved!" << std::endl;
		file.close();
	}
}
