#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	LoadLevel();
}


GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		_tiles[i]->Render();
	}
	for (unsigned int i = 0; i < _powBlocks.size(); i++)
	{
		_powBlocks[i]->Render();
	}
		_mario->Render();
		_koopa->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event event)
{
	// Check Whether Mario is on the ground
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		_mario->Collision(*_tiles[i]);
		if (_mario->IsOnTheGround())
		{
			break;
		}
	}

	for (unsigned int i = 0; i < _powBlocks.size(); i++)
	{
		if (Collisions::Instance()->Box(*_mario->GetRect(), *_powBlocks[i]->GetRect()))
		{
			_powBlocks[i]->TakeAHit();
			_mario->CancelJump();
			break;
		}
	}
	_mario->Update(deltaTime, event);
	_koopa->Update(deltaTime, event);
}

void GameScreenLevel2::LoadLevel()
{
	std::ifstream file;
	file.open("resources/LevelEditor_Maps/1.map", std::ios::in);
	if (!file.is_open()) {
		std::cerr << "File Map not found!" << std::endl;
	}

	char TileType{ ' ' };
	
	file.seekg(std::ios::beg);

	float xPos = 0.0f;
	float yPos = 0.0f;
	while (file >> std::noskipws >> TileType) 
	{
		if (TileType == '\n') {
			yPos += TILE_WIDTH;
			xPos = 0.0f;
		}

		else {
			switch (TileType)
			{
			case static_cast<char>(TileTypes::NONE) :
				//_tiles.push_back(new Tile(mRenderer, TileTypes::NONE, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::PLATFORM) :
				_tiles.push_back(new Tile(mRenderer, TileTypes::PLATFORM, Vector2D(xPos, yPos)));
				break;
				case static_cast<char>(TileTypes::POW) :
					_powBlocks.push_back(new Entity_POW(mRenderer, "resources/Images/PowBlock.png", Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::COIN) :
				_tiles.push_back(new Tile(mRenderer, TileTypes::COIN, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::RIGHT_PIPE) :
				_tiles.push_back(new Tile(mRenderer, TileTypes::RIGHT_PIPE, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::LEFT_PIPE) :
				_tiles.push_back(new Tile(mRenderer, TileTypes::LEFT_PIPE, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::MARIO_SPAWN) :
				_mario = new Entity_Mario(mRenderer, "resources/Images/Mario.png", Vector2D(xPos, yPos - 50));
				break;
			case static_cast<char>(TileTypes::KOOPA_SPAWN) :
				_koopa = new Entity_Koopa(mRenderer, "resources/Images/Koopa.png", Vector2D(xPos, yPos));
				break;

			default:
				break;
			}
			xPos += TILE_WIDTH;
		}
	}
}
