#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	LoadLevel();
	_bgTexture = new Texture2D(renderer);
	_bgTexture->LoadFromFile("resources/Images/Backgrounds/1.png");
	_HUDTexture = new Texture2D(renderer);
	_HUDTexture->LoadFromFile("resources/Images/HUD.png");
}


GameScreenLevel2::~GameScreenLevel2()
{
	_tiles.clear();
	delete _bgTexture;
	_bgTexture = nullptr;
	delete _HUDTexture;
	_HUDTexture = nullptr;
	delete _mario;
	_mario = nullptr;
}

void GameScreenLevel2::Render()
{
	_bgTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	_HUDTexture->Render(Vector2D(0.0f, 412.0f), SDL_FLIP_NONE);
	if (_Screenshake)
	{
		float shake = sin(_Wobble) * 1.5f;
		for (unsigned int i = 0; i < _tiles.size(); i++)
		{
			_tiles[i]->Render(1.0f, shake);
		}
		_mario->Render();
		_koopa->Render();
	}
	else
	{
		for (unsigned int i = 0; i < _tiles.size(); i++)
		{
			_tiles[i]->Render();
		}
		_mario->Render();
		_koopa->Render();
	}
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event event)
{
	bool marioTriggered{ false }, koopaTriggered{ false };
	// Check Whether Mario is on the ground
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		// If block is pow tile
		if (typeid(*_tiles[i]) == typeid(Tile_POW))
		{
			// Check collision against POW block and activate it if collided
			if (static_cast<Tile_POW*>(_tiles[i])->IsAvailable())
			{
				if (_mario->Collision((void*)_tiles[i], TileTypes::POW))
				{
					_koopa->SetIfInjured(true);
					if (!_Screenshake)
					{
						DoScreenWobble();
					}
				}
			}
			// Remove POW Block is has no uses left
			else
				_tiles.erase(_tiles.begin() + i);
		}

		// If block is coin tile
		else if (typeid(*_tiles[i]) == typeid(Tile_Coin))
		{
			static_cast<Tile_Coin*>(_tiles[i])->Update(deltaTime);
			if (_mario->Collision((void*)_tiles[i], TileTypes::COIN))
			{
				_tiles.erase(_tiles.begin() + i);
			}
		}

		// Check Collision with platform blocks
		if (!marioTriggered)
		{
			_mario->Collision((void*)_tiles[i], TileTypes::PLATFORM);
			if (_mario->IsOnTheGround())
			{
				marioTriggered = true;
			}
		}
		if (!koopaTriggered)
		{
			_koopa->Collision((void*)_tiles[i], TileTypes::PLATFORM);
			if (_koopa->IsOnTheGround())
				koopaTriggered = true;
		}
	}
	marioTriggered = false;
	koopaTriggered = false;

	_mario->Update(deltaTime, event);
	_koopa->Update(deltaTime, event);

	if (_Screenshake)
	{
		_ScreenshakeTime -= deltaTime;
		_Wobble++;

		if (_ScreenshakeTime <= 0.0f)
		{
			_Screenshake = false;
		}
		
	}
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
				break;
			case static_cast<char>(TileTypes::PLATFORM) :
				_tiles.push_back(new Tile(mRenderer, TileTypes::PLATFORM, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::POW) :
				_tiles.push_back(new Tile_POW(mRenderer, TileTypes::POW, Vector2D(xPos, yPos)));
				break;
			case static_cast<char>(TileTypes::COIN) :
				_tiles.push_back(new Tile_Coin(mRenderer, TileTypes::COIN, Vector2D(xPos, yPos)));
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

void GameScreenLevel2::DoScreenWobble()
{
	_Screenshake = true;
	_ScreenshakeTime = SCREENSHAKE_DURATION;
	_Wobble = 0.0f;
}
