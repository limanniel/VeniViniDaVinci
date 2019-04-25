#include "GameScreenLevelEditor.h"



GameScreenLevelEditor::GameScreenLevelEditor(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_levelMap = new LevelMap(map);

	_tileTexture = new Texture2D(renderer);
	if (!_tileTexture->LoadFromFile("resources/Images/LevelEditor/Tile.png"))
		std::cerr << "Failed to load tile texture!" << std::endl;
	_tile = new Tile(_tileTexture);

	_groundTileTexture = new Texture2D(renderer);
	if (!_groundTileTexture->LoadFromFile("resources/Images/LevelEditor/TestTile.png"))
		std::cerr << "Failed to load tile texture!" << std::endl;
	_groundTile = new Tile(_groundTileTexture);
	
}


GameScreenLevelEditor::~GameScreenLevelEditor()
{
}

void GameScreenLevelEditor::Render()
{
	int yPos = 0;

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		int xPos = 0;
		for (unsigned int j = 0; j < MAP_WIDTH; j++) {

			int tileType = _levelMap->GetTileAt(i, j);
			switch (tileType)
			{
			case 0:
				_tile->Render(Vector2D(xPos, yPos));
				break;
			case 1:
				_groundTile->Render(Vector2D(xPos, yPos));
				break;
			default:
				break;
			}

			xPos += 32;
		}
		yPos += 32;
	}
}

void GameScreenLevelEditor::Update(float deltaTime, SDL_Event event)
{
	int mousePosX{ 0 }, mousePosY{ 0 };
	SDL_GetMouseState(&mousePosX, &mousePosY);
	mousePosX -= 5;
	mousePosY -= 10;

	int centralXPosition = (int)(mousePosX + (_groundTileTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footposition = (int)(mousePosY + (_groundTileTexture->GetHeight() * 0.5f)) / TILE_HEIGHT;

	std::cout << "Tile: " << _levelMap->GetTileAt(footposition, centralXPosition) << std::endl;

	switch(event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		_levelMap->ChangeTileAt(footposition, centralXPosition, 1);
		break;

	default:
		break;
	}
}
