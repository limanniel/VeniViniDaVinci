#pragma once
#include "GameScreen.h"
#include "CharacterMario.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Tile.h"

class GameScreenLevel2 : public GameScreen
{
private:
	std::vector<Tile*> _tiles;
	CharacterMario* _mario;


	void LoadLevel();

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};

