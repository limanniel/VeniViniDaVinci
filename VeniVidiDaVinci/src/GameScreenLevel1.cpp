#include "GameScreenLevel1.h"
#include "Character.h"  // Forward Declare
#include "Texture2D.h" // Forward Declare
#include "PowBlock.h" // Forward Declare

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = nullptr;
	SetLevelMap();
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	for (int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		delete[] &playerCharacters;
		playerCharacters[i] = nullptr;
	}
	mBackgroundTexture = nullptr;
	mEnemies.clear();

	delete mPowBlock;
	mPowBlock = nullptr;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event event)
{
	//Update the player
	for (int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		playerCharacters[i]->Update(deltaTime, event);
	}

	// Screenshake
	if (mScreenshake) {
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// End shake
		if (mScreenshakeTime <= 0.0f) {
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	if (Collisions::Instance()->Circle(playerCharacters[0]->getCollisionCircle(), playerCharacters[1]->getCollisionCircle())) {
		std::cerr << "Colliding!" << std::endl;
	}

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, event);
	UpdateCoins(deltaTime, event);
}

void GameScreenLevel1::Render()
{
	// Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE, 0.0f);
	for (int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		playerCharacters[i]->Render();
	}

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

	mPowBlock->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("resources/Images/BackgroundMB.png")) {
		std::cout << "Failed to load background texture!";
		return false;
	}
	// Set up player character
	playerCharacters[0] = new CharacterMario(mRenderer, "resources/Images/Mario.png", Vector2D(412.0f, 250.0f), mLevelMap);
	playerCharacters[1] = new CharacterLuigi(mRenderer, "resources/Images/Luigi.png", Vector2D(64.0f, 250.0f), mLevelMap);

	// Set up our POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map
	if (mLevelMap != nullptr) {
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);

	//Spawn initial enemies
	SpawnEnemies();

	//Create Coins
	CreateCoin(Vector2D(126.0f, 200.0f));
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event event)
{
	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			// Check Whether enemy is on groundlevel
			if (mEnemies[i]->GetPosition().y > 300.0f) {
				if ((mEnemies[i]->GetPosition().x < 64.0f) || // If hits left pipe
					(mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) { // If hits right pipe
					mEnemies[i]->SetAlive(false); // Set state of that enemy to be deleted
				}
			}

			mEnemies[i]->Update(deltaTime, event);
			for (int j = 0; j < AMOUNT_OF_PLAYERS; j++)
			{
				// Injured Koopa Death
				if (Collisions::Instance()->Circle(mEnemies[i], playerCharacters[j]) && mEnemies[i]->GetInjured()) {
					mEnemies[i]->SetAlive(false);
				}
				// PLAYER DEATH
				else {
					
				}
			}

			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}

			// Delete dead enemies from vector array
			if (enemyIndexToDelete != -1) {
				mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			}
		}
	}
	SpawnEnemies();
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "resources/Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	CharacterCoin* coin = new CharacterCoin(mRenderer, "resources/Images/Coin.png", position, mLevelMap);
	mCoins.push_back(coin);
}

void GameScreenLevel1::SpawnEnemies()
{
	if (mEnemies.empty()) {
		CreateKoopa(Vector2D(64.0f, 32.0f), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(416.0f, 32.0f), FACING_LEFT, KOOPA_SPEED);
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	for (int i = 0; i < AMOUNT_OF_PLAYERS; i++)
	{
		if (Collisions::Instance()->Box(playerCharacters[i]->getCollisionBox(), mPowBlock->GetCollisionBox())) {
			if (mPowBlock->isAvailable()) {
				// Collided whilst jumping
				if (playerCharacters[i]->isJumping()) {
					DoScreenShake();
					mPowBlock->TakeAHit();
					playerCharacters[i]->CancelJump();
				}
			}
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event event)
{
	int coinIndexToDelete{ -1 };
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, event);

		for (int j = 0; j < AMOUNT_OF_PLAYERS; j++) {
			if (Collisions::Instance()->Box(playerCharacters[j]->getCollisionBox(), mCoins[i]->getCollisionBox())) {
				mPlayerScore++;
				mCoins[i]->SetCollected(true);

				if (mCoins[i]->IsCollected()) {
					coinIndexToDelete = i;
				}
			}
		}
		if (coinIndexToDelete != -1) {
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}