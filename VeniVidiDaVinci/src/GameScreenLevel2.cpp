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
	_koopas.clear();
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

		for (unsigned int i = 0; i < _koopas.size(); i++)
		{
			_koopas[i]->Render();
		}
	}
	else
	{
		for (unsigned int i = 0; i < _tiles.size(); i++)
		{
			_tiles[i]->Render();
		}

		_mario->Render();

		for (unsigned int i = 0; i < _koopas.size(); i++)
		{
			_koopas[i]->Render();
		}
	}
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event event)
{
	// Check Whether Mario is on the ground
	for (unsigned int i = 0; i < _tiles.size(); i++)
	{
		// Check Collision with platform blocks each entity once
		if (!_mario->GetTriggered())
		{
			_mario->Collision((void*)_tiles[i], TileTypes::PLATFORM);
			if (_mario->IsOnTheGround())
				_mario->SetTriggered(true);
		}
	
		// If block is pow tile
		if (typeid(*_tiles[i]) == typeid(Tile_POW))
		{
			// Check collision against POW block and activate it if collided
			if (static_cast<Tile_POW*>(_tiles[i])->IsAvailable())
			{
				if (_mario->Collision((void*)_tiles[i], TileTypes::POW))
				{
					// Injure Koopas after smashing POW Block
					for (unsigned int i = 0; i < _koopas.size(); i++)
					{
						_koopas[i]->SetIfInjured(true);
					}

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
				// Remove picked-up coin
				_tiles.erase(_tiles.begin() + i);
			}
		}

		
		for (unsigned int j = 0; j < _koopas.size(); j++)
		{
			if (!_koopas[j]->GetTriggered())
			{
				_koopas[j]->Collision((void*)_tiles[i], TileTypes::PLATFORM);
				if (_koopas[j]->IsOnTheGround())
					_koopas[j]->SetTriggered(true);
			}
		}
	}
	_mario->SetTriggered(false);

	for (unsigned int i = 0; i < _koopas.size(); i++)
	{
		_koopas[i]->SetTriggered(false);
		if (Collisions::Instance()->Box(*_mario->GetRect(), *_koopas[i]->GetRect()))
		{
			// if koopa injured, kill koopa instead
			if (_koopas[i]->GetIfInjured())
			{
				_koopas.erase(_koopas.begin() + i);
			}
			// get killed by enemy
			else
			{
				SCREEN = SCREENS::SCREEN_GAMEOVER;
				SCREEN_CHANGE = true;
			}
		}
	}
	// Check if any enemy collided with mario and vice versa

	_mario->Update(deltaTime, event);
	for (unsigned int i = 0; i < _koopas.size(); i++)
	{
		_koopas[i]->Update(deltaTime, event);
	}

	if (_Screenshake)
	{
		_ScreenshakeTime -= deltaTime;
		_Wobble++;

		if (_ScreenshakeTime <= 0.0f)
			_Screenshake = false;
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
				_koopas.push_back(new Entity_Koopa(mRenderer, "resources/Images/Koopa.png", Vector2D(xPos, yPos)));
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
