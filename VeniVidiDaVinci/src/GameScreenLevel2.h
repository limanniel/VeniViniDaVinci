#pragma once
#include "GameScreen.h"
#include "Entity_Mario.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Tile.h"

class GameScreenLevel2 : public GameScreen
{
private:
	std::vector<Tile*> _tiles;
	Entity_Mario* _mario{ nullptr };


	void LoadLevel();

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};

