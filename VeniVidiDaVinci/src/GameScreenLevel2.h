#pragma once
#include "GameScreen.h"
#include "Entity_Mario.h"
#include "Entity_Koopa.h"
#include "Entity_POW.h"
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
	std::vector<Entity_POW*> _powBlocks;
	Entity_Mario* _mario{ nullptr };
	Entity_Koopa* _koopa{ nullptr };

	void LoadLevel();
 

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};

