#pragma once
#include "GameScreen.h"
#include "Entity_Mario.h"
#include "Entity_Koopa.h"
#include "Tile.h"
#include "Tile_POW.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

class GameScreenLevel2 : public GameScreen
{
private:
	std::vector<Tile*> _tiles;
	Entity_Mario* _mario{ nullptr };
	Entity_Koopa* _koopa{ nullptr };

	void LoadLevel();

	bool _Screenshake{ false };
	float _ScreenshakeTime{ 0.0f };
	float _Wobble{ 0.0f };
	void DoScreenWobble();

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};

