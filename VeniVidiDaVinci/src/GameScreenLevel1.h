#pragma once
#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"

class Texture2D;  // Forward Declare
class Character; // Forward Declare
class PowBlock; // Forward Declare

class GameScreenLevel1 : public GameScreen
{
private:
	// Level
	Texture2D* mBackgroundTexture;
	Character* playerCharacters[AMOUNT_OF_PLAYERS];
	LevelMap* mLevelMap;

	bool SetUpLevel();
	void SetLevelMap();

	// Spawn counter
	float mSpawnCount;
	void SpawnEnemies();

	// Enemies
	std::vector<CharacterKoopa*> mEnemies;
	void UpdateEnemies(float deltaTime, SDL_Event event);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	// Coins
	std::vector<CharacterCoin*> mCoins;
	void CreateCoin(Vector2D position);
	void UpdateCoins(float deltaTime, SDL_Event event);

	// Pow Block
	PowBlock* mPowBlock;
	void UpdatePOWBlock();

	// Screen Shake
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenShake();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event event);

};
