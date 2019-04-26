#include "GameScreenLevelEditor.h"
#include <string>


GameScreenLevelEditor::GameScreenLevelEditor(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_HUD = new Texture2D(renderer);
	_HUD->LoadFromFile("resources/Images/LevelEditor/LevelEditorHUD.png");

	for (unsigned int i = 0; i < 3; i++)
	{
		_HUDBlockName[i] = new Text(renderer, MarioFont, new SDL_Rect{ 80, 465, 128, 18 });
	}
	_HUDBlockName[0]->CreateText("Platform Block");
	_HUDBlockName[1]->CreateText("Luigi Spawner");
	_HUDBlockName[2]->CreateText("Mario Spawner");

	_levelMap = new LevelMap(map);

	for (unsigned int i = 0; i < LE_AMOUNTOFTYPEBLOCKS; i++)
	{
		std::string texturePath = "resources/Images/LevelEditor/.png";
		_tilesTextures[i] = new Texture2D(renderer);
		texturePath.insert(29, std::to_string(i));
		_tilesTextures[i]->LoadFromFile(texturePath.c_str());

		_tiles[i] = new Tile(_tilesTextures[i]);
	}
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
	delete _levelMap;
	_levelMap = nullptr;
}

void GameScreenLevelEditor::Render()
{
	int yPos = 0;

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		int xPos = 0;
		for (unsigned int j = 0; j < MAP_WIDTH; j++) {
			_tiles[_levelMap->GetTileAt(i, j)]->Render(Vector2D(xPos, yPos));
			xPos += TILE_WIDTH;
		}
		yPos += TILE_HEIGHT;
	}
	_HUD->Render(Vector2D(0.0f, 412.0f), SDL_FLIP_NONE, 0.0f);
	_HUDBlockName[_ActiveBlock - 1]->Render();
	_tiles[_ActiveBlock]->Render(Vector2D(38.0f, 457.0f));
}

void GameScreenLevelEditor::Update(float deltaTime, SDL_Event event)
{
	int mousePosX{ 0 }, mousePosY{ 0 };
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mousePosX -= 12;
	mousePosY -= 12;

	_ActiveBlock = BlockSelector(event);

	int centralXPosition = (int)(mousePosX + (TILE_WIDTH * 0.5f)) / TILE_WIDTH;
	int footposition = (int)(mousePosY + (TILE_HEIGHT * 0.5f)) / TILE_HEIGHT;

	if (event.button.button == SDL_BUTTON_LEFT) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			_levelMap->ChangeTileAt(footposition, centralXPosition, _ActiveBlock);
		}
	}
	else if (event.button.button == SDL_BUTTON_RIGHT) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			_levelMap->ChangeTileAt(footposition, centralXPosition, 0);
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
