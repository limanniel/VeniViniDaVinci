#pragma once
#include "GameScreen.h"
#include "Entity_Mario.h"
#include "Entity_Koopa.h"
#include "Tile_POW.h"
#include "Tile_Coin.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

class GameScreenLevel2 : public GameScreen
{
private:
	Texture2D* _bgTexture{ nullptr };
	Texture2D* _HUDTexture{ nullptr };

	// Object Holders
	std::vector<Tile*> _tiles;
	std::vector<Entity_Koopa*> _koopas;
	Entity_Mario* _mario{ nullptr };
	//Entity_Koopa* _koopa{ nullptr };

	// Screen Shake
	bool _Screenshake{ false };
	float _ScreenshakeTime{ 0.0f };
	float _Wobble{ 0.0f };
	void DoScreenWobble();

	// Load level from file
	void LoadLevel();

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};

